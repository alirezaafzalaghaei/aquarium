#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <iostream>
#define DEG2RAD 3.14159 / 180.0

using namespace std;

float x[10],buby[10]= {-.95},bubx=-3.14,r[10],offset[10],pos[10],z[10],yy[10],speed[10],sizee[10],grass[100],ff=-.6,tv[10]= {0};
int dx[10]= {1},bx=1,zx[10],ee[10],fx=1;
int colors[10][3] = {{255, 165, 0},
    {242, 38, 19},
    {44, 62, 80},
    {219, 10, 91},
    {236,236,236},
    {243, 156, 18},
    {102, 51, 153},
    {224, 130, 131},
    {207, 0, 15},
    {162, 222, 208}
};

void circle(float x, float y, float r);
void DrawEllipse(float x, float y, float radiusX, float radiusY);
void DrawBubble(int i,float t);
void DrawGrass(int i,float t);
void DrawFish(int, int*,float);
void DrawStar(int,float,float,int*,float);
void Drawcircle(float x, float y, float r,float n,bool f1,bool f2);
void DrawCrab(int,float, float, float);
void ground();


void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glClearColor(66/255.,161/255.,198/255.,1); // Black and opaque
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glShadeModel(GL_SMOOTH);
    glLineWidth(2);

    // ground
    ground();

    //fish
    for(int i=0; i<10; i++)
        DrawFish(i,colors[i],sizee[i]);

    //grass
    for(int i=0; i<3; i++)
        DrawGrass(i,-.95+0.05*i);

    //star
    DrawStar(0,0.9,-0.9,colors[4],.5);

    //bubble
    for(int i=0; i<10; i++)
        DrawBubble(i,pos[i]);

    // crab
    DrawCrab(0,0,-.9,.2);

    glutPostRedisplay(); // Post a re-paint request to activate display()

    glutSwapBuffers(); // Double buffered - swap the front and back buffers
}

int main(int argc, char **argv)
{
    srand(time(0));

    for(int i=0; i<10; i++)
    {
        r[i] = (float)(rand()%4+4)/1000;
        offset[i] = (2*(float)rand()/RAND_MAX)-1;
        pos[i]=2*(float)rand()/RAND_MAX-1;
        yy[i] = (rand()%(9- (-7)+1)+-7)/10.0;
        sizee[i] = (float)(rand()%5)/10+.3;
        speed[i] = (float)(rand()%70)/10000+.001;
        z[i]=0;
        zx[i]=1;
        ee[i] = -10+2*i;//2*(rand()%2)-10; //-10,-8,-6
        x[i] = (2*(float)rand()/RAND_MAX)-1;
        tv[i]=0;
    }
    ee[0]=-9;
    ee[1]=-10;
    ee[2]=-9;
    for(int i=0; i<100; i++)
        if (rand()%10<1)
            grass[i] = rand()%10;
        else
            grass[i]=0;

    glutInit(&argc, argv);                           // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE);                // Enable double buffered mode
    glutInitWindowSize(640, 640);                    // Set the window's initial width & height - non-square
    glutInitWindowPosition(50, 50);                  // Position the window's initial top-left corner
    glutCreateWindow("Fish"); // Create window with the given title
    glutDisplayFunc(display);                        // Register callback handler for window re-paint event
    glutMainLoop();                                  // Enter the infinite event-processing loop
    //return 0;
}

void ground()
{

    glPushMatrix();
    glTranslatef(0,-.5,0);
    glRotatef(50,1,0,0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_POLYGON);
    glColor3f(66/255.,161/255.,198/255.);
    glVertex2d(-1, -0.25);
    glColor3ub(230, 126, 34);
    glVertex2d(-1, -1);
    glVertex2d(1, -1);
    glColor3f(66/255.,161/255.,198/255.);
    glVertex2d(1, -0.25);
    glEnd();
    glPopMatrix();
}

