/*********************************************
* Id: mart8517
* Name: Taylor Martin
* Course: CS-324 Computer Graphics
* Due Date: 4/8/22
* File: "MyGL.cpp"
* MyGL resource definition file
*********************************************/
#include "MyGL.h"
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>
#define M_PI 3.141592653589793 

//Window Dimension Variables
static double X_WIN_LENGTH,Y_WIN_LENGTH;
static double X_WIN_MIN,X_WIN_MAX,Y_WIN_MIN,Y_WIN_MAX; 

//Viewport Dimension Variables
static double X_VIEW_LENGTH,Y_VIEW_LENGTH; 
static double X_VIEW_MIN,X_VIEW_MAX,Y_VIEW_MIN,Y_VIEW_MAX;

//Coordinate Variables
static double X_POS_START, Y_POS_START, X_POS_END, Y_POS_END;

//Transformation Variables 
static double TRANSFORMED_X_COORDINATE, TRANSFORMED_Y_COORDINATE; 


/*********************************************
 * Function: Graphics Canvas class constructor
 * Description: initializes GraphicsCanvas 
 *              objects with specified values.
 * Input Parameters: width, height, and color 
 *                   of Canvas.
*********************************************/
GraphicsCanvas::GraphicsCanvas( double width, double height, color background )
    : m_width(width), m_height(height), 
      m_pixels(m_width * m_height, {background}),
      m_backgroundColor(background) { }

/********************************************
 *                SETTERS                   *
********************************************/

/*********************************************
 * Function: setColor
 * Description: sets the color of our pixel
 *              within vector m_pixels
 * Input Parameters: x position, y position, and color of pixel
*********************************************/
void GraphicsCanvas::setColor(double x, double y, color color)
{
   if(x >= 0 && x < m_width && y >= 0 && y < m_height)
   {
      m_pixels[y * m_width + x] = {color}; 
   }
}

/*********************************************
 * Function: setPixel
 * Description: sets the pixel attributes
 * Input Parameters: x position, y position, and pixel value
*********************************************/
void GraphicsCanvas::setPixel(double x, double y, pixel pixel)
{
   if(x >= 0 && x < m_width && y >= 0 && y < m_height)
   {
      m_pixels[y * m_width + x] = pixel;
   }
}

/********************************************
 *                GETTERS                   *
********************************************/

/*********************************************
 * Function: getWidth
 * Description: accesses the GraphicsCanvas
 *              member variable m_width. 
 * Output: returns m_width
*********************************************/
double GraphicsCanvas::getWidth() const
{
   return m_width;
}

/*********************************************
 * Function: getHeight
 * Description: accesses the GraphicsCanvas member
 *              variable m_height. 
 * Output: returns m_height
*********************************************/
double GraphicsCanvas::getHeight() const
{
   return m_height;
}

/*********************************************
 * Function: getPixel
 * Description: accesses elements within GraphicsCanvas
 *              member container m_pixels. 
 * Input: x and y coordinates
 * Output: returns m_pixels
*********************************************/
pixel GraphicsCanvas::getPixel(double x, double y) const
{
   return m_pixels[y * m_width + x]; 
}

/*******************************************
 *          OTHER MEMBER METHODS           *
********************************************/

/*********************************************
 * Function: clearScreen
 * Description: resets the pixels in GraphicsCanvas
 *              member container m_pixels to the original
 *              background color. 
*********************************************/
void GraphicsCanvas::clearScreen()
{
   //auto loop to reset the values within 
   //m_pixels to the original background color
   for(auto pixel : m_pixels)
   {
      pixel = {m_backgroundColor}; 
   }
}

/*******************************************
 *            NON-MEMBER METHODS           *
********************************************/

