# Slight documentation:

The engine consists of 5 components:
1. The engine (ConsoleEngine)
2. The texture (CharTexture)
3. The camera (CharCamera)
4. The rasterizer (CharRasterizer)
5. The math library (clfe::clm)

The math library is unimportant and was borrowed from another one of my unfinished projects (the library itself isn't complete either), so only the first 4 are important.

The structure is as following:
1. The engine employs the singleton pattern as to only have one instance that governs the single opened console during runtime
2. The engine itself holds a texture, a camera, and a rasterizer (created upon initiation)
3. The engine mainly handles user interfacing and "drawing" the texture on the console
4. The engine then funnels drawing and camera movement instructions to the rasterizer and camera
5. The camera is independent in the sense that it doesn't hold any references to other components
6. All the camera does is return transformation matrices based on its position and the given screen widths and heights
7. The texture doesn't do anything on its own and is just a data medium
8. The rasterizer holds a reference to a texture (which is drawn to) and a camera, which gives positional data for transforming 3d points into 2d space
9. Upon a 2d draw call, the rasterizer directly draws on the texture without any data manipulation
10. Upon a 3d draw call, the rasterizer requests the camera's transformation matrices and applys the transformations to the 3d points, transforming them into 2d points and then drawing

Usage:

* Everything is in the "Engine" namespace (you can just modify the code to change the namespace, there isn't much code so it should be simple)
* Due to simplicity, all declarations were stuffed in a single header file "engine/ConsoleEngine.h"
* Unlike modern graphics apis which queue draw calls and then performs them all at once, this engine performs as draws are called aka there is no centeral "draw everything" command (ConsoleEngine::render() is actually just putting the texture onto the console, not drawing everything)
* I am not very fluent with the console so you can check ConsoleEngine.cpp for the texture rendering code and perhaps modify it to draw to the console better
* Due to technical limitations and my laziness, there are no shaders for drawing triangles and stuff

For the actual implementations, just check HelloWorld.cpp
Do note that the engine was made on a whim and is not very optimized
This README was also made on a whim (who would actually use this engine lol)
