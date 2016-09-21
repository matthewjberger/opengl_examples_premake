#include <GlobalIncludes.h>
#include <VAO.h>
#include <Buffer.h>
#include <ShaderProgram.h>

class MainState
{
public:
    ~MainState(){}

    void initialize();

    void draw();
    void update();
    void handle_events(SDL_Event event);
    void finalize();

private:
    std::shared_ptr<VAO> triVAO;
    std::shared_ptr<Buffer> triVBO;
    std::shared_ptr<ShaderProgram> triProgram;
};
