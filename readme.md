# C++03 Compile-Time Ray-Tracer
A ray-tracer whose image is computed entirely at compile-time. The end result being a program with a set of constants baked in representing the color values of each pixel of the image.

# What happens while compiling

The compiler will recursively generate types each type is just one stage in the rendering process. The process starts with a set of global types reprsenting the scene data, and with the `Renderer` type to start the main loop.

## Scene Data

Data about what is in the scene and how it gets rendered are currently just global types accessed directly by the rendering process. If desired these could be passed as template parameters to each type in the rendering process to make things more reusable, but this could have an adverse affect on rendering times.

### MyObjectList

This contains the list of objects to be rendered, currently only spheres are used.

### MyCamera

Contains the position, direction, half extents of the view window, and the distance of the eye to the view plane.

### MyLight

A simple directional light for lighting the scene. This is the simplest form of lighting and keeps the compilation process much simpler. Other types of lights could be used just as easily. `MyLightLen` is computed once to minimize the lighting computations later.

## Looping Structure

The point of these types is generate `x` and `y` coordinate information once for each pixel in the image. The reset of the actual rendering process is handled with the `Render` type. Secondly, these types are used to generate all the runtime functions used to extract the image.

### Renderer

The `Renderer` type takes two arguments, the `Width` and `Height of the rendered scene in pixels. The job opf the Renderer is to start the recursive type generation with the `Loop` type. 

### Loop

The `Loop` type represents a nest for-loop over each pixel in the image. It does this with partial template specialization to step along each pixel in a row until it gets to the end, then stepping down to the next row to start over again. There is two recursive base cases, one for the end of each row, one pixel past the end. The other is for getting to the one row past the bottom.

### Render

The `Render` class is ultimately where all the color data constants are stored. It simply takes a computed color from `Raytrace` and redirects it's constants to the runtime.

## Rendering

### Raytrace

1. Compute a `Ray` type from the `x` and `y` coordinates
2. Run the ray through the `Query` type find intersection information
3. Run the intersection information through to compute the ultimate color

### Query

Takes a ray and a list of objects to interect with. It will keep track of the best intersection by the shortest distance to interesct. It simply runs through the list of objects linearly (there was only three in the test scene). Each interesction results in a normal and a reference to the object that was hit.

### ComputeColor

Takes the intersection information to compute the diffuse color contribution. It considers the color of the object that was hit, and surface normal to the light direction to compute shading.

## Optimising the compilation

It turns out that in the case of compile-time programs, unoptimized builds are far better. The compilation process will generate potentially millions of types that the compiler has to manage. Optimized builds end up using more memory, presumably because it is building up information needed for removing redundant code and generating as few instructions as possible. This is actually counter to what we want to acheive with compilation.

The projects contains a `Meta` configuration used to ensure the build is unoptimised.


# Extracting the Image

The compiler itself has very few mechanisms for outputting- one being the `#pragma message` and the other being an error message. I orignally considered force generating a compilation error at the end of the rendering process and simply stating the structure of this output to be a new image file format. This would mean creatign an image transformation program to convert from my new file type to a well established one.

Instead I opted for simplying having the runtime just oytput the image as its only task. No work for computing the image was being done at runtime, simply taking a series of constants and writing them to a file by calling `fprintf()` to form a .tga file.
