#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define IMAGE_W 4096
#define IMAGE_H 4096
#define SCALE 4
#define MAX_ITER 200

typedef struct {
  double x;
  double y;
} Complex;

// Function to convert iteration count to a color
void get_color(int n, uint8_t *r, uint8_t *g, uint8_t *b) {
  if (n == MAX_ITER) {
    // Color for points inside the Mandelbrot set (black)
    *r = *g = *b = 0;
  } else {
    // Map iteration count to a color gradient
    double t = (double)n / MAX_ITER;
    *r = (uint8_t)(9 * (1 - t) * t * t * t * 255);
    *g = (uint8_t)(15 * (1 - t) * (1 - t) * t * t * 255);
    *b = (uint8_t)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
  }
}

Complex pixels_to_complex(int i, int j) {
  Complex z = {SCALE * ((double)j / IMAGE_W - 0.5) * IMAGE_W / IMAGE_H,
               SCALE * ((double)i / IMAGE_H - 0.5)};
  return z;
}

Complex add(Complex z1, Complex z2) {
  Complex res = {z1.x + z2.x, z1.y + z2.y};
  return res;
}

Complex multiply(Complex z1, Complex z2) {
  Complex res = {z1.x * z2.x - z1.y * z2.y, z1.x * z2.y + z1.y * z2.x};
  return res;
}

double magnitude(Complex z) { return z.x * z.x + z.y * z.y; }

int main() {
  // Allocate memory for the image dynamically
  uint8_t *img = malloc(IMAGE_W * IMAGE_H * 3 * sizeof(uint8_t));
  if (img == NULL) {
    perror("Failed to allocate memory");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < IMAGE_H; i++) {
    for (int j = 0; j < IMAGE_W; j++) {
      Complex C = pixels_to_complex(i, j);
      Complex z = {0.0, 0.0};
      int n = 0;

      while (n < MAX_ITER && magnitude(z) <= 4.0) {
        z = add(multiply(z, z), C);
        n++;
      }

      // Get the color based on the number of iterations
      uint8_t r, g, b;
      get_color(n, &r, &g, &b);

      img[(i * IMAGE_W + j) * 3 + 0] = r; // Red
      img[(i * IMAGE_W + j) * 3 + 1] = g; // Green
      img[(i * IMAGE_W + j) * 3 + 2] = b; // Blue
    }
  }

  // Save the image
  stbi_write_png("mandelbrot.png", IMAGE_W, IMAGE_H, 3, img, IMAGE_W * 3);

  // Free the allocated memory
  free(img);

  system("xdg-open ./mandelbrot.png");

  return EXIT_SUCCESS;
}
