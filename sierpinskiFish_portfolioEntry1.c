#include "FPToolkit.c"
/*

       Y+
       |
       |    * (y,z)
       |  
<------+--------Z+
   D   |
       |
       |



with the x-axis perpendicular to this plane.

*/

#define M 700000
#define CENTER 3      //how far back the circle is
#define RADIUS 2      //how big the circle is
#define NUM_BUBBLES 30
#define MOVIE_FRAMES 180  //2 degrees a frame, so 180 frames is one full lap around the circle
double bx[NUM_BUBBLES], by[NUM_BUBBLES], br[NUM_BUBBLES], bspeed[NUM_BUBBLES] ;
double Wsize = 1000  ; //window size ... choose 600 for repl
double X[M],Y[M],Z[M] ;
double Xplot[M],Yplot[M] ;
int N = 0 ;

//fills in one bubble one row at a time, fading from the bottom color to the top color
void drawGradientBubble(double cx, double cy, double r)
{
  double topColor[3]    = {246/255.0, 100/255.0, 238/255.0} ; //pink
  double bottomColor[3] = {245/255.0, 239/255.0, 244/255.0} ; //almost white

  double dy ;
  for (dy = -r ; dy <= r ; dy++) {
    //how wide the bubble is at this height (pythagoras: w^2 + dy^2 = r^2)
    double w = sqrt(r*r - dy*dy) ;

    //t goes from 0 at the bottom of the bubble to 1 at the top
    double t = (dy + r)/(2*r) ;
    G_rgb(bottomColor[0] + t*(topColor[0]-bottomColor[0]),
          bottomColor[1] + t*(topColor[1]-bottomColor[1]),
          bottomColor[2] + t*(topColor[2]-bottomColor[2])) ;
    G_line(cx - w, cy + dy, cx + w, cy + dy) ;
  }
}

void makeBubbles()
{
  int i ;
  for (i = 0 ; i < NUM_BUBBLES ; i++) {
    bx[i] = drand48()*Wsize ;
    by[i] = drand48()*Wsize ;
    br[i] = 3 + drand48()*10 ;        //radius from 3 to 13
    bspeed[i] = 1 + drand48()*3 ;     //speed from 1 to 4 pixels per frame
  }
}
void drawBubbles(int frame)
{
  int i ;
  for (i = 0 ; i < NUM_BUBBLES ; i++) {
    by[i] += bspeed[i] ;

    //floated off the top? start over at the bottom
    if (by[i] > Wsize + br[i]) {
      by[i] = -br[i] ;
      bx[i] = drand48()*Wsize ;
    }

    //wobble (the + i makes each bubble wobble at a different time)
    double wobble = sin(frame*0.1 + i) * 3 ;
    double x = bx[i] + wobble ;

    //fill it in with the gradient first, then draw the outline on top
    drawGradientBubble(x, by[i], br[i]) ;
    G_rgb(1, 1, 1) ;
    G_circle(x, by[i], br[i]) ;
  }
}
void translate(double dx, double dy, double dz) 
{
  int i ;

  for (i = 0 ; i < N ; i++) {
    X[i] += dx ;
    Y[i] += dy ;
    Z[i] += dz ;    
  }
}

void scale(double s)
{
  int i ;

  for (i = 0 ; i < N ; i++) {
    X[i] *= s ;
    Y[i] *= s ;
    Z[i] *= s ;
  }
}

void rotate_y(double degrees)
// X[] and Z[] will change but Y[] will be unchanged
{
  double radians,c,s,temp ;
  int i ;
  
  radians = degrees*M_PI/180 ;
  c = cos(radians) ;
  s = sin(radians) ;
  for (i = 0 ; i < N ; i++) {
    temp =  c*X[i] + s*Z[i] ;
    Z[i] = -s*X[i] + c*Z[i] ;
    X[i] = temp ;
  }
}

void project(double observer_distance, double halfangle_degrees)
{
  double D = observer_distance ;
  double ha = M_PI*halfangle_degrees/180.0 ;
  //how much to scale things up so they fill the window (same for every point so only figure it out once)
  double scale = 0.5*Wsize/tan(ha) ;

  int i ;
  for (i = 0 ; i < N ; i++) {
    //things farther away (bigger Z) get divided by more so they look smaller
    Xplot[i] = scale*X[i]/(D+Z[i]) + 0.5*Wsize ;
    Yplot[i] = scale*Y[i]/(D+Z[i]) + 0.5*Wsize ;
  }
}

void draw()
{
  int i ;
  for (i = 0 ; i < N ; i=i+2) {
    G_line(Xplot[i],Yplot[i],  Xplot[i+1],Yplot[i+1]) ;
  }
}

void save_line(double xs, double ys, double zs,
               double xe, double ye, double ze)
{
  // about to add items at slots N and N+1 :
  if (N+1 >= M) {
    printf("full\n") ;
    return ;
  }
  
  X[N] = xs ; Y[N] = ys ; Z[N] = zs ; N++ ;
  X[N] = xe ; Y[N] = ye ; Z[N] = ze ; N++ ;
}

//same as findMidpointOfLine but with z too
void midpoint3D(double p1[3], double p2[3], double result[3])
{
  result[0] = (p1[0]+p2[0])/2 ;
  result[1] = (p1[1]+p2[1])/2 ;
  result[2] = (p1[2]+p2[2])/2 ;
}

