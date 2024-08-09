# Mandelbrot Set Image Generator

This is a simple C program to generate and save an image of the Mandelbrot set using a color gradient. The program uses the `stb_image_write` library to handle image file creation.

## Features

- Generates a Mandelbrot set image.
- Supports large image sizes.
- Uses a color gradient for better visual appeal.
- Outputs the image in PNG format.

## Prerequisites

- **C Compiler**: Ensure you have `gcc` or another C compiler installed.
- **stb_image_write**: This program uses the `stb_image_write` library to save images. Download the library from [stb](https://github.com/nothings/stb) and place the `stb_image_write.h` file in the same directory as the source code.

## Building

1. **Download the Source Code**: Clone or download the repository.

2. **Download the `stb_image_write.h`**: Place the `stb_image_write.h` file from [stb](https://github.com/nothings/stb) in the project directory.

3. **Compile the Program**:

   ```sh
   gcc -o mandelbrot main.c -Istb -lm
   ```

   - `-Istb` tells the compiler where to find the `stb_image_write.h` file.
   - `-lm` links the math library needed for mathematical functions.

## Usage

Run the compiled program:

```sh
./mandelbrot
```

This will generate an image named `mandelbrot.png` in the current directory.

## Configuration

The image resolution and other parameters can be adjusted by modifying the `#define` values in the `main.c` source file:

- `IMAGE_W` and `IMAGE_H`: Width and height of the output image.
- `SCALE`: Scaling factor for the Mandelbrot set.
- `MAX_ITER`: Maximum number of iterations for determining point membership in the Mandelbrot set.

## Example

To generate a `4096 * 4096` image, set:

```c
#define IMAGE_W 4096
#define IMAGE_H 4096
```
