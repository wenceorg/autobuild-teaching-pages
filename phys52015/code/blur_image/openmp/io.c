
// This file is part of the HPC workshop of Durham University
// Prepared by Alejandro Benitez-Llambay, November 2018
// email: alejandro.b.llambay@durham.ac.uk

#include "proto.h"
#include <stdio.h>
#include <stdlib.h>

void read_ppm(char *filename, struct Image *image) {
  int dimx, dimy;
  int i, j;
  unsigned char color[3];
  FILE *fp;
  if (!(fp = fopen(filename, "rb"))) {
    printf(RED "ERROR: Cannot read file %s \n" RESET, filename);
    return;
  }

  printf(GRN "Reading image file: %s ... " RESET, filename);
  fscanf(fp, "P6\n%d %d\n255\n", &dimx, &dimy);

  image->dimx = dimx;
  image->dimy = dimy;

  image->r = malloc(sizeof(float) * dimx * dimy);
  image->g = malloc(sizeof(float) * dimx * dimy);
  image->b = malloc(sizeof(float) * dimx * dimy);
  image->xcoord = malloc(sizeof(int) * dimx * dimy);
  image->ycoord = malloc(sizeof(int) * dimx * dimy);

  for (j = 0; j < dimy; j++) {
    for (i = 0; i < dimx; i++) {
      fread(color, 1, 3, fp);
      image->r[i + dimx * j] = (float)color[0];
      image->g[i + dimx * j] = (float)color[1];
      image->b[i + dimx * j] = (float)color[2];
      image->xcoord[i + dimx * j] = (int)i;
      image->ycoord[i + dimx * j] = (int)j;
    }
  }
  fclose(fp);
  printf(BLU "Done\n" RESET);
  return;
}

// function inspired by http://rosettacode.org
void write_ppm(char *filename, struct Image image) {
  int i, j;
  int dimx, dimy;
  FILE *fp;
  if (!(fp = fopen(filename, "wb"))) {
    printf(RED "ERROR: Cannot save file %s \n" RESET, filename);
    return;
  }

  fprintf(fp, "P6\n%d %d\n255\n", image.dimx, image.dimy);

  dimx = image.dimx;
  dimy = image.dimy;
  for (j = 0; j < dimy; j++) {
    for (i = 0; i < dimx; i++) {
      static unsigned char color[3];
      color[0] = image.r[i + dimx * j]; /* red */
      color[1] = image.g[i + dimx * j]; /* red */
      color[2] = image.b[i + dimx * j]; /* red */

      fwrite(color, 1, 3, fp);
    }
  }
  fclose(fp);
  return;
}
