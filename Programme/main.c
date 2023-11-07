#include <stdio.h>
#include "biblio.h"
#include "ouverture.c"


int main(){

  FILE* f1 = OpenFile();
  FILE* f2 = CreateFile();
  image_t* image = ReadImage(f1);
  WriteP6(f2, image);
  free(f1);
  free(f2);
  free(image->pixels);
  free(image);

  return 0;
}