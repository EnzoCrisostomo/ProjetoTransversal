#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* m_window = glfwCreateWindow(1280, 720, "********", nullptr, nullptr);

    if (m_window == nullptr)
    {
        throw std::runtime_error("Couldn't create glfwWindow.");
    }
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Couldn't load OpenGL.");
    }
    glViewport(0, 0, 1280, 720);

    
    while (!glfwWindowShouldClose(m_window))
    {
        glClearColor(0.60f, 0.20f, 0.70f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    glfwTerminate();

	return 0;
}