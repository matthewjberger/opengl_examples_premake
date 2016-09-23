#include <GlobalIncludes.h>

class MainState
{
public:
    ~MainState(){}

    void initialize();

    void draw();
    void update();
    void handle_events(SDL_Event event);
    void finalize();
    GLuint compile_shaders();

private:
    GLuint rendering_program;
    GLuint vertex_array_object;
};
