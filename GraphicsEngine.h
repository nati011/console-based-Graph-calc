//This is a graphics engine for the console. It enables the use of the terminal as a graphics display.
#ifndef GRAPHICSENGINE_H_INCLUDED
#define GRAPHICSENGINE_H_INCLUDED



#endif // GRAPHICSENGINE_H_INCLUDED


//Automatically generated Guard word to define the header file for the project
#ifndef GRAPHICSENGINE_H_INCLUDED
#define GRAPHICSENGINE_H_INCLUDED
#endif // GRAPHICSENGINE_H_INCLUDED

#include"MathParser.h"
#include <math.h>
#include <iostream>
#include <windows.h>
#include <wchar.h>
#include <string.h>

using namespace std;

//This functions rounds up rational numbers
double round(double);

//prototypes of all the functions
//disp() displays the output and houses the call of the WriteConsoleOutputCharacterW() Windows API function
void disp();

//The draw() function populates the screen buffer that sits behind the console
void draw(int , wchar_t);
//This overloaded function accepts only one value instead of x and y coordinates
void draw(int, wchar_t);

//The draw_block() function is a derivative of the draw() function.
void draw_block(int, int, int, int, wchar_t);

//This function prepares the output console by setting the windows API parameters
void prepare_console_output(float width, float height, float font, float);

//This function draws graphs
//Input: The function to be plotted
//     : The left limit of the graph to be displayed
//     : The upper limit of the graph to be displayed
//     : The right limit of the graph to be displayed
//     : The lower limit of the graph to be displayed

void graph();//string);

// screen resolution, cell size
const int res_x = 151;
const int res_y = 151;


// We prepare a screen that sits behind the console.
// We make changes to it, to display and to update the output.
wchar_t *screen= new wchar_t[res_x*res_y];

// Create Output console screen buffer and set handle to it as a readable, writable space of type wchar_t
HANDLE hconsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE ,0 ,NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

//dw  is a variable of type DWORD. it's used as an argument for the WriteConsoleOutputCharacterW() windows API function
//and to be supplied in the function call it needs to first be declared and initialized
DWORD dw=0;


void disp()
{
    //This windows API function enables us to use the console as a Graphics display.
    //The std::cout function does not enable a fast screen update.
    //There are redundancies and delays which make it unideal for such an application.
    //It is to solve these problems that we take handle of the buffer directly and populate it after which we can display it at ones.
    WriteConsoleOutputCharacterW(hconsole, screen, res_x*res_y,{0,0}, &dw);
}
void draw(int y, int x, wchar_t ch)
{
    //The draw function does the simplest and most fundamental of operations one can perform on the screen buffer that sits behind the console
    if(x >= 0 && x < res_x && y >= 0 && y < res_y)
    {
        //since screen[] is a one dimensional array we index elements by using the formula (position of y * width of x + position of x)
        screen[y * res_x +x] = ch;
    }
}
void draw(int i, wchar_t ch)
{
    //The draw function does the simplest and most fundamental of operations one can perform on the screen buffer that sits behind the console
    if(i > 0 && i < (res_x*res_y) )
    {
        //since screen[] is a one dimensional array we index elements by using the formula (position of y * width of x + position of x)
        screen[i] = ch;
    }
}
void draw_block(int x0, int y0, int xf, int yf, wchar_t ch)
{
    //To draw a block we accept x0, y0, xf and yf and shade all units with character ch by making use of the previously defined draw function

    for(int i=y0; i<=yf; i++)
    {
        for(int j=x0; j<=xf; j++)
            draw(j, i, ch);
    }
}

void prepare_console_output(float width, float height, float font_x, float font_y)
{
    //obtain the largest possible size of the buffer handle and store it inside the COORD type structure.
    //x and y are stored in big.X and big.Y, respectively.
    COORD big = GetLargestConsoleWindowSize(hconsole);

    //Prepare console only if width and height values are valid
    if(width < big.X && width > 0 && height < big.Y && height > 0)
    {
        //make the hconsole handle into an output stream
        hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

        //set the windows API parameters
        CONSOLE_FONT_INFOEX cfi;

        //set size
        cfi.cbSize = sizeof(cfi);
        cfi.nFont=0;

        //set font size to user supplied values width and height
        cfi.dwFontSize.X=width;
        cfi.dwFontSize.Y=height;

        //set Font
        cfi.FontFamily = FF_DECORATIVE;
        cfi.FontWeight = FW_NORMAL;

        //Set console window name
        wcscpy(cfi.FaceName, L"Graph calculator");

    //buffer is a size descriptor of type COORD
    COORD buffer = {(short)width, (short)height};

    //The set console screen buffer size function is a windows API function that sets the buffer size of hconsole
    SetConsoleScreenBufferSize(hconsole, buffer);
    //          !
    SMALL_RECT m_rectWindow = {0,0,(short)width-1, (short)height-1};
    //The set console screen buffer size function is a windows API function that sets the windows size of hconsole
    SetConsoleWindowInfo(hconsole, TRUE, &m_rectWindow);
    }
}

