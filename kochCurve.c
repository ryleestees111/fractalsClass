#include "FPToolkit.c"
#include "ryleeUtils.c"

void kochCurve(double p1[2], double p2[2], int depth){
    //grab two points and create a koch curve from that 
    double p3[2];
    double p4[2];
    double p5[2];
    double p6[2];
    double p7[2];

    if(depth ==0){
        myLine(p1[0], p1[1], p2[0], p2[1]);
        return;
    }
    else{
        //make a right triangle out of the two original points
        p5[0] = p2[0];
        p5[1]= p1[1];

        //find the length of the straight lines of that triangle
        double height = p5[1]-p2[1];
        double length = p5[0]-p1[0];
        double smallTriHeight = height/3;
        double smallTriLength = length/3;
        
        p3[0] = p1[0]+(smallTriLength);
        p3[1] = p5[1]-(smallTriHeight);
        p4[0] = p3[0]+ (smallTriLength);
        p4[1] = p3[1]-(smallTriHeight);

        //line from p3 to p4
        double px = p4[0]-p3[0];
        double py = p4[1]-p3[1];

        //rotate it 90 degrees
        double perpendicularPx = -py;
        double perpendicularPy = px;

        //shorten the middle line
        px = perpendicularPx*0.866;
        py = perpendicularPy*0.866;
        findMidpointOfLine(p3, p4, p7);
        p6[0] = p7[0]+px;
        p6[1] = p7[1]+py;

        kochCurve(p1, p3, depth-1);
        kochCurve(p3, p6, depth-1);
        kochCurve(p6, p4, depth-1); 
        kochCurve(p4, p2, depth-1);
    }

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

    //wait for the user to select two points 
    double P1[2];
    double P2[2];
    G_wait_click(P1);
    G_wait_click(P2);
    int depth =0;
    //values from waitkey come back as ascii so need to subtract '0' which is 48 in ascii
    depth = G_wait_key() - '0'; 
    kochCurve(P1, P2, depth);

    //so that the window doesn't close
    G_wait_key();

}