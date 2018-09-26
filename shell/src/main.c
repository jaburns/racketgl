#include <GL/glew.h>
#include <SDL.h>
#include <linmath.h>

typedef struct ShellState
{
    SDL_Window *sdl_window;
    SDL_GLContext sdl_context;
    int window_width;
    int window_height;
}
ShellState;

typedef struct FloatPair
{
    float first;
    float second;
}
FloatPair;

#define DLL_EXPORT __declspec(dllexport)

DLL_EXPORT void shell_init(const char *title, int width, int height)
{
    ShellState result;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // TODO panic
        //return result;
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); // MSAA
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetSwapInterval(1);

    result.window_width = width;
    result.window_height = height;

    result.sdl_window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    result.sdl_context = SDL_GL_CreateContext(result.sdl_window);

    glewExperimental = GL_TRUE;
    const GLenum glewInitResult = glewInit();

    if (glewInitResult != GLEW_OK)
    {
        SDL_GL_DeleteContext(result.sdl_context);
        SDL_DestroyWindow(result.sdl_window);
        SDL_Quit();

        // TODO panic
        // return result;
    }

    //return result;
}

DLL_EXPORT float add_floats(FloatPair pair)
{
    return pair.first + pair.second;
}