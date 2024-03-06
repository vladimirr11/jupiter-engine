# Jupiter Engine 
This repo is in its very beginning and at this time it represents a simple 2D/3D renderer that hasn't much to show. The renderer uses OpenGL as graphics API and at present most of the core OpenGL objects are abstracted. Next to come is a simple scene editor.

## Getting Started 
To clone the repo use:
```bash
git clone --recursive https://github.com/vladimirr11/jupiter-engine.git
```

### Build 
... with CMake. 
```bash
mkdir build
cd build
cmake .. <favorite make files generator>
cmake --build .
```
Tested compilers gcc 11.2 and 9.4 on Linux and Windows, MSVC 14.3 on Windows. 
