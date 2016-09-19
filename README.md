OpenGL Examples

## Building

#### Linux

    git clone --recursive https://github.com/matthewjberger/opengl.git
    cd opengl
    premake5 gmake
    cd build
    make
    # Navigate to desired demo's output directory and run the corresponding executable

To build specific examples only, add or remove lines in the premake5.lua file that say:
```lua
create_example("projectName")
```
in the _generate()_ function at the top of the file and then run premake again.
