/*********************************************
* Id: mart8517
* Name: Taylor Martin
* Course: CS-324 Computer Graphics
* Due Date: 4/8/22
* File: "MyGL.h"
* MyGL resource initialization file
*********************************************/
#ifndef MYGL_H
#define MYGL_H
#include <string>
#include <vector> 

//struct color to access colors values
struct color
{
   uint8_t red;
   uint8_t green;
   uint8_t blue;
}; 
//nested struct pixel which is of color type
struct pixel
{
   color c; 
}; 
//set color values 
namespace colors
{
   constexpr color BLACK{   0,   0,   0 };
   constexpr color WHITE{ 255, 255, 255 };
   constexpr color RED{   255,   0,   0 };
   constexpr color GREEN{   0, 255,   0 };
   constexpr color BLUE{    0,   0, 255 };
}

//Rows and Columns Sizes for 4x4 matrix
static const int NUM_ROWS = 4;
static const int NUM_COLS = 4; 

//Matrix type code
enum MYGL_MATRIX_TYPE 
{
   IDENTITY, X_TRANSLATION, Y_TRANSLATION, Z_TRANSLATION, 
   SCALING, X_ROTATION, Y_ROTATION, Z_ROTATION, PERSPECTIVE
}; 

class GraphicsCanvas
{
   public:
      //GraphicsCanvas class constructor
      GraphicsCanvas(double width, double height, color backgroundColor = colors::WHITE);  

      //setters 

      //set the pixel width and height and color 
      void setPixel(double x, double y, pixel color); 
      //set the color of the pixel 
      void setColor(double x, double y, color color); 

      //getters

      //getter member function returns pixel
      pixel getPixel(double x, double y)const;
      //get the width of the canvas
      double getWidth()const;
      //get the height of the canvas
      double getHeight()const;

      //other member functions
      
      //clears the screen
      void clearScreen();

   private:
      // Canvas width and height variables 
      double m_width, m_height; 
      
      //vector of pixel structs to store and utilize pixels
      std::vector<pixel>m_pixels;
     
      //create an instance to color struct called background to access colors values
      color m_backgroundColor;

}; 

//Sets the Viewport
void MYGL_DEFINE_VIEWPORT(double x1, double x2,double y1,double y2);

//Sets the Window 
void MYGL_DEFINE_WINDOW(double x1, double x2,double y1,double y2);

//mapping onto subregion of the bitmap/pixelmap. Transforms widow point to viewport point
void MYGL_WINDOW_TO_VIEWPORT(double X_WIN_POINT, double Y_WIN_POINT);

//initializes a matrix to the identity matrix
void MYGL_INIT_IDENTITY_MATRIX(double M[NUM_ROWS][NUM_COLS]); 

//Defines (initializes) an elementary transformation matrix
void MYGL_DEFINE_ELEMENTARY_TRANSFORM(double matrix[NUM_ROWS][NUM_COLS], enum MYGL_MATRIX_TYPE code, double value);

//matrix multiplication, concatenates matrices
void MYGL_MULTIPLY_TRANSFORMS(double matrix_A[NUM_ROWS][NUM_COLS], double matrix_B[NUM_ROWS][NUM_COLS], double result[NUM_ROWS][NUM_COLS]);

//multiplies together a vector and a 4x4 matrix
void MYGL_MULTIPLY(std::vector<double>Vec3, double ACTIVE_TRANSFORM[NUM_ROWS][NUM_COLS]); 

//builds a transform matrix
void MYGL_BUILD_ELEMENTARY_TRANSFORM(double TRANSFORM_MATRIX[NUM_ROWS][NUM_COLS], enum MYGL_MATRIX_TYPE TRANSFORM_CODE, double TRANSFORM_VALUE); 

// applies a transformation to a point
void MYGL_APPLY_TRANSFORM(std::vector<double>Vec3,double ACTIVE_TRANSFORM[NUM_ROWS][NUM_COLS]); 

//specifies the desired camera transformation matrix
void MYGL_DEFINE_CAMERA_TRANSFORM(double CAMERA_MATRIX[NUM_ROWS][NUM_COLS], double fX, double fY, double fZ, double theta, double phi, double alpha, double r);

//matrix printing 
void MYGL_PRINT_MATRIX(double matrix[NUM_ROWS][NUM_COLS]); 

//copies one matrix into the other
void MYGL_COPY_MATRIX(double matrix_A[NUM_ROWS][NUM_COLS],double matrix_B[NUM_ROWS][NUM_COLS]); 

//moves to a specific point in the view
void MYGL_MOVE_TO_3D(std::vector<double> Vec3, double ACTIVE_TRANSFORM[NUM_ROWS][NUM_COLS], double CAMERA_TRANSFORM[NUM_ROWS][NUM_COLS]);

//draws a line to a point in the view
void MYGL_DRAW_TO_3D(GraphicsCanvas& canvas, std::vector<double> Vec3, double ACTIVE_TRANSFORM[NUM_ROWS][NUM_COLS], double CAMERA_TRANSFORM[NUM_ROWS][NUM_COLS]);

//drawline
void MYGL_DRAW_LINE(GraphicsCanvas& canvas, double x1, double y1, double x2, double y2, color color);

//write name to file
void MYGL_WRITE_NAME(GraphicsCanvas const& canvas, std::string const& outFileName); 

//writes the created image to a bmp file
void writeGraphicsToFile(GraphicsCanvas const& canvas, std::string const& outFileName);



#endif /* MYGL_H */
