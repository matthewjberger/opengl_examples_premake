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
        "#version 330 core                                    \n"
        "layout(location = 0) in vec4 offset;                 \n"
        "void main(void)                                      \n"
        "{                                                    \n"
        "    const vec4 vertices[3] =                         \n"
        "       vec4[3](vec4(0.25, -0.25, 0.5, 1.0),          \n"
        "       vec4(-0.25, -0.25, 0.5, 1.0),                 \n"
        "       vec4(0.25, 0.25, 0.5, 1.0));                  \n"
        "    gl_Position = vertices[gl_VertexID] + offset;    \n"
        "}                                                    \n"
    };

    // Source code for fragment shader
    static const GLchar * fragment_shader_source[] =
    {
        "#version 330 core                    \n"
        "out vec4 color;                      \n"
        "void main(void)                      \n"
        "{                                    \n"
        "   color = vec4(0.0, 0.8, 1.0, 1.0); \n"
        "}                                    \n"
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
    // Create our shader program
    rendering_program = compile_shaders();

    // Create a dummy VAO
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
}

void MainState::finalize()
{
    // Delete our dummy VAO and our shader program 
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rendering_program);
}

void MainState::handle_events(SDL_Event event) {}
void MainState::update() {}

void MainState::draw()
{
    // Get the current time
    double currentTime = SDL_GetTicks() / 1000.00;

    // Create a color that varies gradually and cyclically with time
    const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f,
        (float)cos(currentTime) * 0.5f + 0.5f,
        0.0f, 1.0f };

    // Clear the screen to the color above
    glClearBufferfv(GL_COLOR, 0, color);

    // Use the shader program we created earlier
    glUseProgram(rendering_program);

    // Create an array of four floats that move a point in a circle in x,y over time
    GLfloat attrib[] = { 
        (float)sin(currentTime) * 0.5f,
        (float)cos(currentTime) * 0.6f,
        0.0f, 0.0f };    

    // Update the 'offset' vertex attribute with the value above
    glVertexAttrib4fv(0, attrib);

    // Process three vertices as a triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


