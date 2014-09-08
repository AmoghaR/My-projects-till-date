#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include<unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include<iostream>
using namespace std;

int check=1;  //for different screens
int count=0;
int w=500, h=500;
int duration,obj,limit;

typedef struct _item
{
    float x, y, z;
    float vx, vy, vz;

    float r, g, b;				// color for the items

    int rotx, roty, rotz;
    int incrotx, incroty, incrotz;

    int type;	/* different objects */
} item;

float xcord,ycord,zcord;

item object[30];

int rotate_x=0, rotate_y=0, old_x = 0, old_y = 0;

float cursor_x=0, cursor_y=0;

int objects = 1;

int info = 1;

int check2=0,check3=0;

void Truncate(float& d, unsigned int numberOfDecimalsToKeep)
{
    d = roundf(d * powf(10, numberOfDecimalsToKeep)) / powf(10, numberOfDecimalsToKeep);
}


void alarm_handler(int signum)
{

    if(count>limit-1)
        check2=1;
    else
        check3=1;
}

void func(int duration)
{
    struct itimerval delay;
    int ret;

    signal(SIGALRM, alarm_handler);
    delay.it_value.tv_sec = duration;
    delay.it_value.tv_usec = 0;
    delay.it_interval.tv_sec = 0;
    delay.it_interval.tv_usec = 0;

    ret=setitimer(ITIMER_REAL,&delay,NULL);

    if(ret)
    {
        perror("setitimer");
        return ;
    }


}

void init()
{
    int i;

    glClearColor(0, 0, 1.0, 0);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1,-1, 1,0, 10);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);

    for(i = 0; i < obj; i++)
    {


        object[i].x = (float)rand()/(float)(RAND_MAX) - 0.5;
        object[i].y = (float)rand()/(float)(RAND_MAX) - 0.5;
        object[i].z = (float)rand()/(float)(RAND_MAX) - 0.5;

        object[i].vx = (float)rand()/(float)(RAND_MAX*500) - 1/250;
        object[i].vy = (float)rand()/(float)(RAND_MAX*500) - 1/250;
        object[i].vz = (float)rand()/(((float)RAND_MAX)*100.0);

        object[i].r = 1.0;
        object[i].g = 0.0;
        object[i].b = 0.0;

        object[i].rotx = rand()%10 - 5;
        object[i].roty = rand()%10 - 5;
        object[i].rotz = rand()%10 - 5;

        object[i].incrotx = rand()%10 - 5;
        object[i].incroty = rand()%10 - 5;
        object[i].incrotz = rand()%10 - 5;

        object[i].type = rand()%4;
    }

    glPointSize(1);
}

void onscr1(char *prints,float a,float b,float c)
{
    int i;


    glMatrixMode(GL_PROJECTION);

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(a,b,c);

    for(i = 0; i < strlen(prints); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, prints[i]);
    }


    glPopMatrix();


}

void onscr2(char *prints,float a,float b,float c)
{
    int i;


    glMatrixMode(GL_PROJECTION);

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(a,b,c);

    for(i = 0; i < strlen(prints); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, prints[i]);
    }


    glPopMatrix();


}

void onscr3(char *prints,float a,float b,float c)
{
    int i;

    glMatrixMode(GL_PROJECTION);


    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(a,b,c);

    for(i = 0; i < strlen(prints); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, prints[i]);
    }
    glPopMatrix();

}



