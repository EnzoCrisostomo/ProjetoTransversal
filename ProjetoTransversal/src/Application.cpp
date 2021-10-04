#include <glad/glad.h>
#include <exception>

#include "Application.h"
#include "Options/Options.h"

bool shouldUpdateProjMat = false;

void WindowResizeCallBack(GLFWwindow* window, int width, int height);

Application::Application(const char* applicationName, int width, int height)
    :m_width(width), m_heigth(height), m_elapsedTime(0.0)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    m_window = glfwCreateWindow(width, height, applicationName, nullptr, nullptr);

    if (m_window == nullptr)
    {
        throw std::runtime_error("Couldn't create glfwWindow.");
    }
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Couldn't load OpenGL.");
    }
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback(m_window, WindowResizeCallBack);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    m_masterRenderer = new MasterRenderer();
    m_world = new World(m_player);
    m_player.SetWindow(m_window);
}

Application::~Application()
{
    delete m_masterRenderer;
    delete m_world;
    glfwTerminate();
}


void Application::runLoop()
{
    //Main loop
    //==========================================================================================================================//
    while (!glfwWindowShouldClose(m_window))
    {
        double newFrameTime = glfwGetTime();

        if (shouldUpdateProjMat)
        {
            shouldUpdateProjMat = false;
            m_masterRenderer->UpdateOrthoProjMatrix();
            m_player.CreateProjectionMatrix();
        }
        m_player.Update(m_world, m_elapsedTime);

        m_world->UpdateWorld(m_player);
        m_world->RenderWorld(m_masterRenderer);
        m_masterRenderer->finishRender(m_player);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
        m_elapsedTime = glfwGetTime() - newFrameTime;
        /*double fps = 1.0 / m_elapsedTime;
        while (fps > 5)
        {
            m_elapsedTime = glfwGetTime() - newFrameTime;
            fps = 1.0 / m_elapsedTime;
        }
        std::cout << "Elapsed Time: " << m_elapsedTime << "\n";*/
        //std::cout << "fps: " << (int)fps << "\n";
    }
}

void WindowResizeCallBack(GLFWwindow* window, int width, int height)
{
    shouldUpdateProjMat = true;
    Options::windowWidth = (float)width;
    Options::windowHeight = (float)height;
    glViewport(0, 0, width, height);
}