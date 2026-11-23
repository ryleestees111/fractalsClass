#include "FPToolkit.c"
#include "ryleeUtils.c"

void rotatePoint(double p[2], double newP[2]){
    double x = p[0];
    double y = p[1];
    newP[0] = (cos(30*(M_PI/180))*x) + (-sin(30*(M_PI/180))*y);
    newP[1] = (sin(30*(M_PI/180))*x) +(cos(30*(M_PI/180))*y);
}

int main(){
    srand(time(NULL));

    double height = 800.0;
    double width = 800.0;

    G_init_graphics(width, height);

    //clear the screen in a given color
    // G_rgb (165/255.0, 207/255.0, 85/255.0) ;
    drawRandomColorMaker();
    G_clear ();

    //OG POINTS
    double p1[2] = {420, 380};
    double p2[2] ={420, 420};
    double p3[2] ={380, 420};
    double p4[2] ={380, 380};

    myLine(p1[0], p1[1], p2[0], p2[1]);
    myLine(p2[0], p2[1], p3[0], p3[1]);
    myLine(p3[0], p3[1], p4[0], p4[1]);
    myLine(p4[0], p4[1], p1[0], p1[1]);
    G_wait_key();
    //move points top the origin
    double p1Origin[2];
    p1Origin[0] = 20;
    p1Origin[1] = -20;
    double p2Origin[2];
    p2Origin[0] = 20;
    p2Origin[1] = 20;
    double p3Origin[2];
    p3Origin[0] = -20;
    p3Origin[1]= 20;
    double p4Origin[2];
    p4Origin[0] = -20;
    p4Origin[1]= -20;

    myLine(p1Origin[0], p1Origin[1], p2Origin[0], p2Origin[1]);
    myLine(p2Origin[0], p2Origin[1], p3Origin[0], p3Origin[1]);
    myLine(p3Origin[0], p3Origin[1], p4Origin[0], p4Origin[1]);
    myLine(p4Origin[0], p4Origin[1], p1Origin[0], p1Origin[1]);

    //rotate around the origin
    rotatePoint(p1Origin, p1Origin);
    rotatePoint(p2Origin, p2Origin);
    rotatePoint(p3Origin, p3Origin);
    rotatePoint(p4Origin, p4Origin);

    myLine(p1Origin[0], p1Origin[1], p2Origin[0], p2Origin[1]);
    myLine(p2Origin[0], p2Origin[1], p3Origin[0], p3Origin[1]);
    myLine(p3Origin[0], p3Origin[1], p4Origin[0], p4Origin[1]);
    myLine(p4Origin[0], p4Origin[1], p1Origin[0], p1Origin[1]);

    //bring it back to the origin
    p1[0] = p1Origin[0] + 400;
    p1[1] = p1Origin[1] + 400;
    p2[0] = p2Origin[0] + 400;
    p2[1] = p2Origin[1] +400;
    p3[0] = p3Origin[0]+400;
    p3[1] = p3Origin[1]+400;
    p4[0] = p4Origin[0]+400;
    p4[1] = p4Origin[1]+400;

    myLine(p1[0], p1[1], p2[0], p2[1]);
    myLine(p2[0], p2[1], p3[0], p3[1]);
    myLine(p3[0], p3[1], p4[0], p4[1]);
    myLine(p4[0], p4[1], p1[0], p1[1]);    




    //so that the window doesn't close
    G_wait_key();
}