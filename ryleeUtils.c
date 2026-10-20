#include <stdio.h>
#include <math.h>
#include <stdlib.h> // drand48, atoi
#include <unistd.h> // usleep
#include <time.h> // for the get_time stuff
#include <sys/time.h> 
#include <string.h> // for strlen

void drawRandomColorMaker(){
        int N=255;
        int colorVal1 = rand() % (N + 1);
        int colorVal2 = rand() % (N + 1);
        int colorVal3 = rand() % (N + 1);

        G_rgb(colorVal1/255.0,colorVal2/255.0,colorVal3/255.0);
    
}

void myLine(double x0, double y0, double x1, double y1){
    
    double t=0;
    drawRandomColorMaker();
    while(t<=1){
        double differenceX = x1-x0;
        double differenceY = y1-y0;
        double x=x0+t*(differenceX);
        double y=y0+t*(differenceY);
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

void makeSquareFromTwoPoints(double p1[2], double p2[2]){
    //take the two points and calculate what the next two points need to
    //be created so that we make a perfect square

    double p3[2];
    p3[0] = p1[0];
    p3[1] = p2[1];

    //find the length of the straight lines on the triangle
    double height= p3[1]-p1[1];
    double length= p2[0]-p3[0];

    double p4[2];
    p4[0] = p2[0]-height;
    p4[1] = p2[1]+length;
    
    double p5[2];
    p5[0] = p1[0]-height;
    p5[1] = p4[1]-height;

    //draw the square
    myLine(p1[0], p1[1], p2[0], p2[1]);
    myLine(p2[0], p2[1], p4[0], p4[1]);
    myLine(p4[0], p4[1], p5[0], p5[1]);
    myLine(p5[0], p5[1], p1[0], p1[1]);
}

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
    //to see the lines created in order
    // G_wait_key();
}
