#include <stdio.h>
#include <tiffio.h>

int main (int argc, char** argv){
    TIFF* tiff;
    tiff = TIFFOpen (argv[1], "r");
    TIFFClose (tiff);
    printf("Closed");
    return 0;
}
/*
para ejecutar en el build como argumento pasar:
../../src/cap2/listing2.9/imagen.tiff

*/