# OpenGL Examples

This project uses premake to generate build files for linux or windows that link against SDL2 and OpenGL to run separate examples of OpenGL code. There is a set of core files that contain some OpenGL wrappers and a main file that runs a state machine inside of a game loop. In each example there is a state class that is set in the state machine at the start and has access to all of SDL2, SDL2_image, SDL2_ttf, SDL2_mixer, GLM, and OpenGL.

# Building

#### Linux

    git clone --recursive https://github.com/matthewjberger/opengl_examples.git
    cd opengl_examples
    premake5 gmake
    cd build
    make
    # Navigate to desired demo's output directory and run the corresponding executable

To build specific examples only, add or remove lines in the premake5.lua file that say:
```lua
create_example("projectName")
```
in the _generate()_ function at the top of the file and then run premake again.

#### Windows

Download the source and header files for all of SDL2, SDL2_image, SDL2_ttf, and SDL2_mixer and set an environment variable called *SDL2_PATH* to point to the root folder. The SDL2 folder structure should look like this:

```
SDL2
└───include
│      
└───lib
    └─── x64
    └─── x86
```
Place all of the include files from SDL2_image, SDL2_ttf, and SDL2_mixer in the main SDL2 include directory above, and all of their library files in the lib/x86 and lib/64 folders above.

Then, download GLM and set an environment variable called *GLM_PATH* to point to the root folder. It should look like this:

```
glm
└───glm
└─── (other folders that come with glm)
```

Visual Studio 2015 is recommended if building on windows.
