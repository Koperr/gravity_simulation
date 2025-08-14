#pragma once
#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class MyWindow {
public:
    MyWindow(int width, int height, const std::string& title);
    ~MyWindow();
    bool shouldClose() const;
    void pollEvents();
    void swapBuffers();

private:
    GLFWwindow* window;
};

#endif