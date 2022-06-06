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

//temp
#include <conio.h>

bool shouldUpdateProjMat = false;

void ImprimirMenu(std::string mensagem)
{
    system("cls");
    std::cout << 
        "====Menu Principal====\n"
        "1- Carregar Mundo\n"
        "2- Criar Mundo\n"
        "3- Editar Nome Mundo\n"
        "4- Excluir Mundo\n"
        "5- Sair\n\n";

    std::cout << mensagem << '\n';
}

std::string NavegarMundos()
{
    const std::filesystem::path worldPath{ Options::savePath };
    std::vector<std::string> mundos;
    for (auto const& dir_entry : std::filesystem::directory_iterator{ worldPath })
    {
        mundos.push_back(dir_entry.path().stem().string());
    }
    if (mundos.size() == 0)
    {
        ImprimirMenu("Não existem mundos salvos!");
        return "";
    }
    int pos = 0;
    std::cout << "\nMundos disponíveis:\n";
    while (true)
    {
        std::string msg = "\x1e \x1f  Para navegar, (backspace) para sair.\n\n";
        int start = 0;
        int end = 10;
        if (pos >= mundos.size() - 5)
        {
            if (mundos.size() >= 10)
                start = mundos.size() - 10;
            end = mundos.size();
        }
        else if (pos >= 5)
        {
            start = pos - 5;
            end = pos + 5;
        }
        for (int i = start; i < end && i < mundos.size(); i++)
        {
            msg += (pos == i ? "\x1a  " : "   ") + mundos[i] + '\n';
        }
        msg += "\nSelecione o mundo para carregar.";
        ImprimirMenu(msg);
        int x = _getch();
        switch (x)
        {
        case 8:
        {
            ImprimirMenu("Digite um número para comecar.");
            return "";
            break;
        }
        case 13:
        {
            if (mundos.size() > 0)
                return mundos[pos];
            else
            {
                ImprimirMenu("Não existem mundos salvos!");
                return "";
            }
            break;
        }
        case 72:
        {
            pos--;
            if (pos < 0)
                pos = 0;
            break;
        }
        case 80:
        {
            pos++;
            if (pos >= mundos.size())
                pos = mundos.size() - 1;
            break;
        }
        default:
            continue;
        }
    }
}

void WindowResizeCallBack(GLFWwindow* window, int width, int height);

Application::Application(const char* applicationName, int width, int height)
    :m_width(width), m_heigth(height), m_elapsedTime(0.0), m_state(State::Menu)
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
}

Application::~Application()
{
    delete m_masterRenderer;
    delete m_mainMenuState;
    if(m_playingState)
        delete m_playingState;
    glfwTerminate();
}


void Application::runLoop()
{
    //Main loop
    //==========================================================================================================================//
    m_mainMenuState = new MainMenuState(this);
    ImprimirMenu("Digite um número para comecar.");
    while (!glfwWindowShouldClose(m_window))
    {
        if (m_state == State::Menu)
        {
            if (m_playingState)
            {
                delete m_playingState;
                m_playingState = nullptr;
                ImprimirMenu("Digite um número para comecar.");
            }

            m_mainMenuState->Update(m_elapsedTime);
            
            int tecla = _getch();
            switch (tecla)
            {
            case 49:
            {
                std::string nomeMundo = NavegarMundos();
                if (nomeMundo == "")
                    break;
                
                if (std::filesystem::exists(Options::savePath + nomeMundo + "/"))
                {
                    ImprimirMenu("Carregando...");
                    m_playingState = new PlayingState(this, m_window, nomeMundo);
                    ChangeState(State::Playing);
                }
                else
                {
                    ImprimirMenu("O mundo não existe!");
                }
                break;
            }
            case 50:
            {
                ImprimirMenu("Digite o nome do mundo para criar: ");
                std::string nomeMundo;
                std::cin >> nomeMundo;

                if (!std::filesystem::exists(Options::savePath + nomeMundo + "/"))
                {
                    ImprimirMenu("Criando...");
                    m_playingState = new PlayingState(this, m_window, nomeMundo);
                    ChangeState(State::Playing);
                }
                else
                {
                    ImprimirMenu("O mundo \"" + nomeMundo + "\" já existe!");
                }
                break;
            }
            case 51:
            {
                std::string nomeMundo = NavegarMundos();
                if (nomeMundo == "")
                    break;

                ImprimirMenu("Digite um novo nome para " + nomeMundo + " : ");
                std::string novoNome;
                std::cin >> novoNome;

                if (std::filesystem::exists(Options::savePath + nomeMundo + "/"))
                {
                    std::filesystem::rename((Options::savePath + nomeMundo + "/"), 
                                            (Options::savePath + novoNome + "/"));
                    ImprimirMenu(nomeMundo + " renomeado para " + novoNome + ".");
                }
                else
                {
                    ImprimirMenu("Não foi possivel renomear o mundo.");
                }

                break;
            }
            case 52:
            {
                std::string nomeMundo = NavegarMundos();
                if (nomeMundo == "")
                    break;

                if (std::filesystem::exists(Options::savePath + nomeMundo + "/"))
                {
                    std::filesystem::remove_all(Options::savePath + nomeMundo + "/");
                    ImprimirMenu(nomeMundo + " Excluído.");
                }
                else
                {
                    ImprimirMenu("Não foi possivel excluir o mundo.");
                }

                break;
            }
            case 53:
            {
                std::cout << "Saindo...\n";
                glfwSetWindowShouldClose(m_window, true);
                break;
            }
            default:
            {
                ImprimirMenu(std::string("Tecla ") + std::to_string(tecla) + std::string(" não é válida!"));
                break;
            }
            }
            //m_playingState = new PlayingState(this, m_window, testeNome);
            //m_mainMenuState->Render(m_masterRenderer);
            glfwPollEvents();
        }
        if (m_state == State::Playing)
        {
            double newFrameTime = glfwGetTime();

            if (shouldUpdateProjMat)
            {
                shouldUpdateProjMat = false;
                m_masterRenderer->UpdateOrthoProjMatrix();
                m_playingState->UpdateMatrix();
            }
            m_playingState->Update(m_elapsedTime);
            m_playingState->Render(m_masterRenderer);
            glfwSwapBuffers(m_window);
            glfwPollEvents();
            m_elapsedTime = glfwGetTime() - newFrameTime;
        }

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

void Application::setup()
{
    if (Options::saveEnabled)
    {
        std::cout << "Criando pastas\n";
        std::filesystem::create_directory(Options::dataPath);
        std::filesystem::create_directory(Options::savePath);
    }
}

void Application::ChangeState(State state)
{
    m_state = state;
}

void WindowResizeCallBack(GLFWwindow* window, int width, int height)
{
    shouldUpdateProjMat = true;
    Options::windowWidth = (float)width;
    Options::windowHeight = (float)height;
    glViewport(0, 0, width, height);
}