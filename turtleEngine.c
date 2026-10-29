#include "FPToolkit.c"
#include "ryleeUtils.c"

//no starting value here so the exe doesn't get huge, the string gets copied in in main
char u[100000000];

void stringInterpreter(){
    //initialize turtle
    double turtle[2] = {300, 300};
    double tDir = 0;
    double f = 30.0;
    double rotation = 60.0;

    //interpret string u one character at a time. 
    int i=0;
    while (u[i] != '\0'){
        switch(u[i]){
            case 'f': {
                //move forward f in the direction the turtle is facing
                //(cos, sin) is the direction, times f to scale it up, then add the turtle's spot
                double txTemp = turtle[0];
                double tyTemp = turtle[1];
                turtle[0] = turtle[0] + f*cos(tDir*(M_PI/180));
                turtle[1] = turtle[1] + f*sin(tDir*(M_PI/180));
                myLine(txTemp, tyTemp, turtle[0], turtle[1]);
                break;
            }
            case '+':
                //turn counter clockwise by 'rotation', the turtle doesn't move
                tDir = tDir + rotation;
                break;
            case '-':
                //turn clockwise by 'rotation', the turtle doesn't move
                tDir = tDir - rotation;
                break;
            default:
                //do nothing
                break;
        }
        i++;
    }
}

int main(){
    srand(time(NULL));

    double height = 800.0;
    double width = 800.0;

    G_init_graphics(width, height);

    //clear the screen in a given color
    G_rgb (165/255.0, 207/255.0, 85/255.0) ;
    // drawRandomColorMaker();
    G_clear ();

    strcpy(u, "fff+f++ff-f");
    // strcpy(u, "ff+ff+ff+f");

    stringInterpreter();

    //so that the window doesn't close
    G_wait_key();
}
