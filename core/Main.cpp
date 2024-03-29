#include "GlobalIncludes.h"
#include "MainState.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool Initialize();
void Finalize();

SDL_Window* gWindow = nullptr;
SDL_GLContext gContext;

int main(int argc, char* args[])
{
    MainState state;

    if (!Initialize())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        state.initialize();

        bool quit = false;
        SDL_Event event;
        SDL_StartTextInput();
        while (!quit)
        {
            while (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }
            }
            state.handle_events(event);
            state.update();
            state.draw();
            SDL_GL_SwapWindow(gWindow);
        }
        SDL_StopTextInput();

        state.finalize();
    }
    Finalize();
    return 0;
}

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

        gWindow = SDL_CreateWindow("OpenGL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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
            }
        }


    }

    return success;
}

void Finalize()
{
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}