/*********************************************
 * Function: writeGraphicsToFile
 * Description: creates a bmp file and writes 
 *              the pixels from m_pixels to 
 *              the newly created file. 
 * Input: GraphicsCanvas object and filename 
 *        for output
 * Output: creates a bmp file with canvas
*********************************************/
void writeGraphicsToFile(GraphicsCanvas const& canvas, std::string const& outFileName)
{
   std::fstream outFile(outFileName, std::ios::app); 

   //check to see if file creation and opening was successful
   if(!outFile)
   {
      //shoot error message and exit if file creation failed 
      std::cerr << "Couldn't open file " << outFileName <<" Terminating Process\n"; 
      exit(1); 
   }

   outFile << "P6 " << canvas.getWidth() << " " << canvas.getHeight() << " 255\n";

   //write pixels to file
   for(auto y = 0; y < canvas.getHeight(); ++y)
   {
      for(auto x = 0; x < canvas.getWidth(); ++x)
      {
         auto const pixel = canvas.getPixel(x, y);

         outFile << pixel.c.red << pixel.c.green << pixel.c.blue; 
      }
   }
}

/*********************************************
 * Function: MYGL_WRITE_NAME
 * Description: creates a bmp file and writes 
 *              my name to the ouptut file. 
 * Input: GraphicsCanvas object and filename 
 *        for output
 * Output: creates a bmp file with canvas
*********************************************/
void MYGL_WRITE_NAME(GraphicsCanvas const& canvas, std::string const& outFileName)
{
   std::fstream outFile(outFileName, std::ios::out); 

   //check to see if file creation and opening was successful
   if(!outFile)
   {
      //shoot error message and exit if file creation failed 
      std::cerr << "Couldn't open file " << outFileName <<" Terminating Process\n"; 
      exit(1); 
   }

   outFile << "Taylor Martin\n CS-324: Computer Graphics\n PA#3: MyGL\n";
}

/*********************************************
 * Function: setViewport
 * Description: Sets the Viewport of the window.
 * Input: x1, x2, y1, y2 positions 
*********************************************/

void MYGL_DEFINE_VIEWPORT(double x1, double x2, double y1,double y2)
{

   X_VIEW_MIN = x1;
   X_VIEW_MAX = x2;
   Y_VIEW_MIN = y1;
   Y_VIEW_MAX = y2;
   X_VIEW_LENGTH = X_VIEW_MAX - X_VIEW_MIN;
   Y_VIEW_LENGTH = Y_VIEW_MAX - Y_VIEW_MIN; 
}

/*********************************************
 * Function: setWindow
 * Description: sets the window of the canvas. 
 * Input: x1, x2, y1, y2 positions
*********************************************/
void MYGL_DEFINE_WINDOW(double x1, double x2, double y1,double y2)
{ 
   X_WIN_MIN = x1;
   X_WIN_MAX = x2;
   Y_WIN_MIN = y1;
   Y_WIN_MAX = y2;
   X_WIN_LENGTH = X_WIN_MAX - X_WIN_MIN;
   Y_WIN_LENGTH = Y_WIN_MAX - Y_WIN_MIN;
}

/*********************************************
 * Function: windowToViewport
 * Description: maps a point from window space to 
 *              viewport space
 * Input: double xWinPoint, double yWinPoint
 * Output: Transformed viewport point coordinates
*********************************************/
void MYGL_WINDOW_TO_VIEWPORT(double X_WIN_POINT, double Y_WIN_POINT)
{  
   //window points in 
   //viewport points out

   //scaling factor Sx for x coordinate
   double sx = (X_VIEW_LENGTH)/(X_WIN_LENGTH);
   //scaling factor Sy for y coordinate
   double sy = (Y_VIEW_LENGTH)/(Y_WIN_LENGTH); 
   //calculate the x coordinate transformation point for the Viewport
   TRANSFORMED_X_COORDINATE = X_VIEW_MIN + (X_WIN_POINT - X_WIN_MIN)*sx; 
   //calculate the y coordinate transformation point for the Viewport
   TRANSFORMED_Y_COORDINATE = Y_VIEW_MIN + (Y_WIN_POINT - Y_WIN_MIN)*sy; 

   std::cout << "The Transformed Point on the Viewport is : (" << TRANSFORMED_X_COORDINATE << "," << TRANSFORMED_Y_COORDINATE << ")\n\n";
}

/*********************************************
 * Function: MYGL_MOVE_TO_3D
 * Description: moves to a specific point in the view
 * Input: x, y, z cordinates and active transformation matrix
*********************************************/

