#include <GlobalIncludes.h>
#include <VAO.h>
#include <Buffer.h>
#include <ShaderProgram.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool Initialize();
void InitializeGL();
void Draw();
void Finalize();

std::shared_ptr<VAO> triVAO;
std::shared_ptr<Buffer> triVBO;
std::shared_ptr<ShaderProgram> triProgram;

SDL_Window* gWindow = nullptr;
SDL_GLContext gContext;

bool Initialize()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gContext = SDL_GL_CreateContext(gWindow);
            if (gContext == NULL)
            {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize GLAD
                gladLoadGLLoader(SDL_GL_GetProcAddress);

                //Use Vsync
                if (SDL_GL_SetSwapInterval(1) < 0)
                {
                    printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                }

                InitializeGL();
            }
        }


    }

    return success;
}

void InitializeGL()
{
    // Specify vertices
    glm::vec3 triangleVertices[] =
    {
        // Top Middle - Red
        glm::vec3(0.0f,  0.5f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f),

        // Bottom Right - Green
        glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f),

        // Bottom Left - Blue
        glm::vec3(-0.5f,  -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)
    };

    // Create and fill the Vertex Buffer, and configure the VAO
    triVAO = std::make_shared<VAO>();
    triVBO = std::make_shared<Buffer>();

    triVAO->bind();
    triVBO->bind();
    triVBO->add_data(&triangleVertices, sizeof(glm::vec3) * 6);
    triVBO->upload_data();

    // Configuring vertex attributes must be done last
    triVAO->enable_attribute(0); // Position
    triVAO->configure_attribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) * 2, 0);

    triVAO->enable_attribute(1); // Color
    triVAO->configure_attribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) * 2, (GLvoid*)sizeof(glm::vec3));
    triVAO->unbind();

    // Create the shader program
    triProgram = std::make_shared<ShaderProgram>();
    triProgram->create_program();
    triProgram->add_shader_from_file("shaders/triVert.glsl", GL_VERTEX_SHADER);
    triProgram->add_shader_from_file("shaders/triFrag.glsl", GL_FRAGMENT_SHADER);
    triProgram->link_program();
}

void Draw()
{
    // Clear the screen
    glClearColor(0.392f, 0.584f, 0.93f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    triProgram->use();
    triVAO->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    triVAO->unbind();
}

void Finalize()
{
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main(int argc, char* args[])
{
    if (!Initialize())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        bool quit = false;

        SDL_Event e;

        SDL_StartTextInput();

        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }

            Draw();

            SDL_GL_SwapWindow(gWindow);
        }

        SDL_StopTextInput();
    }

    Finalize();

    return 0;
}
