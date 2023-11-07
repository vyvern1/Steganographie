#include <stdio.h>
#include "biblio.h"

FILE* CreateFile(){
  char nameFile[50];
  FILE* newFile;

  printf("Choisir le nom du fichier à créé (avec extension) : ");
  scanf("%s", nameFile);

  if (newFile = fopen(nameFile, "r")){
    printf("Le fichier %s existe déja veiller choisir un autre nom.\n",&nameFile);
    fclose(newFile);
    CreateFile();
  }
  else{
    newFile = fopen(nameFile, "w");
    printf("Le fichier %s à bien était créé\n",&nameFile);
    return newFile;
  }
}

FILE* OpenFile(){
  char nameFile[50];
  FILE* Couverture;

  printf("Enter le nom du fichier servant de couverture (avec extension) : ");
  scanf("%s", nameFile);

  if (Couverture = fopen(nameFile, "r")){
    return Couverture;
  }
  else{
    printf("Le fichier couverture %s n'existe pas, veiller choisir un autre nom.\n",&nameFile);
    OpenFile();
  }
}

header_t ReadHeader(FILE* image_file){
  header_t header;

  fscanf(image_file, "%2c %d %d %d ",header.magicNumber, &header.width, &header.height, &header.maxColor);
  header.magicNumber[2] = 0;
  return header;
}

image_t* ReadImage(FILE* image_file){
  header_t header = ReadHeader(image_file);
  image_t* image = NULL;

  if (strcmp("P6", header.magicNumber) == 0){
    image = ReadP6(image_file, header);
  }
  return image;
}

image_t* ReadP6(FILE* image_file, header_t header){
  int size = header.width * header.height;
  image_t* image = (image_t*) malloc (sizeof(image_t));
  image -> header = header;
  image -> pixels = (pixel_t*) malloc (sizeof(pixel_t)*size);
  char r = 0, g = 0, b = 0;

  for (int i = 0; i < (size) ; i++){
    fscanf(image_file, "%c%c%c", &r, &g, &b);
    image -> pixels[i].R = (int) r;
    image -> pixels[i].G = (int) g;
    image -> pixels[i].B = (int) b;
  }
  //printf("image -> pixels[0].R = %c\nimage -> pixels[0].R = %c\nimage -> pixels[0].R = %c",(char) image -> pixels[0].R, (char) image -> pixels[0].R, (char) image -> pixels[0].R);
  return image;
}

void WriteHeader(FILE* out_file, header_t header){
  fprintf(out_file, "%s\n%d\n%d %d\n", header.magicNumber,header.width,header.height,header.maxColor);
}

void WriteP6(FILE* out_file, image_t* image){
  header_t header = image -> header;
  header.magicNumber[1] = '6';
  WriteHeader(out_file, header);
  int size = header.width * header.height;

  for (int i = 0; i < (size); i++){
    fprintf(out_file,"%c%c%c", (char) image->pixels[i].R, (char) image->pixels[i].G, (char) image->pixels[i].B);
  }
}