/*********************************************
* Id: mart8517
* Name: Taylor Martin
* Course: CS-324 Computer Graphics
* Due Date: 4/8/22
* Ran on windows, complied in PowerShell
* Compile: c++ -Wall -Wextra -std=c++14 MyGL.h MyGL.cpp main.cpp -o main.exe
* Run: ./main.exe
* File: "main.cpp"
*********************************************/
#include "MyGL.h"
#include <string>
#include <cmath>
#define M_PI 3.141592653589793 
int main()
{
   //set size of canvas
   //constexpr auto SIZE = 800; 
   double M[NUM_ROWS][NUM_COLS]; 
   double fX = 0.0; 
   double fY = 1.0; 
   double fZ = 0.0; 
   double theta = 45; 
   double phi = 30;
   double alpha = 0;
   double r = 25; 

   MYGL_INIT_IDENTITY_MATRIX(M);
   MYGL_DEFINE_CAMERA_TRANSFORM(M,fX, fY, fZ, theta, phi,alpha,r); 
   MYGL_PRINT_MATRIX(M);

   return 0;
}