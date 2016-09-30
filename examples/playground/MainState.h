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

private:
	// State-wide objects and variables can go here
};