void DrawFish(int i, int c0[],float sc)
{

    //body
    glPushMatrix();
    glColor3ub(c0[0],c0[1],c0[2]);
    if(dx[i]==1)
    {
        glScalef(1,1,1);
        DrawEllipse(x[i], 0+yy[i], .18*sc, .12*sc);
    }
    else
    {
        glScalef(-1,1,1);
        DrawEllipse(-x[i], 0+yy[i], .18*sc, .12*sc);
    }
    glPopMatrix();

    //lower
    glPushMatrix();
    glTranslatef(0,+yy[i],0);
    if(dx[i]==1)
    {

        glScalef(1,1,1);
        glRotatef(40, 1, 0, 1);
        glTranslatef(x[i],0,x[i]);
    }
    else
    {
        glScalef(-1,1,1);
        glRotatef(40, 1, 0, 1);
        glTranslatef(-x[i],0,-x[i]);
    }
    DrawEllipse(-.17*sc, .035*sc, .1*sc, .075*sc);
    glPopMatrix();

    // upper
    glPushMatrix();
    glTranslatef(0,+yy[i],0);
    if(dx[i]==1)
    {
        glScalef(1,1,1);
        glRotatef(-40, 1, 0, 1);
        glTranslatef(x[i],0,x[i]);
    }
    else
    {
        glScalef(-1,1,1);
        glRotatef(-40, 1, 0, 1);
        glTranslatef(-x[i],0,-x[i]);
    }
    DrawEllipse(-.17*sc, - .035*sc, .1*sc, .075*sc);
    glPopMatrix();

    // eye
    glPushMatrix();
    glColor3f(1,1,1);
    if(dx[i]==1)
    {
        glScalef(1,1,1);
        DrawEllipse(x[i]+.1*sc,0+.03*sc+yy[i],.025*sc,.025*sc);
        glColor3f(0,0,0);
        DrawEllipse(x[i]+.1*sc,0+.03*sc+yy[i],.01*sc,.01*sc);
    }
    else
    {
        glScalef(-1,1,1);
        DrawEllipse(-x[i]+.1*sc,.03*sc+yy[i],.025*sc,.025*sc);
        glColor3f(0,0,0);
        DrawEllipse(-x[i]+.1*sc,.03*sc+yy[i],.01*sc,.01*sc);
    }
    glPopMatrix();

    dx[i] = x[i]>.87?-1:x[i]<-.87?1:dx[i];
    x[i] = dx[i]==1?x[i]+speed[i]:x[i]-speed[i];

}
void circle(float x, float y, float r)
{
    float t;
    for (int i = -1000; i < 1000; i++)
    {
        t = i / 1000.0;
        glVertex2f(t + x, sqrt(r * r - t * t) + y);
        glVertex2f(t + x, -sqrt(r * r - t * t) + y);
    }
}
void DrawEllipse(float x, float y, float radiusX, float radiusY)
{
    register int i;
    register float rad ;
    glBegin(GL_POLYGON);
    for (i = 0; i < 360; i++)
    {
        glVertex2f(x + cos(i * DEG2RAD) * radiusX, y + sin(i * DEG2RAD) * radiusY);
    }
    glEnd();
}
void DrawBubble(int i,float t)
{
    // bubble
    glPushMatrix();
    if (i%2==0)
    {
        glColor4f(1,1,1,.3);
        DrawEllipse(t+sin(bubx)/20,buby[i]+offset[i],.03,.03);
        glColor3f(1,1,1);
        glPointSize(1);
        glBegin(GL_POINTS);
        circle(t+sin(bubx)/20,buby[i]+offset[i],.03);
        glEnd();
    }
    else
    {
        glColor4f(1,1,1,.3);
        DrawEllipse(t+cos(bubx)/20,buby[i]+offset[i],.03,.03);
        glColor3f(1,1,1);
        glPointSize(1);
        glBegin(GL_POINTS);
        circle(t+cos(bubx)/20,buby[i]+offset[i],.03);
        glEnd();
    }
    glPopMatrix();


    buby[i]+=r[i];

    if(buby[i]>1.3)
    {
        buby[i] =-1.5;
        pos[i]=2*(float)rand()/RAND_MAX-1;
    }
    bubx +=0.01;

}
void DrawGrass(int k,float t)
{
    glPushMatrix();
    glLineWidth(6);
    glBegin(GL_LINE_STRIP);
    float j=0;
    for(int i=0; i<79+ee[k]; j+=0.006,i++,tv[k]+=0.1) //(float)rand()/RAND_MAX
    {
        glColor3f(109/255.0-j,154/255.0+j,109/255.0-j);
        glVertex2f(t+sin(.9*tv[k])/70  + z[k]*cos(.005*tv[k])/70,(float)i/150-1);

    }
    glEnd();
    glPopMatrix();
    z[k] += 0.001*zx[k];
    zx[k] = z[k]>1.56?-1:z[k]<-1.56?1:zx[k];

}
void DrawStar(int k,float x,float y,int* color,float sc)
{
    glPushMatrix();
    glTranslatef(x,y,0);
    glScalef(sc,sc,0);

    glRotatef(50,1,0,0);


    glColor3ub(color[0],color[1],color[2]);
    glLineWidth(3);
    glScalef(1,1,1);
    float tt=0;
    {
        glBegin (GL_TRIANGLES);
        glVertex3f(0.0,0.2,tt);
        glVertex3f(0.04,0.08,tt);
        glVertex3f(-0.04,0.08,tt);
        glVertex3f(0.04,0.08,tt);
        glVertex3f(0.17,0.08,tt);
        glVertex3f(0.07,0.0,tt);
        glVertex3f(0.07,0.0,tt);
        glVertex3f(0.12,-.14,tt);
        glVertex3f(0,-.04,tt);
        glVertex3f(0,-.04,tt);
        glVertex3f(-0.12,-.14,tt);
        glVertex3f(-0.06,0,tt);
        glVertex3f(-0.06,0,tt);
        glVertex3f(-0.16,0.08,tt);
        glVertex3f(-0.04,0.08,tt);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex3f(0.04,0.08,tt);
        glVertex3f(0.07,0.0,tt);
        glVertex3f(0,-.04,tt);
        glVertex3f(-0.07,0.0,tt);
        glVertex3f(-0.04,0.08,tt);
        glEnd();
    }
    glPopMatrix();

}
void DrawCrab(int i,float x,float y,float sc)
{
    glPushMatrix();
    glTranslatef(x+ff,y,0);
    glScalef(sc,sc,0);
    glColor3ub(228,85,44);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glLineWidth(3);
    glPointSize(3);

    DrawEllipse(0,0,.5,.3);
    Drawcircle(0,-1,1.1,490,true,false);

    glBegin(GL_LINES);
    glVertex2f(-.1,-.01);
    glVertex2f(.1,-.01);
    glEnd();

    Drawcircle(.20,.33,.05,1000,true,true);
    Drawcircle(-.20,.33,.05,1000,true,true);

    glPushMatrix();
    glRotatef(60,0,0,1);
    glTranslatef(.70,-.10,0);
    glTranslatef(.01,-.05,0);
    Drawcircle(-.15,.35,.4,200,false,true);
    glPopMatrix();

    glPushMatrix();
    glRotatef(120,0,0,1);
    glTranslatef(.70,-.10,0);
    glTranslatef(.06,.09,0);

    Drawcircle(-.2,-.2,.4,200,true,false);
    glPopMatrix();


    Drawcircle(-.5,.7,.1,500,false,true);
    Drawcircle(.5,.7,.1,500,false,true);

    glPushMatrix();
    glRotatef(120,0,0,1);
    glTranslatef(-.30,0.45,0);
    glTranslatef(.00,-.08,0);

    Drawcircle(-.2,-.2,.3,150,false,true);
    glPopMatrix();

    glPushMatrix();
    glRotatef(240,0,0,1);
    glTranslatef(.5,.71,0);

    Drawcircle(0,-.5,.3,150,false,true);
    glPopMatrix();

    glPushMatrix();
    glRotatef(240,0,0,1);
    glTranslatef(.45,.71,0);

    Drawcircle(0,-.5,.2,140,false,true);
    glPopMatrix();

    glPushMatrix();
    glRotatef(120,0,0,1);
    glTranslatef(-.26,0.45,0);
    glTranslatef(.00,-.08,0);

    Drawcircle(-.2,-.2,.2,140,false,true);
    glPopMatrix();

    glPopMatrix();
    ff+=0.0015*fx;
    fx= ff>.6?-1:ff<-.6?1:fx;
}
void Drawcircle(float x, float y, float r,float n=1000,bool f1=false,bool f2=false)
{
    float t;
    glBegin(GL_POINTS);

    for (int i = -n; i < n; i++)
    {
        t = i / 1000.0;
        if (f1)
            glVertex2f(t + x, sqrt(r * r - t * t) + y);
        if(f2)
            glVertex2f(t + x, -sqrt(r * r - t * t) + y);
    }
    glEnd();
}