//same idea as drawSierpinskiTriangle but in 3D, and it saves the lines instead of drawing them
void sierpinski3D(int depth, double p1[3], double p2[3], double p3[3])
{
  if (depth == 0) {
    return ;
  }

  //save the 3 edges of this triangle
  save_line(p1[0],p1[1],p1[2],  p2[0],p2[1],p2[2]) ;
  save_line(p2[0],p2[1],p2[2],  p3[0],p3[1],p3[2]) ;
  save_line(p3[0],p3[1],p3[2],  p1[0],p1[1],p1[2]) ;

  double m1[3], m2[3], m3[3] ;
  midpoint3D(p1, p2, m1) ;
  midpoint3D(p2, p3, m2) ;
  midpoint3D(p3, p1, m3) ;

  sierpinski3D(depth-1, m1, m3, p1) ;
  sierpinski3D(depth-1, m1, m2, p2) ;
  sierpinski3D(depth-1, m2, m3, p3) ;
}

/*
  side view (x and y), the fish faces +x:

        dorsalTip
           \
     tailTop  \   top
        \  dorsalBase   \
   tailNotch --- tailEnd ------------- nose
        /                       /
     tailBot             bottom

  left and right are on the sides of the body (+z and -z) at the same x as top/bottom.
  the fish is kept skinny in z, and centered around (0,0,0) so it spins in place
*/
void buildFish(int depth)
{
  N = 0 ; // global

  //body
  double nose[3]      = { 1.2,  0.0,  0.0} ;
  double top[3]       = { 0.1,  0.6,  0.0} ;
  double bottom[3]    = { 0.1, -0.5,  0.0} ;
  double left[3]      = { 0.1,  0.0,  0.3} ;
  double right[3]     = { 0.1,  0.0, -0.3} ;
  double tailEnd[3]   = {-0.8,  0.0,  0.0} ;

  //tail fin
  double tailTop[3]   = {-1.4,  0.5,  0.0} ;
  double tailNotch[3] = {-1.15, 0.0,  0.0} ;
  double tailBot[3]   = {-1.4, -0.5,  0.0} ;

  //fin on the back, sits on the line from top to tailEnd
  double dorsalBase[3] = {-0.35, 0.3, 0.0} ;
  double dorsalTip[3]  = {-0.55, 0.85, 0.0} ;

  //little side fins sticking out and back from left and right
  double leftFinTip[3]  = {-0.2, -0.3,  0.6} ;
  double leftFinBase[3] = { 0.4, -0.1,  0.2} ;
  double rightFinTip[3]  = {-0.2, -0.3, -0.6} ;
  double rightFinBase[3] = { 0.4, -0.1, -0.2} ;

  //front half of the body: nose to the ring of 4 points
  sierpinski3D(depth, nose, top, left) ;
  sierpinski3D(depth, nose, left, bottom) ;
  sierpinski3D(depth, nose, bottom, right) ;
  sierpinski3D(depth, nose, right, top) ;

  //back half of the body: the ring of 4 points to tailEnd
  sierpinski3D(depth, tailEnd, top, left) ;
  sierpinski3D(depth, tailEnd, left, bottom) ;
  sierpinski3D(depth, tailEnd, bottom, right) ;
  sierpinski3D(depth, tailEnd, right, top) ;

  //tail (2 triangles so it has a notch in it)
  sierpinski3D(depth, tailEnd, tailTop, tailNotch) ;
  sierpinski3D(depth, tailEnd, tailNotch, tailBot) ;

  //fins
  sierpinski3D(depth, top, dorsalBase, dorsalTip) ;
  sierpinski3D(depth, left, leftFinBase, leftFinTip) ;
  sierpinski3D(depth, right, rightFinBase, rightFinTip) ;
}

//fills the screen one row at a time, fading from dark blue at the bottom to light blue at the top
void drawGradientOceanBackground()
{
  double topColor[3]    = {  0/255.0, 207/255.0, 255/255.0} ; //light blue
  double bottomColor[3] = {  0/255.0,  30/255.0,  80/255.0} ; //deep ocean blue

  int y ;
  for (y = 0 ; y < Wsize ; y++) {
    //t goes from 0 at the bottom to 1 at the top (same t idea as myLine)
    double t = y/Wsize ;
    G_rgb(bottomColor[0] + t*(topColor[0]-bottomColor[0]),
          bottomColor[1] + t*(topColor[1]-bottomColor[1]),
          bottomColor[2] + t*(topColor[2]-bottomColor[2])) ;
    G_line(0, y, Wsize-1, y) ;
  }
}
void swimFish()
{
  G_init_graphics(Wsize,Wsize) ;

  buildFish(5) ;
  scale(1.5);
  //put the fish on the edge of the circle, then push the whole circle back away from the camera
  translate(0, 0, RADIUS+CENTER) ;

  int frame = 0 ;
  makeBubbles();
  while (1) {
    drawGradientOceanBackground() ;
    G_rgb(255/255.0, 0/255.0, 214/255.0) ;
    project(3,45) ;
    draw() ;
    drawBubbles(frame);
    //swim 2 degrees around the circle: move the circle's center to the origin, rotate, move it back
    //(the sin part makes it bob up and down a little while it swims)
    translate(0, 0, -CENTER) ;
    rotate_y(2) ;
    translate(0, sin(frame*0.05)*0.05, CENTER) ;

    if (G_wait_key() == 'q') { break ; }

    //save this frame as a numbered picture for the movie (fish0000.bmp, fish0001.bmp, ...)
    char fname[200] ;
    sprintf(fname, "fishMovie/fish%04d.bmp", frame) ;
    G_save_to_bmp_file(fname) ;

    frame++ ;
    if (frame == MOVIE_FRAMES) { break ; }
  }
}

int main()
{
  swimFish() ;
}