void MYGL_MOVE_TO_3D(std::vector<double> Vec3, double ACTIVE_TRANSFORM[NUM_ROWS][NUM_COLS], double CAMERA_TRANSFORM[NUM_ROWS][NUM_COLS])
{
   // procedure Draw3D (
   // (x, y, z) --- point to which we want to draw
   // aT --- active transform
   // cT --- Camera transform )
   // {
   // Apply aT to (x, y, z) --> (x’, y’, z’)
   // Apply cT to (x’, y’, z’) --> (x’’, y’’, z’’)
   // -- Project onto xy plane (x’’, y’’)
   // Map window to viewport (x’’, y’’) --> (vX, vY)
   // DrawTo( vX, vY )
   // }

   // Apply aT to (x, y, z) --> (x’, y’, z’)
   MYGL_MULTIPLY(Vec3,ACTIVE_TRANSFORM);

   // Apply cT to (x’, y’, z’) --> (x’’, y’’, z’’)
   MYGL_MULTIPLY(Vec3,CAMERA_TRANSFORM);

   //Project onto xy plane (x’’, y’’)
   MYGL_WINDOW_TO_VIEWPORT(Vec3[0], Vec3[1]); 

   X_POS_START = TRANSFORMED_X_COORDINATE; 
   Y_POS_START = TRANSFORMED_Y_COORDINATE; 
}


/*********************************************
 * Function: MYGL_DRAW_TO_3D
 * Description: draws a line to a point in the view
 * Input: x, y, z cordinates and active transformation matrix
*********************************************/

void MYGL_DRAW_TO_3D(GraphicsCanvas& canvas, std::vector<double> Vec3, double ACTIVE_TRANSFORM[NUM_ROWS][NUM_COLS], double CAMERA_TRANSFORM[NUM_ROWS][NUM_COLS])
{
   // procedure Draw3D (
   // (x, y, z) --- point to which we want to draw
   // aT --- active transform
   // cT --- Camera transform )
   // {
   // Apply aT to (x, y, z) --> (x’, y’, z’)
   // Apply cT to (x’, y’, z’) --> (x’’, y’’, z’’)
   // -- Project onto xy plane (x’’, y’’)
   // Map window to viewport (x’’, y’’) --> (vX, vY)
   // DrawTo( vX, vY )
   // }

   // Apply aT to (x, y, z) --> (x’, y’, z’)
   MYGL_MULTIPLY(Vec3,ACTIVE_TRANSFORM);

   // Apply cT to (x’, y’, z’) --> (x’’, y’’, z’’)
   MYGL_MULTIPLY(Vec3,CAMERA_TRANSFORM);

   //Project onto xy plane (x’’, y’’)
   MYGL_WINDOW_TO_VIEWPORT(Vec3[0], Vec3[1]); 

   X_POS_END = TRANSFORMED_X_COORDINATE; 
   Y_POS_END = TRANSFORMED_Y_COORDINATE; 

   //call MYGL_DrawLine after scaling
   MYGL_DrawLine(canvas,X_POS_START,Y_POS_START,X_POS_END,Y_POS_END,colors::BLACK); 

   //save current point for next function call
   X_POS_START = X_POS_END;
   Y_POS_START = Y_POS_END;
}


/*********************************************
 * Function: MYGL_DEFINE_ELEMENTARY_TRANSFORM
 * Description:  initializes a identity matrix
 *       
 * Input: A 4x4 Matrix 
*********************************************/
void MYGL_INIT_IDENTITY_MATRIX(double M[NUM_ROWS][NUM_COLS])
{
   double IDENTITY_MATRIX[4][4]= 
      { 1 , 0 , 0 , 0 , 
        0 , 1 , 0 , 0 ,
        0 , 0 , 1 , 0 , 
        0 , 0 , 0 , 1
      }; 

   for(int i = 0; i < NUM_ROWS; i++)
   {
      for(int j = 0; j < NUM_COLS; j++)
      {
         M[i][j] = IDENTITY_MATRIX[i][j]; 
      }

   }
}

