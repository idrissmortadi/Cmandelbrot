#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define IMAGE_W 4096
#define IMAGE_H 4096
#define SCALE 4.0
#define MAX_ITER 100

typedef struct {
  double x;
  double y;
} Complex;

Complex pixels_to_complex(int i, int j) {
  Complex z = {SCALE * ((double)j / IMAGE_W - 0.5),
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

      // Map the number of iterations to a color (grayscale)
      uint8_t color = (uint8_t)(255 * n / MAX_ITER);
      img[(i * IMAGE_W + j) * 3 + 0] = color; // Red
      img[(i * IMAGE_W + j) * 3 + 1] = color; // Green
      img[(i * IMAGE_W + j) * 3 + 2] = color; // Blue
    }
  }

  // Save the image
  stbi_write_png("mandelbrot.png", IMAGE_W, IMAGE_H, 3, img, IMAGE_W * 3);

  // Free the allocated memory
  free(img);

  return EXIT_SUCCESS;
}
