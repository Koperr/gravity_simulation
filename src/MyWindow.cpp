#include <iostream>

#include "MyWindow.h"

MyWindow::MyWindow(int width, int height, const std::string& title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        std::exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed creating window!" << std::endl;
        glfwTerminate();
        std::exit(-1);
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        std::exit(-1);
    }

    std::cout << "OpenGL version" << glGetString(GL_VERSION) << std::endl;
}

MyWindow::~MyWindow() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool MyWindow::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void MyWindow::pollEvents() {
    glfwPollEvents();
}

void MyWindow::swapBuffers() {
    glfwSwapBuffers(window);
}