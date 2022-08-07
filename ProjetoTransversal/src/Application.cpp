#include <glad/glad.h>

#include "States/PlayingState.h"
#include "States/MainMenuState.h"
#include "Application.h"
#include "Options/Options.h"

#include <exception>
#include <filesystem>
#include <random>
#include <limits>
#include <locale>
#include <iostream>

void WindowResizeCallBack(GLFWwindow* window, int width, int height);

Application::Application(const char* applicationName, int width, int height)
    :m_width(width), m_heigth(height), m_elapsedTime(0.0)
{
    setlocale(LC_CTYPE, "");

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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Couldn't load OpenGL.");
    }
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback(m_window, WindowResizeCallBack);

    m_masterRenderer = new MasterRenderer();
}

Application::~Application()
{
    delete m_activeState;
    delete m_masterRenderer;
    glfwTerminate();
}


void Application::runLoop()
{
    //Main loop
    //==========================================================================================================================//
    while (!glfwWindowShouldClose(m_window))
    {
        if (m_activeState == nullptr)
            return;

        double newFrameTime = glfwGetTime();

        m_activeState->Update(m_elapsedTime);
        m_activeState->Render(m_masterRenderer);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
        m_elapsedTime = glfwGetTime() - newFrameTime;
    }
}

void Application::setup()
{
    if (Options::saveEnabled)
    {
        std::cout << "Criando pastas...\n";
        std::filesystem::create_directory(Options::dataPath);
        std::filesystem::create_directory(Options::savePath);
    }
    m_activeState = new MainMenuState(this, m_window);
}

void Application::ChangeState(BaseState* state)
{
    auto* menuState = dynamic_cast<MainMenuState*>(m_activeState);
    if (menuState)
    {
        delete menuState;
    }
    auto* playingState = dynamic_cast<PlayingState*>(m_activeState);
    if (playingState)
    {
        delete playingState;
    }
    m_activeState = state;
}

void WindowResizeCallBack(GLFWwindow* window, int width, int height)
{
    Options::windowWidth = (float)width;
    Options::windowHeight = (float)height;
    glViewport(0, 0, width, height);
}