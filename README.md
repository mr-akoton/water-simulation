# Water Simulation

This project is a procedural water simulation and renderer written in C++ using *OpenGL 3.3*.
It was build for learning purposes, to better understand how sinewave operations and 3D rendering systems work using OpenGL.

---

## 🧩 Features

### Core Functionality

- ✅ Procedural generation — Wave generated with pseudo-random values.
- ✅ Configurable water parameters — Amplitude, frequency, steepness.
- ✅ Blinn Phong reflection model — Approximation of lighting.
- ✅ Camera system — Move and rotate freely in 3D space.

### Potential Features

- ⏳ Water effects — Reflection, depth, foam.
- ⏳ Skybox — Textured sky with a moving sun.
- ⏳ Tesselation — Mesh rendering optimization.
- ⏳ Cinematic effects — Post-process rendering effects.

---

## 🚀 Getting Started

### Prerequisites

This application is developed and tested on Linux only. You may not be able to build it on another operating system:

You need:
- `C++11` or later
- `OpengGL 3.3` compatible GPU.
- `GLFW` installed on the system or build localy.

### Compile and Run

Download or clone the repository on your device and compile it:

``` 
git clone git@github.com:mrakoton/water-simulation.git water-simulation
cd water-simulation && make
./water-simulation
```

---

## 🔗 Documentations

- [**Victor Gordan** - OpenGL Tutorial](https://www.youtube.com/watch?v=XpBGwZNyUh0&list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M-)
- [**Acerola** - How Games Fake Water](https://youtu.be/PH9q0HNBjT4?si=kZ0-5nDRtUmomY7x)
- [**GPUGems** - Chapter 1. Effective Water Simulation from Physical Models](https://developer.nvidia.com/gpugems/gpugems/part-i-natural-effects/chapter-1-effective-water-simulation-physical-models)
- [**Wikipedia** - Blinn Phong reflection model](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model)

