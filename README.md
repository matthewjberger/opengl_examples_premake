OpenGL Examples

## Building

#### Linux

    premake5 gmake
    cd build
    make
    # Navigate to desired demo's output directory

To build specific examples only, add or remove lines in the premake5.lua file that say:
```lua
create_example("projectName")
```
in the _generate()_ function at the top of the file.
