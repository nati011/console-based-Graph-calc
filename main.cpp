//This is the graph calculator
#include "GraphicsEngine.h"
#include <string>

void draw_window();

void draw_graph();

void plot();//string);
//Prompt user, take input and plot graph
int main()
{
    //string expression_store;
    //cout<<"Enter Expression:";
    //getline(cin, expression_store);

    plot();//expression_store);
}
void plot()//string expression_store)
{

        //Prepare the output console
        prepare_console_output(151,151,0,0);
        //draw graph
        graph();
        //expression_store);

        draw_window();

        // Activate/ use the prepared hconsole
        SetConsoleActiveScreenBuffer(hconsole);
        //Set the console window name to Graph calculator
        SetConsoleTitle("Graph calculator");
        //Game loop
        while(true)
        {
            //display the prepared screen
            disp();
        }


}
//This function draws on the screen buffer by making use of the draw_block function is defined in the graphics engine
void draw_window()
{
    //draw boarder
    draw_block(1,1,1,149,0x2588);
    draw_block(1,1,149,1,0x2588);
    draw_block(149,1,149,149,0x2588);
    draw_block(1,149,149,149,0x2588);
}

