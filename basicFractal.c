#include "FPToolkit.c"
#include "ryleeUtils.c"


int main(){
    srand(time(NULL));

    double height = 800.0;
    double width = 800.0;

    G_init_graphics(width, height);

    //clear the screen in a given color
    // G_rgb (165/255.0, 207/255.0, 85/255.0) ;
    drawRandomColorMaker();
    G_clear () ;

    double P1[2] ;
    double P2[2] ;
    double P3[2] ;
    G_wait_click(P1);
    G_wait_click(P2);
    G_wait_click(P3);
    int depth =0;
    //values from waitkey come back as ascii so need to subtract '0' which is 48 in ascii
    depth = G_wait_key() - '0'; 

    drawSierpinskiTriangle(depth, P1, P2, P3);




    //so that the window doesn't close
    G_wait_key();

}