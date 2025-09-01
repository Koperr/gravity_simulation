#pragma once
#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "glm.hpp"

class MyWindow {
public:
    MyWindow(int width, int height, const std::string& title);
    ~MyWindow();
    bool shouldClose() const;
    void pollEvents();
    void swapBuffers();
    void changeWindowTitle(const std::string& title);

    void processInput(const MyWindow& window, glm::vec3& camera_pos, glm::vec3& camera_front, glm::vec3& camera_up, float deltaTime);

    GLFWwindow* window;
private:

};

#endif