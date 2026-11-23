#include "FPToolkit.c"
double x=0;
double y=0;

void translate(double dX, double dY){
    x=x+dX;
    y=y+dY;
}

void scale(double sX, double sY){
    x=x*sX;
    y=y*sY;
}

void rotate(double degrees){
    double rad;
    double temp;
    double c;
    double s;
    rad = degrees*(M_PI/180.0);
    c=cos(rad);
    s=sin(rad);

    temp=(c*x)-(s*y);
    y=(s*x)+(c*y);
    x=temp;
}


int main(){

    double height = 800.0;
    double width = 800.0;
    G_init_graphics(width, height);
    //clear the screen in a given color
    G_rgb (0/255.0, 0/255.0, 0/255.0) ;
    // drawRandomColorMaker();
    G_clear ();

    int r=0;
    for(int i=0; i<10000000; i++){
        r=floor(5*drand48());
        //diagonal line
        // if(r==0){
        //     scale(0.5, 0.5);
        // }
        // else if (r==1){
        //     scale(0.5, 0.5);
        //     translate(0.5, 0.5);
        // }

        //sierpinski triangle
        // if(r==0){
        //     scale(0.5, 0.5);
        // }
        // else if(r==1){
        //     scale(0.5, 0.5);
        //     translate(0.5, 0);
        // }
        // else if(r==2){
        //     scale(0.5, 0.5);
        //     translate(0, 0.5);
        // }
        // // else{
        // //     scale(0.5, 0.5);
        // //     translate(0.5, 0.5);

        // // }

        //trying koch curve
        if(r==0){
            scale(1.0/3, 1.0/3);
        }
        else if(r==1){
            scale(1.0/3, 1.0/3);
            rotate(60);
            translate(1.0/3, 0);
        }
        else if(r==2){
            scale(1.0/3, 1.0/3);
            rotate(300);
            translate(0.5, 0.289);
        }
        else if(r==3){
            scale(1.0/3, 1.0/3);
            translate(2.0/3, 0);
        }
        G_rgb(123/255.0,245/255.0,99/255.0);

        G_point(800*x,800*y);

    }
    G_wait_key();

    
}