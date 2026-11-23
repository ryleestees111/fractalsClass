#include "FPToolkit.c"
#include "ryleeUtils.c"

//how big the strings are allowed to get
#define STRING_SIZE 100000000

//no starting value here so the exe doesn't get huge
char u[STRING_SIZE];
//scratch space for building the next string (can't build u while we're reading it)
char temp[STRING_SIZE];

//everything that describes one l-system
char axiom[100];
double rotation;
//the rule for each character, looked up by the character itself (ex: rules['A'] is A's rule)
//characters without a rule are just an empty string
char rules[128][100];

//how far the turtle went in each direction, filled in by stringInterpreter
double minX, maxX, minY, maxY;

double xStack[100];
double yStack[100];
double angleStack[100];

void squareWave()
{
    strcpy(axiom, "A");
    rotation = 90.0;
    strcpy(rules['A'], "f-f-B");
    strcpy(rules['B'], "f+f+A");
}

void kochCurveLSystem()
{
    strcpy(axiom, "f");
    rotation = 60.0;
    strcpy(rules['f'], "f+f--f+f");
}

void pushAndPop(){
    strcpy(axiom, "A");
    rotation = 22.5;
    strcpy(rules['A'], "F-[[A]+A]+F[+FA]-A");
    strcpy(rules['F'], "FF");
}

//start with the axiom, then do the replacements 'depth' times
void stringBuilder(int depth)
{
    strcpy(u, axiom);

    int d = 0;
    while (d < depth){
        int i = 0; //where we are in u (reading)
        int j = 0; //where we are in temp (writing)
        while (u[i] != '\0'){
            char *rule = rules[(int)u[i]];
            if (rule[0] == '\0'){
                //no rule for this character so just copy it over
                temp[j] = u[i];
                j++;
            }
            else{
                //swap the character out for its rule
                if (j + strlen(rule) >= STRING_SIZE){
                    //out of room, u still has the last finished string so just use that
                    printf("string got too big, stopping at depth %d\n", d);
                    return;
                }
                strcpy(&temp[j], rule);
                j = j + strlen(rule);
            }
            i++;
        }
        temp[j] = '\0';
        strcpy(u, temp);
        d++;
    }
}

//walks the turtle through u. if draw is 0 it just measures how big the drawing is
void stringInterpreter(double x, double y, double f, int draw)
{
    double tDir = 0;

    minX = maxX = x;
    minY = maxY = y;

    //interpret string u one character at a time. 
    int i=0;
    int sp = 0;
    while (u[i] != '\0'){
        if (u[i] == 'f' || u[i] >='A' && u[i] <='Z'){
            //move forward f in the direction the turtle is facing
            double newX = x + f*cos(tDir*(M_PI/180));
            double newY = y + f*sin(tDir*(M_PI/180));
            if (draw){
                // G_wait_key();
                myLine(x, y, newX, newY);
            }
            x = newX;
            y = newY;

            //keep track of the edges of the drawing
            minX = fmin(minX, x);
            maxX = fmax(maxX, x);
            minY = fmin(minY, y);
            maxY = fmax(maxY, y);
        }
        else if (u[i] == '+'){
            //turn counter clockwise
            tDir = tDir + rotation;
        }
        else if (u[i] == '-'){
            //turn clockwise
            tDir = tDir - rotation;
        }
        else if (u[i] == '['){
            //push current location to stack
            sp++;
            xStack[sp] = x;
            yStack[sp] = y;
            angleStack[sp] = tDir;
        }
        else if (u[i] == ']'){
            //pop from top of stack and move back to the previous location
            x=xStack[sp];
            y=yStack[sp];
            tDir=angleStack[sp];
            sp--;
        }
        //anything else (like A and B) is just for building the string so the turtle ignores it
        i++;
    }
}

//figures out the step size and starting spot so the drawing fills the screen and is centered
void autoPlacer(double width, double height)
{
    //1st pass: start at (0,0) with a step size of 1 and don't draw, just measure
    stringInterpreter(0, 0, 1, 0);

    //scale it up to fill 90% of the screen, using whichever direction runs out of room first
    double scale = fmin(0.9*width / (maxX - minX), 0.9*height / (maxY - minY));

    //move the center of the drawing to the center of the screen
    double startX = width/2 - scale*(minX + maxX)/2;
    double startY = height/2 - scale*(minY + maxY)/2;

    //2nd pass: actually draw it
    stringInterpreter(startX, startY, scale, 1);
}

int main()
{
    srand(time(NULL));

    double height = 800.0;
    double width = 800.0;

    int depth = 0;
    printf("Specify the depth for the l-system: ");
    fflush(stdout);
    scanf("%d", &depth);

    G_init_graphics(width, height);

    //clear the screen in a given color
    G_rgb (0/255.0, 0/255.0, 0/255.0) ;
    // drawRandomColorMaker();
    G_clear ();

    //pick which l-system to draw
    // squareWave();
    // kochCurveLSystem();
    pushAndPop();

    stringBuilder(depth);
    //print the string to check it (only if it's short enough to read)
    if (strlen(u) < 500){
        printf("%s\n", u);
    }

    autoPlacer(width, height);

    //so that the window doesn't close
    G_wait_key();
}
