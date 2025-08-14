#include "MyWindow.h"
#include "Renderer.h"

#include "Shaders.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <iostream>

int main()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "Hello World!\n";

    MyWindow window(1920, 1080, "gravity_simulation");

    float positions[] = {
        -0.5f, -0.5f, 1.0, 0.0, 0.0, 0.0, 0.0,
         0.5f, -0.5f, 0.0, 1.0, 0.0, 1.0, 0.0,
         0.5f,  0.5f, 0.0, 0.0, 1.0, 1.0, 1.0,
        -0.5f,  0.5f, 1.0, 1.0, 1.0, 0.0, 1.0
    };

    uint indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    uint vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    VertexArray va;
    VertexBuffer vb(positions, 4 * 7 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indicies, 6);

    Shader shader("res/shaders/texture.glsl");
    GLCall(shader.Bind());
    //GLCall(shader.SetUniform4f("u_Color", 1.0f, 0.0f, 1.0f, 1.0f));

    Texture texture("res/textures/stalin.png");
    GLCall(texture.Bind()); // slot 0
    GLCall(shader.SetUniform1i("u_Texture", 0)); // slot 0

    Renderer renderer;



    while (!window.shouldClose()) {
        renderer.Clear();

        va.Bind();
        //ib.Bind();

        renderer.Draw(va, ib, shader);

        window.swapBuffers();
        window.pollEvents();
    }

    shader.Unbind();


    return 0;
}