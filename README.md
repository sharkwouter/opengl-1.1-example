# OpenGL 1.1 example

This is a simple OpenGL example using SDL2 to manage the window. It just draws a basic cube made out of triangles and spins it. It works on PC and PSP.

## How to Build

### PC

Run the following commands:

```
mkdir build
cd build
cmake ..
make
```

The binary will be in the build directory.

### PSP

Install the [PSPDEV Toolchain](https://pspdev.github.io/). Then run the following commands:

```
mkdir build
cd build
psp-cmake ..
make
```


The `EBOOT.PBP` will be in the build directory.