void
display(void)
{
    int i, j;
    float pos =4.0;


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0,1.0,1.0,1.01);
    glMatrixMode(GL_PROJECTION);

    glPushMatrix();

    glRotatef(rotate_x, 0, 1, 0);
    glRotatef(rotate_y, 1, 0, 0);

    glTranslatef(-cursor_x, cursor_y, 0);

    glColor3f(0.0,0.0,0.0);
    glutWireSphere(1.0,10,10);

    if(objects)
        for (i = 0; i < 30; i++)
        {

            glPushMatrix();

            glColor3f(object[i].r, object[i].g, object[i].b);

            glTranslatef(object[i].x, object[i].y, object[i].z);

            Truncate(object[i].x,2);
            Truncate(object[i].y,2);

            if(object[i].x==xcord && object[i].y==ycord )
            {
                Truncate(object[i].z,1);


                if(object[i].type!=4)
                {
                    object[i].type=4;
                    count=count+1;
                    object[i].r=1.0;
                    object[i].b=1.0;
                    object[i].g=1.0;
                }

                if(count==30)
                {


                    check2=1;


                }

            }

            glRotatef(object[i].rotx, 1, 0, 0);
            glRotatef(object[i].roty, 0, 1, 0);
            glRotatef(object[i].rotz, 0, 0, 1);

            switch(object[i].type)
            {
            case 0:
                glutWireSphere(0.03, 5, 5);
                break;
            case 1:
                glutWireCone(0.03, 0.03, 5, 5);
                break;
            case 2:
                glutWireCube(0.03);
                break;
            case 3:
                glutWireTorus(0.03, 0.03, 5, 5);
                break;
            case 4 :
                glutWireTeapot(0.03);
                break;

            }
            glPopMatrix();
        }

    glPopMatrix();

    if(check)
    {

        glClearColor(1.0,0.4,0.4,1.0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        int i, j;

        glPushMatrix();



        glColor3f(1.0,0.0,0.0);

        onscr2("MATCH 3D", -0.5,3.7,-0.5);

        onscr3("PROJECT BY:", -4.0,3.0,-0.5);

        onscr1("Abhilash N Murthy", -4.0,2.7,-0.5);

        onscr1("Amogha R", -4.0,2.3,-0.5);

        onscr3("UNDER THE GUIDANCE OF:", 2.5,3.0,-0.5);

        onscr1("Mrs.Sudha", 2.5,2.7,-0.5);

        onscr1("Associate professor , PESIT-BSC", 2.5,2.3,-0.5);

        onscr3("Instructions:", -4.0,1.0,-0.5);

        onscr3("The objective of the game is to change the incoming objects to teapots before the time runs out", -4.0,0.5,-0.5);

        onscr3("All you have to do is move the cursor around the path of the incoming object until it turns to a teapot and dissappears. Thats all... ", -4.0,0.0,-0.5);

        onscr3("You have 20 objects and 150 seconds ", -4.0,-1.5,-0.5);

        onscr3("Press Enter to the play game", -0.7,-3.0,-0.5);

        glPopMatrix();


    }

    if(check2)
    {
        glClearColor(1.0,0.4,0.4,1.0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        onscr2("You Win!!!", -0.5,3.7,-0.5);
    }

    if(check3)
    {

        glClearColor(1.0,0.4,0.4,1.0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        onscr2("You Lose!!!", -0.5,3.7,-0.5);

    }
    glutSwapBuffers();

}



void idle()
{
    int i;

    if(objects)
        for(i = 0; i < 30; i++)
        {
            object[i].z += object[i].vz;
            object[i].rotx += object[i].incrotx;
            object[i].roty += object[i].incroty;
            object[i].rotz += object[i].incrotz;
            object[i].z = object[i].z > 0. ? -0.3 : object[i].z;
        }

    glutPostRedisplay();
}

void passive(int x, int y)
{

    if(x < w && x > 0)
        cursor_x = (float)x/(float)w - 0.5;
    if(y < h && y > 0)
        cursor_y = (float)y/(float)h - 0.5;

    Truncate(cursor_x,2);

    Truncate(cursor_y,2);
    xcord=cursor_x;
    ycord=-cursor_y;
    glutPostRedisplay();

}


void keyboard(unsigned char key, int x, int y)
{
    int i;
    switch (key)
    {
    case 27:
        exit(0);
        break;

    case 13 :
        check = !check;

    }
}

void reshape(int width, int height)
{
    w = width;
    h = height;
    glClearColor(0.5, 0.5, 1.0, 1.0);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1,-1, 1,-1, 500);
    glFrustum(-1, 1,-1, 1, 0.1, 2);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{

    obj=20;
    duration=150;
    limit=30;

    func(duration);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(w, h);
    glutInit(&argc, argv);

    glutCreateWindow("MATCH 3D");
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutPassiveMotionFunc(passive);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutFullScreen();
    glutSetCursor(GLUT_CURSOR_NONE);
    init();
    glutMainLoop();
    return 0;
}