double round(double number)
{
  //round the value accepted from number and return it's value
  return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}

int round_int(double number)
{
  //round the value accepted from number and return it's value
  return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}

void graph()//string expression_store)
{
    //Set size of graph, size of x, size of y, size of -x and size of -y
    //The graph will have the same size of x, -x, y, -y
  int size = 75;
    //Since the cell density of our console is limited we need to rescale the graph so that it can be plotted.
    //the step variable sets the relationship between a unit cell and a length on graph
  double step  = (1.0/40);
    //This array stores y elements of size size_of+size_of+1
  int *values = new int[size+size+1];
  //This  variable stores the computed results in values
  double value, x;
  //populate each elements of values[] by calculating the corresponding y components
  for(int i = 0;i< size+size+1;++i)
 {
    //since value starts from left most(2nd quadrant) x is negative
    x = (i - (size));
    //x needs to be multiplied with step
    x = x*step;

    // EQUATION
    //change the value x into a string and store it in val so that it can be used in the next operation
    //string val = to_string((x));
    //value = Evaluate(substitute(expression_store, 'x', x));
    value = log(x);
    //y = f(x)
    //Reduce and Eliminate fraction part by rounding by making use of our own round() function
    //this is to stretch our screen vertically
    value = value/step;
    values[i] = round(value);
  }
/*      The graph is broken up into each quadrants and drawn separately.
       This method is cultivated for the sake of convenience We start plotting
       from the left most cell of our memory space and proceed by following
       the elementary cursor movement of the console- (i.e from left to right and top to bottom).

    Draw upper half of the the graph

        [x] [x]
        [ ] [ ]

    */
  for(int i=0; i<=size; i++)
  {

       /*
            Draw the second quadrant of the graph
                    [x][ ]
                    [ ][ ]
        */
        //if graph value found populate the screen buffer by the bottom half block wchar_t symbol
        //else mark empty cell with '.' character
        for(int j = 0; j < size+1; j++)
      {

         if(size - i == values[j])
            //screen[i][j] = char(220);
            draw(i,j, 0x2588);
         else
            //screen[i][j] = L'.';
            draw(i,j, L'.');

      }

       //draw positive y axis
       if(size -i != values[size])
            //screen[i][size] = char(177);
            draw(i,size,0x2592);

 /*
        Draw the first quadrant
                    [ ][x]
                    [ ][ ]
        */
        //same as before, if graph value found populate the screen buffer by the bottom half block wchar_t symbol
        //else mark empty cell with '.' character
      for(int k = size+1; k < size+size+1;++k)
      {
        if(size - i == values[k+1])
           //screen[i][k] = char(220);
           draw(i,k,0x2588);
        else
           //screen[i][k] = L'.';
           draw(i,k,L'.');
      }

  }
  //Draw x axis

    for(int i = 0;i < size+size+1;++i)
    {
        if( 0 != values[i] )
           //screen[size][i] = char(177);
           draw(size, i, 0x2592);

    }

 //Draw lower half of the the graph
    /*
        [ ] [ ]
        [x] [x]

    */
   for(int i = size+1;i < size+size+1;++i)
    {
        /*
         Draw the third quadrant
                    [ ][ ]
                    [x][ ]
        same as before, if graph value found populate the screen buffer by the bottom half block wchar_t symbol
        else mark empty cell with '.' character
        */
        for(int b = 0; b < size+1;++b)
        {
            if((0-i+size) == values[b])
               //screen[i][b] = char(220);
                draw(i,b,0x2588);
            else
                //screen[i][b] = L'.';
                draw(i,b,L'.');
        }
        if((0-i+size) != values[size])
            //screen[i-1][size] = char(177);
            draw(i-1,size, 0x2592);

   /*
         Draw the fourth quadrant
                    [ ][ ]
                    [ ][x]
        same as before, if graph value found populate the screen buffer by the bottom half block wchar_t symbol
        else mark empty cell with '.' character
        */

        for(int k = size; k < size+size+1;k++)
        {
            if((0-i+size) == values[k+1])
                //screen[i][k] = char(220);
                draw(i,k,0x2588);
            else
                //screen[i][k] = L'.';
                draw(i,k,L'.');
        }

    }

}
