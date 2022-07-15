








# Team A: Low-level image processing

### Using programming language C++ and framework Qt implement a program that represents a system that applies different image processing algorithms on input images. The software must have the following features:

- graphical user interface; /in - Ivon Nikolova/
- opens popular raster image formats like jpg, png;
- can apply a set of image processing algorithms, visualize the result, and save the resulting image as a file

### The algorithms implemented must be:

- Spatial filtering: 
  - low-pass Gaussian smoothing filtering /rr - Radoslav Radev/, 
  - Laplacian sharpening filter /rr/, 
  - image sharpening using the gradient /in/.
- Non-linear spatial filtering: noise reduction using median filtering. /tk - Tanyo Kostadinov/ 
- Sobel edge detection on a gray-scale image. /at - Angel Terziev/
- Canny edge detection on a gray-scale image (optional).

- Additional:
  - convert an image to Grayscale /in/
  - Mean filter  /in/

Tasks:
- Implement history (Cmd + Z)
- Make the filter abstract class when the other filters are implemented, since we may use many of its current functions