/*********************************************
 * Function: MYGL_DEFINE_ELEMENTARY_TRANSFORM
 * Description:  initializes an elementary transformation matrix
 *       
 * Input: A 4x4 Matrix and Matrix type
*********************************************/
void MYGL_DEFINE_ELEMENTARY_TRANSFORM(double matrix[NUM_ROWS][NUM_COLS], enum MYGL_MATRIX_TYPE code, double value)
{

   if(code == X_TRANSLATION)
   {
      matrix[3][0] = value; 
   }

   if(code == Y_TRANSLATION)
   {
      matrix[3][1] = value;
   }

    if(code == Z_TRANSLATION)
   {
      matrix[3][2] = value;
   }

   if(code == SCALING)
   {
      matrix[0][0] = value; 
      matrix[1][1] = value;
      matrix[2][2] = value;

   }

   if(code == X_ROTATION)
   {
      double radians = value * (180/M_PI); 
      matrix[1][1] = cos(radians);
      matrix[1][2] = sin(radians);
      matrix[2][1] = -sin(radians);
      matrix[2][2] = cos(radians);
   }

   if(code == Y_ROTATION)
   {
      double radians = value * (180/M_PI); 
      matrix[0][0] = cos(radians);
      matrix[0][2] = -sin(radians);
      matrix[2][0] = sin(radians);
      matrix[2][2] = cos(radians);
   }

   if(code == Z_ROTATION)
   {
      double radians = value * (180/M_PI); 
      matrix[0][0] = cos(radians);
      matrix[0][1] = sin(radians);
      matrix[1][0] = -sin(radians);
      matrix[1][1] = cos(radians);
   }

   if(code == PERSPECTIVE)
   {
      matrix[2][3] = -(1/value);
   }

   //MYGL_PRINT_MATRIX(matrix); 
}

/*********************************************
 * Function: MYGL_BUILD_ELEMENTARY_TRANSFORM
 *
 * Description: routine creates a new transform by premultiplying 
 *        a transform by a new transform 
 *        (as specified by the arguments to the routine)
 * 
 * Input: transformation matrix, matrix type, value for transformation
*********************************************/
void MYGL_BUILD_ELEMENTARY_TRANSFORM(double TRANSFORM_MATRIX[NUM_ROWS][NUM_COLS], enum MYGL_MATRIX_TYPE TRANSFORM_CODE, double TRANSFORM_VALUE)
{
   //create two temporary matrices
   double M[NUM_ROWS][NUM_COLS], M2[NUM_ROWS][NUM_COLS]; 
   MYGL_INIT_IDENTITY_MATRIX(M);

   //create new transformation matrix
   MYGL_DEFINE_ELEMENTARY_TRANSFORM(M, TRANSFORM_CODE, TRANSFORM_VALUE); 
  
   //concatenate transformarion matrices
   MYGL_MULTIPLY_TRANSFORMS(TRANSFORM_MATRIX,M,M2); 
 

   //copy M2 into TRANSFORM_MATRIX
   MYGL_COPY_MATRIX(M2,TRANSFORM_MATRIX); 

}

