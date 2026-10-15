#include "FPToolkit.c"


void myLine(double x0, double y0, double x1, double y1){
    
    double t=0;
    while(t<=1){
        double differenceX = x1-x0;
        double differenceY = y1-y0;
        double x=x0+t*(differenceX);
        double y=y0+t*(differenceY);

        G_rgb(192/255.0,140/255.0,230/255.0);
        G_point(x,y);
        double unsignedDiffX = fabs(differenceX);
        double unsignedDiffY = fabs(differenceY);
        if(unsignedDiffX >unsignedDiffY){
            t=t+(1.0/unsignedDiffX);
            
        }
        else{
            t=t+(1/unsignedDiffY);
                }
    }
}

void drawOneTriangle(double p1[2], double p2[2], double p3[2]){
    myLine(p1[0], p1[1], p2[0], p2[1]);
    myLine(p2[0], p2[1], p3[0], p3[1]);
    myLine(p3[0], p3[1], p1[0], p1[1]);
}

void findMidpointOfLine(double p1[2], double p2[2], double result[2]){
     result[0] = (p1[0]+p2[0])/2;
     result[1] = (p1[1]+p2[1])/2;
}

// void drawTriangle(double p1[2], double p2[2], double p3[2], int depth){


//     G_rgb(0.0, 1.0, 0.0); 
//     G_triangle(p1[0], p1[1], p2[0], p2[1], p3[0], p3[1]);


//     int d=0;
//     if(d=depth){
//         //stop, end case
//         return;
//     }
//     else{
//         double newP1[2];
//         newP1[0] = p1[0]/2;
//         newP1[1] = p1[1]/2;
//         double newP2[2];
//         newP2[0] = p2[0]/2;
//         newP2[1] = p2[1]/2;
//         double newP3[2];
//         newP3[0] = p3[0]/2;
//         newP3[1] = p3[1]/2;
//         drawTriangle(newP1, newP2, newP3, d+1);
//     }
// }

void drawSierpinskiTriangle(int depth, double p1[2], double p2[2], double p3[2]){
    // printf("depth at beginning = %d\n", depth);

    if(depth==0){
        // printf("Got in return");
        return;
    }
    else{
        drawOneTriangle(p1, p2, p3);
        double midPoint1[2];
        findMidpointOfLine(p1, p2, midPoint1);
        double midPoint2[2];
        findMidpointOfLine(p2, p3, midPoint2);
        double midPoint3[2];
        findMidpointOfLine(p3, p1, midPoint3);
        drawSierpinskiTriangle(depth-1, midPoint1, midPoint3, p1);
        drawSierpinskiTriangle(depth-1, midPoint1, midPoint2, p2);
        drawSierpinskiTriangle(depth-1, midPoint2, midPoint3, p3);
        // printf("depth in else = %d\n", depth);
    }
}

//need to make a triangle based off of user input and then maybe with each click do more depth?
int main(){
    double height = 800.0;
    double width = 800.0;

    G_init_graphics(width, height);

    // clear the screen in a given color
    G_rgb (165/255.0, 207/255.0, 85/255.0) ; // dark gray
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