#include "trafo.h"

int rgb2gray(int R, int G, int B){

   int gray;

   int coef1 = 3483;
   int coef2 = 11718;
   int coef3 = 1183;

   gray = (R*coef1 + G*coef2 + B*coef3)/16384;

   return gray;
}