/*********************************************
 * Function: MYGL_DEFINE_CAMERA_TRANSFORM
 *
 * Description: specifies the desired camera transformation matrix.
 * 
 * Input: fX, fY, fZ -- focal point
         theta, phi, alpha -- orientation
         r -- distance: eye to origin
*********************************************/
void MYGL_DEFINE_CAMERA_TRANSFORM(double CAMERA_MATRIX[NUM_ROWS][NUM_COLS], double fX, double fY, double fZ, double theta, double phi, double alpha, double r)
{
   // procedure DefineCameraTransform (
   // fX, fY, fZ -- focal point
   // theta, phi, alpha -- orientation
   // r -- distance: eye to origin )
   // {
   // -- Apply translation transformations
   // DefineElementaryTransform( CAMERA, X_TRANS, -fX )
   // BuildElementaryTransform( CAMERA, Y_TRANS, -fY )
   // BuildElementaryTransform( CAMERA, Z_TRANS, -fZ )
   // -- Apply rotation transformations
   // BuildElementaryTransform( CAMERA, Y_ROT, -theta )
   // BuildElementaryTransform( CAMERA, X_ROT, phi )
   // BuildElementaryTransform( CAMERA, Z_ROT, -alpha )
   // -- Apply perspective transformation
   // BuildElementaryTransform( CAMERA, PERSPECTIVE, r )
   // }

   //Apply translation transformations
   MYGL_DEFINE_ELEMENTARY_TRANSFORM(CAMERA_MATRIX, X_TRANSLATION, -fX);
   MYGL_PRINT_MATRIX(CAMERA_MATRIX); 
   
   MYGL_BUILD_ELEMENTARY_TRANSFORM(CAMERA_MATRIX, Y_TRANSLATION, -fY);
   MYGL_PRINT_MATRIX(CAMERA_MATRIX); 
   
   MYGL_BUILD_ELEMENTARY_TRANSFORM(CAMERA_MATRIX, Z_TRANSLATION, -fZ);
   MYGL_PRINT_MATRIX(CAMERA_MATRIX); 
   //Apply rotation transformations
   MYGL_BUILD_ELEMENTARY_TRANSFORM(CAMERA_MATRIX,Y_ROTATION,-theta); 
   MYGL_PRINT_MATRIX(CAMERA_MATRIX); 

   MYGL_BUILD_ELEMENTARY_TRANSFORM(CAMERA_MATRIX,X_ROTATION,phi); 
   MYGL_PRINT_MATRIX(CAMERA_MATRIX); 

   MYGL_BUILD_ELEMENTARY_TRANSFORM(CAMERA_MATRIX,Z_ROTATION,-alpha); 
   MYGL_PRINT_MATRIX(CAMERA_MATRIX); 

   //Apply perspective transformation
   MYGL_BUILD_ELEMENTARY_TRANSFORM(CAMERA_MATRIX,PERSPECTIVE,r); 
   MYGL_PRINT_MATRIX(CAMERA_MATRIX); 
}



/*********************************************
 * Function: MYGL_APPLY_TRANSFORM
 *
 * Description: applies a transformation to a point
 * 
 * Input: a vector of points(x,y,z) and active transformation matrix. 
*********************************************/
void MYGL_APPLY_TRANSFORM(std::vector<double> Vec3, double ACTIVE_TRANSFORM[NUM_ROWS][NUM_COLS])
{
   // procedure ApplyTransform (
   // (x, y, z) -- a point
   // aT -- active transform
   // (x’, y’, z’) -- returns transformed point )
   // {
   // (x, y, z) --> [x, y, z, 1] -- point to vector
   // Multiply [x y z 1] [aT] giving (x’’, y’’, z’’, h)
   // (h usually 1)
   // (x’, y’, z’) = (x’’, y’’, z’’)

   //point to vector
   Vec3.push_back(1); 

   //Multiply vector by our active transformation matrix
   MYGL_MULTIPLY(Vec3,ACTIVE_TRANSFORM); 
   
   //Vector to point
   Vec3.pop_back(); 

}


