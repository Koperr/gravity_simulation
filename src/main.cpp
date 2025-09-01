//#include "Event.h"
#include "Renderer.h"
#include "MyWindow.h"

#include "Shaders.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "Camera.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;
bool SCR_FOCUS = true;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    MyWindow my_window(SCR_WIDTH, SCR_HEIGHT, "gravity_simulation");

    glfwSetFramebufferSizeCallback(my_window.window, framebuffer_size_callback);
    glfwSetKeyCallback(my_window.window, key_callback);
    glfwSetCursorPosCallback(my_window.window, mouse_callback);
    glfwSetScrollCallback(my_window.window, scroll_callback);

    float positions[] = {
        100.0f, 100.0f, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
        200.0f, 100.0f, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0,
        200.0f, 200.0f, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0,
        100.0f, 200.0f, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0
    };

    float positions_cube[] = {
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f
    };

    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int indicies_cube[] = {
        0,1,2, 2,3,0,  // tył
        4,5,6, 6,7,4,  // przód
        0,1,5, 5,4,0,  // dół
        2,3,7, 7,6,2,  // góra
        0,3,7, 7,4,0,  // lewa
        1,2,6, 6,5,1   // prawa
    };

    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    VertexArray va;
    //VertexBuffer vb(positions2, 4 * 8 * sizeof(float));
    VertexBuffer vb(positions_cube, 8 * 6 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(3); // xyz
    layout.Push<float>(3); // rgb
    //layout.Push<float>(2); // texcoord
    va.AddBuffer(vb, layout);

    //IndexBuffer ib(indicies, 6); // square
    IndexBuffer ib(indicies_cube, 3 * 6 * 2); // qube

    Shader shader("res/shaders/rgb.glsl");
    GLCall(shader.Bind());
    GLCall(shader.SetUniform4f("u_Color", 1.0f, 0.0f, 1.0f, 1.0f));

    //Texture texture("res/textures/stalin.png");
    //GLCall(texture.Bind()); // slot 0
    //GLCall(shader.SetUniform1i("u_Texture", 0)); // slot 0

    Renderer renderer;

    va.Bind();

    
    //glfwSetKeyCallback(window.GetWindow(), key_callback);
    lastFrame = glfwGetTime();

    while (!my_window.shouldClose()) {
        renderer.Clear();
        
        // per frame time logic
        // --------------------
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;
        
        // input
        // ------------
        processInput(my_window.window);
        
        
        GLCall(shader.SetUniform1f("u_Time", currentTime));


        glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 960.0f/540.0f, 0.1f, 100.0f);

        glm::mat4 mvp = proj * view * model;
        GLCall(shader.SetUniformMat4("m_MVP", mvp));
        std::cout << "x = " << camera.Position.x << " y = " 
        << camera.Position.y << " z = " << camera.Position.z << " yaw = " << camera.Yaw
        << " pitch = " << camera.Pitch << std::endl;
        
        my_window.changeWindowTitle(std::to_string(currentTime).c_str());
        
        renderer.Draw(va, ib, shader);

        my_window.swapBuffers();
        my_window.pollEvents();
    }

    shader.Unbind();


    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever key is pressed
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
    {
        if (SCR_FOCUS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPosCallback(window, nullptr);
            SCR_FOCUS = false;
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(window, mouse_callback);
            SCR_FOCUS = true;
        }
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
