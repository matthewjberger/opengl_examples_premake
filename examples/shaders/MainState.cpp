#include <MainState.h>

/* Created by following the example from the excellent OpenGL Superbible 7 book */

GLuint MainState::compile_shaders()
{
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint program;

    // Source code for vertex shader
    static const char * vertex_shader_source[] =
    {
        "#version 330 core                           \n"
        "void main(void)                             \n"
        "{                                           \n"
        "    gl_Position = vec4(0.0, 0.0, 0.5, 1.0); \n"
        "}                                           \n"
    };

    // Source code for fragment shader
    static const GLchar * fragment_shader_source[] =
    {
        "#version 330 core                  \n"
        "                                   \n"
        "out vec4 color;                    \n"
        "                                   \n"
        "void main(void)                    \n"
        "{                                  \n"
        " color = vec4(0.0, 0.8, 1.0, 1.0); \n"
        "}                                  \n"
    };

    // Create and compile vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    // Create and compile fragment shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    // Create program, attach shaders, and link the shaders
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    // Delete the shaders as the program has them now
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

void MainState::initialize()
{
    rendering_program = compile_shaders();
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
}

void MainState::finalize()
{
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rendering_program);
}

void MainState::handle_events(SDL_Event event) {}
void MainState::update() {}

void MainState::draw()
{
    int currentTime = SDL_GetTicks() / 1000;
    const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f,
        (float)cos(currentTime) * 0.5f + 0.5f,
        0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, color);

    glUseProgram(rendering_program);
    glPointSize(40.0f);
    glDrawArrays(GL_POINTS, 1, 1);
}