/*********************************************
 * Function: MYGL_DrawLine
 * Description: called by MYGL_DRAW_TO_3D, 
 *              draws a line. 
 * Input: GraphicsCanvas object, x1,y1,x2,y2 
 *        coordinates and color structure instance
*********************************************/
void MYGL_DrawLine(GraphicsCanvas& canvas, double x1, double y1, double x2, double y2, color color)
{
   std::cout<<"In drawLine\n"; 
   std::cout<<"x1: "<<x1<<" y1: "<< y1 <<" x2: "<<x2 << " y2: "<<y2<<"\n\n";

   int xTmp, yTmp;

   //horizontal
   if(y1 == y2)
   {
      if(x1 > x2)
      {
         xTmp = x1; 
         x1 = x2; 
         x2 = xTmp; 
      }

      for(auto i = x1; i <= x2; i++)
      {
         canvas.setColor(i,y1,color);
      }

      return;
   }

   //vertical
   else if(x1 == x2)
   {
      if(y1 > y2)
      {
         yTmp = y1; 
         y1 = y2;
         y2 = yTmp;
      }

      for(auto j = y1; j <= y2; j++)
      {
         canvas.setColor(x1,j,color);
      }

      return; 
   }

   double a = 1.0 * (y1 - y2) / (x1 - x2); //formula for slope
   double b = y1 - a * x1; // y-intercept
   
   for(double i = std::min(x1,x2); i < std::max(x1,x2); i += 1.0)
   {
      for(double j = std::min(y1,y2); j < std::max(y1,y2); j+= 1.0)
      {
         double x1_intercept = a * (i - 0.5) + b;
         double x2_intercept = a * (i + 0.5) + b;
         double y1_intercept = (j - b - 0.5) / a;
         double y2_intercept = (j - b + 0.5) / a;

         if(x1_intercept >= j - 0.5 && x1_intercept <= j + 0.5)
         {
            canvas.setColor(i,j,color); 
         }

         else if(x2_intercept >= j - 0.5 && x2_intercept <= j + 0.5)
         {
            canvas.setColor(i,j,color); 
         }

         else if(y1_intercept >= i - 0.5 && y1_intercept <= i + 0.5)
         {
            canvas.setColor(i,j,color); 
         }
         
         else if(y2_intercept >= i - 0.5 && y2_intercept <= i + 0.5)
         {
            canvas.setColor(i,j,color); 
         }
      }  
   }
}

/*********************************************
 * Function: MYGL_MULTIPLY_TRANSFORMS
 * Description: multiplys and concatenates matrices
 * Input: Two matrices to be multiplied together 
 *         and a matrix to store the result. 
*********************************************/
void MYGL_MULTIPLY_TRANSFORMS(double matrix_A[NUM_ROWS][NUM_COLS], double matrix_B[NUM_ROWS][NUM_COLS],double result[NUM_COLS][NUM_ROWS] )
{

   for(int i = 0; i < NUM_ROWS; i++)
   {
      for(int j = 0; j < NUM_COLS; j++)
      {
         result[i][j] = 0;

         for(int k = 0; k < NUM_ROWS; k++)
         {
            result[i][j] += matrix_A[i][k] * matrix_B[k][j]; 
         }
      }
   }

   //MYGL_PRINT_MATRIX(result); 
}

/*********************************************
 * Function: MYGL_MULTIPLY
 * Description: multiplys together a vector  
 *             and a 4x4 matrix. Stores result 
 *             back into the sent in vector. 
 * Input: A vector (x,y,z,1) and a 4x4
 *         active transformation matrix. 
 *********************************************/

void MYGL_MULTIPLY(std::vector<double>Vec3, double ACTIVE_TRANSFORM[NUM_ROWS][NUM_COLS])
{
   int result[NUM_COLS];

   for(int i = 0; i < NUM_ROWS; i++)
   {
      result[i] = 0; 

      for(int j = 0; j < NUM_COLS; j++)
      {
         result[i] += Vec3[i] * ACTIVE_TRANSFORM[i][j]; 
      }

      Vec3[i] = result[i]; 
   }
}

/*********************************************
 * Function: MYGL_PRINT_MATRIX
 * Description: prints a matrix (2D Array)
 * Input: Matrix (2D Array)
*********************************************/
void MYGL_PRINT_MATRIX(double matrix[NUM_ROWS][NUM_COLS])
{
   std::cout << "Matrix: \n"; 

   for(int i = 0; i < NUM_ROWS; i++)
   {
      for(int j = 0; j < NUM_COLS; j++)
      {
         std::cout << matrix[i][j] << " ";
      }
      std::cout << "\n";
   }

   std::cout << "\n"; 
}

/*********************************************
 * Function: MYGL_COPY_MATRIX
 * Description: copies matrix_A into matrix_B 
 * Input: two equal size matrices
*********************************************/
void MYGL_COPY_MATRIX(double matrix_A[NUM_ROWS][NUM_COLS],double matrix_B[NUM_ROWS][NUM_COLS])
{
   for(int i = 0; i < NUM_ROWS; i++)
   {
      for(int j = 0; j < NUM_COLS; j++)
      {
         matrix_B[i][j] = matrix_A[i][j]; 
      }
   }
}
