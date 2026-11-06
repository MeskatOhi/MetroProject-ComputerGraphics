#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>


#define PI 3.1416


int activeScene = 1;
int metroSoundOn = 0;
int soundMuted = 0;
int currentPage = 0;   // 0 = Cover, 1 = Instruction, 2 = Project
int projectStarted = 0;

void sound();
void stopSound();
void updateMetroSound(int visible);



// =========================
// COVER & INSTRUCTION PAGE
// =========================

void renderBitmapString(float x, float y, void *font, const char *text)
{
    glRasterPos2f(x, y);

    for(int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(font, text[i]);
    }
}

void pageInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1350, 0, 750);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawCoverPage()
{
    pageInit();

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.5);
    renderBitmapString(265, 710, GLUT_BITMAP_TIMES_ROMAN_24,
                       "AMERICAN INTERNATIONAL UNIVERSITY-BANGLADESH (AIUB)");

    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(485, 680, GLUT_BITMAP_HELVETICA_18,
                       "COURSE NAME: COMPUTER GRAPHICS");
    renderBitmapString(570, 640, GLUT_BITMAP_HELVETICA_18,
                       "SUMMER 2025-2026");
    renderBitmapString(620, 610, GLUT_BITMAP_HELVETICA_18,
                       "SECTION: F");

    renderBitmapString(590, 570, GLUT_BITMAP_HELVETICA_18,
                       "PROJECT TITLE:");

    glColor3f(0.0, 0.0, 0.5);
    renderBitmapString(455, 535, GLUT_BITMAP_TIMES_ROMAN_24,
                       "INTERACTIVE METRO-RAIL TRANSIT SIMULATION");

    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(585, 495, GLUT_BITMAP_HELVETICA_18,
                       "SUPERVISED BY:");
    renderBitmapString(555, 465, GLUT_BITMAP_TIMES_ROMAN_24,
                       "MAHFUJUR RAHMAN");

    renderBitmapString(590, 415, GLUT_BITMAP_HELVETICA_18,
                       "SUBMITTED BY:");
    renderBitmapString(1000, 415, GLUT_BITMAP_HELVETICA_18,
                       "SUBMISSION DATE: 01/09/2026");

    glBegin(GL_LINES);
        glVertex2i(1000, 405);
        glVertex2i(1290, 405);
    glEnd();

    // Table border
    glBegin(GL_LINE_LOOP);
        glVertex2i(55, 380);
        glVertex2i(1295, 380);
        glVertex2i(1295, 55);
        glVertex2i(55, 55);
    glEnd();

    // Vertical lines
    glBegin(GL_LINES);
        glVertex2i(170, 380); glVertex2i(170, 55);
        glVertex2i(520, 380); glVertex2i(520, 55);
        glVertex2i(835, 380); glVertex2i(835, 55);
    glEnd();

    // Horizontal lines
    glBegin(GL_LINES);
        glVertex2i(55, 330); glVertex2i(1295, 330);
        glVertex2i(55, 275); glVertex2i(1295, 275);
        glVertex2i(55, 220); glVertex2i(1295, 220);
        glVertex2i(55, 165); glVertex2i(1295, 165);
        glVertex2i(55, 110); glVertex2i(1295, 110);
    glEnd();

    // Header
    renderBitmapString(85, 350, GLUT_BITMAP_HELVETICA_18, "SL NO.");
    renderBitmapString(310, 350, GLUT_BITMAP_HELVETICA_18, "NAME");
    renderBitmapString(650, 350, GLUT_BITMAP_HELVETICA_18, "ID");
    renderBitmapString(990, 350, GLUT_BITMAP_HELVETICA_18, "CONTRIBUTION");

    // Member 1
    renderBitmapString(105, 300, GLUT_BITMAP_HELVETICA_18, "1");
    renderBitmapString(195, 300, GLUT_BITMAP_HELVETICA_18, "AHMAD AKIB RUPOK");
    renderBitmapString(625, 300, GLUT_BITMAP_HELVETICA_18, "23-50699-1");
    renderBitmapString(890, 300, GLUT_BITMAP_HELVETICA_18, "Scene 2");

    // Member 2
    renderBitmapString(105, 245, GLUT_BITMAP_HELVETICA_18, "2");
    renderBitmapString(195, 245, GLUT_BITMAP_HELVETICA_18, "HALIMATUS SADIA");
    renderBitmapString(625, 245, GLUT_BITMAP_HELVETICA_18, "23-53096-3");
    renderBitmapString(890, 245, GLUT_BITMAP_HELVETICA_18, "Scene 3");

    // Member 3
    renderBitmapString(105, 190, GLUT_BITMAP_HELVETICA_18, "3");
    renderBitmapString(195, 190, GLUT_BITMAP_HELVETICA_18, "MD. JAWAD HASSAN");
    renderBitmapString(625, 190, GLUT_BITMAP_HELVETICA_18, "23-54909-3");
    renderBitmapString(890, 190, GLUT_BITMAP_HELVETICA_18, "Scene 5");

    // Member 4
    renderBitmapString(105, 135, GLUT_BITMAP_HELVETICA_18, "4");
    renderBitmapString(195, 135, GLUT_BITMAP_HELVETICA_18, "MESKAT OHI");
    renderBitmapString(625, 135, GLUT_BITMAP_HELVETICA_18, "23-55353-3");
    renderBitmapString(890, 135, GLUT_BITMAP_HELVETICA_18, "Scene 1");

    // Member 5
    renderBitmapString(105, 80, GLUT_BITMAP_HELVETICA_18, "5");
    renderBitmapString(195, 80, GLUT_BITMAP_HELVETICA_18, "RAGIB NUR KAIF");
    renderBitmapString(625, 80, GLUT_BITMAP_HELVETICA_18, "24-56862-1");
    renderBitmapString(890, 80, GLUT_BITMAP_HELVETICA_18, "Scene 4, Merge & Sound");

    renderBitmapString(500, 25,GLUT_BITMAP_HELVETICA_18,"Press Key : ENTER For Next Page");

    glFlush();
}

void drawInstructionPage()
{
    pageInit();

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.5);
    renderBitmapString(455, 700, GLUT_BITMAP_TIMES_ROMAN_24,
                       "INTERACTIVE METRO-RAIL TRANSIT SIMULATION");

    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(565, 655, GLUT_BITMAP_HELVETICA_18,
                       "INSTRUCTION PAGE");

    glBegin(GL_LINES);
        glVertex2i(350, 635);
        glVertex2i(1000, 635);
    glEnd();

    renderBitmapString(420, 595, GLUT_BITMAP_HELVETICA_18,
                       "Use the following keyboard keys to control the project.");

    // Navigation
    glColor3f(0.0, 0.0, 0.5);
    renderBitmapString(180, 535, GLUT_BITMAP_HELVETICA_18, "NAVIGATION");

    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(230, 490, GLUT_BITMAP_HELVETICA_18, "ENTER");
    renderBitmapString(340, 490, GLUT_BITMAP_HELVETICA_18,
                       "- Go from Cover Page to Instruction Page");

    renderBitmapString(230, 450, GLUT_BITMAP_HELVETICA_18, "S");
    renderBitmapString(340, 450, GLUT_BITMAP_HELVETICA_18,
                       "- Start the Project");

    // Scene controls
    glColor3f(0.0, 0.0, 0.5);
    renderBitmapString(180, 390, GLUT_BITMAP_HELVETICA_18, "SCENE CONTROLS");

    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(230, 345, GLUT_BITMAP_HELVETICA_18, "1");
    renderBitmapString(340, 345, GLUT_BITMAP_HELVETICA_18, "- Scene 1");

    renderBitmapString(230, 310, GLUT_BITMAP_HELVETICA_18, "2");
    renderBitmapString(340, 310, GLUT_BITMAP_HELVETICA_18, "- Scene 2");

    renderBitmapString(230, 275, GLUT_BITMAP_HELVETICA_18, "3");
    renderBitmapString(340, 275, GLUT_BITMAP_HELVETICA_18, "- Scene 3");

    renderBitmapString(230, 240, GLUT_BITMAP_HELVETICA_18, "4");
    renderBitmapString(340, 240, GLUT_BITMAP_HELVETICA_18, "- Scene 4");

    renderBitmapString(230, 205, GLUT_BITMAP_HELVETICA_18, "5");
    renderBitmapString(340, 205, GLUT_BITMAP_HELVETICA_18, "- Scene 5");

    // Sound controls
    glColor3f(0.0, 0.0, 0.5);
    renderBitmapString(700, 390, GLUT_BITMAP_HELVETICA_18, "SOUND CONTROLS");

    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(750, 345, GLUT_BITMAP_HELVETICA_18, "M");
    renderBitmapString(850, 345, GLUT_BITMAP_HELVETICA_18, "- Mute Sound");

    renderBitmapString(750, 310, GLUT_BITMAP_HELVETICA_18, "P");
    renderBitmapString(850, 310, GLUT_BITMAP_HELVETICA_18, "- Play Sound");

    // Exit
    glColor3f(0.0, 0.0, 0.5);
    renderBitmapString(700, 240, GLUT_BITMAP_HELVETICA_18, "EXIT");

    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(750, 205, GLUT_BITMAP_HELVETICA_18, "ESC");
    renderBitmapString(850, 205, GLUT_BITMAP_HELVETICA_18, "- Exit Project");

    // Flow
    glColor3f(0.0, 0.0, 0.5);
    renderBitmapString(180, 145, GLUT_BITMAP_HELVETICA_18, "PROJECT FLOW");

    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(390, 100, GLUT_BITMAP_HELVETICA_18,
                       "Scene 1  ->  Scene 2  ->  Scene 3  ->  Scene 4  ->  Scene 5");

    glFlush();
}


//Ohi
// train variables

float scene1_trainPosition = -12.5f;

float scene1_trainSpeed = 0.08f;

int scene1_night = 0;

int scene1_animationFinished = 0;

// cloud variables

float scene1_cloudPosition = -4.0f;

float scene1_cloudSpeed = 0.03f;

// bird variables

float scene1_birdPosition = -4.0f;

float scene1_birdSpeed = 0.06f;

// sun variables

float scene1_sunPosition = -2.0f;

float scene1_sunSpeed = 0.04f;

// moon variables

float scene1_moonPosition = -2.0f;

float scene1_moonSpeed = 0.04f;

// scene1_circle

void scene1_circle(float cx, float cy, float r)

{

    glBegin(GL_POLYGON);

    for(int i = 0; i <= 360; i++)

    {

        float a = i * 3.1416 / 180.0;

        glVertex2f(

            cx + cos(a) * r,

            cy + sin(a) * r

        );

    }

    glEnd();

}

// scene1_building

void scene1_building(float x1, float x2, float y1, float y2)

{

    glColor3f(0.82,0.82,0.82);

    glBegin(GL_QUADS);

    glVertex2f(x1,y1);

    glVertex2f(x2,y1);

    glVertex2f(x2,y2);

    glVertex2f(x1,y2);

    glEnd();

    if(scene1_night == 0)

    {

        glColor3f(0.45,0.45,0.45);

    }

    else

    {

        glColor3f(1.0,0.75,0.25);

    }

    for(float x = x1 + 0.2; x < x2 - 0.1; x += 0.4)

    {

        for(float y = y1 + 0.3; y < y2 - 0.2; y += 0.45)

        {

            glBegin(GL_QUADS);

            glVertex2f(x,y);

            glVertex2f(x+0.12,y);

            glVertex2f(x+0.12,y+0.18);

            glVertex2f(x,y+0.18);

            glEnd();

        }

    }

}

// cloud

void scene1_drawCloud(float x, float y)

{

    glColor3f(1.0,0.75,0.35);

    scene1_circle(x,y,0.50);

    scene1_circle(x+0.4,y+0.2,0.62);

    scene1_circle(x+0.9,y,0.50);

}

// birds

void scene1_drawBird(float x, float y)

{

    glColor3f(0.0,0.0,0.0);

    glBegin(GL_LINES);

    glVertex2f(x,y);

    glVertex2f(x+0.25,y+0.20);

    glVertex2f(x+0.25,y+0.20);

    glVertex2f(x+0.50,y);

    glEnd();

}

// stars

void scene1_drawStars()

{

    if(scene1_night == 1)

    {

        glColor3f(1.0,1.0,1.0);

        // left side stars

        glBegin(GL_POLYGON);



        glVertex2f(1.08,9.05);

        glVertex2f(1.22,9.02);

        glVertex2f(1.10,8.92);

        glVertex2f(1.13,8.77);

        glVertex2f(1.0,8.85);

        glVertex2f(0.87,8.77);

        glVertex2f(0.90,8.92);

        glVertex2f(0.78,9.02);

        glVertex2f(0.92,9.05);
        glVertex2f(1.0,9.2);

        glEnd();

        glBegin(GL_POLYGON);



        glVertex2f(2.58,8.37);

        glVertex2f(2.72,8.34);

        glVertex2f(2.60,8.24);

        glVertex2f(2.63,8.10);

        glVertex2f(2.5,8.18);

        glVertex2f(2.37,8.10);

        glVertex2f(2.40,8.24);

        glVertex2f(2.28,8.34);

        glVertex2f(2.42,8.37);
        glVertex2f(2.5,8.5);

        glEnd();

        glBegin(GL_POLYGON);



        glVertex2f(3.88,9.37);

        glVertex2f(4.02,9.34);

        glVertex2f(3.90,9.24);

        glVertex2f(3.93,9.10);

        glVertex2f(3.8,9.18);

        glVertex2f(3.67,9.10);

        glVertex2f(3.70,9.24);

        glVertex2f(3.58,9.34);

        glVertex2f(3.72,9.37);
        glVertex2f(3.8,9.5);

        glEnd();

        // right side stars

        glBegin(GL_POLYGON);


        glVertex2f(15.08,9.27);

        glVertex2f(15.22,9.24);

        glVertex2f(15.10,9.14);

        glVertex2f(15.13,9.0);

        glVertex2f(15.0,9.08);

        glVertex2f(14.87,9.0);

        glVertex2f(14.90,9.14);

        glVertex2f(14.78,9.24);

        glVertex2f(14.92,9.27);
        glVertex2f(15.0,9.4);


        glEnd();

        glBegin(GL_POLYGON);



        glVertex2f(16.78,8.47);

        glVertex2f(16.92,8.44);

        glVertex2f(16.80,8.34);

        glVertex2f(16.83,8.20);

        glVertex2f(16.7,8.28);

        glVertex2f(16.57,8.20);

        glVertex2f(16.60,8.34);

        glVertex2f(16.48,8.44);

        glVertex2f(16.62,8.47);
        glVertex2f(16.7,8.6);
        glEnd();

        glBegin(GL_POLYGON);



        glVertex2f(17.88,9.47);

        glVertex2f(18.02,9.44);

        glVertex2f(17.90,9.34);

        glVertex2f(17.93,9.20);

        glVertex2f(17.8,9.28);

        glVertex2f(17.67,9.20);

        glVertex2f(17.70,9.34);

        glVertex2f(17.58,9.44);

        glVertex2f(17.72,9.47);
        glVertex2f(17.8,9.6);

        glEnd();

        glBegin(GL_POLYGON);



        glVertex2f(18.88,8.67);

        glVertex2f(19.02,8.64);

        glVertex2f(18.90,8.54);

        glVertex2f(18.93,8.40);

        glVertex2f(18.8,8.48);

        glVertex2f(18.67,8.40);

        glVertex2f(18.70,8.54);

        glVertex2f(18.58,8.64);

        glVertex2f(18.72,8.67);
        glVertex2f(18.8,8.8);

        glEnd();

        glBegin(GL_POLYGON);


        glVertex2f(19.58,9.37);

        glVertex2f(19.72,9.34);

        glVertex2f(19.60,9.24);

        glVertex2f(19.63,9.10);

        glVertex2f(19.5,9.18);

        glVertex2f(19.37,9.10);

        glVertex2f(19.40,9.24);

        glVertex2f(19.28,9.34);

        glVertex2f(19.42,9.37);
        glVertex2f(19.5,9.5);

        glEnd();

    }

}

// train

void scene1_drawTrain()

{

    glPushMatrix();

    glTranslatef(scene1_trainPosition,0.0f,0.0f);

    // train body

    glColor3f(0.84,0.84,0.82);

    glBegin(GL_QUADS);

    glVertex2f(0.5,5.35);

    glVertex2f(12.0,5.35);

    glVertex2f(12.0,6.55);

    glVertex2f(0.5,6.55);

    glEnd();

    // front

    glColor3f(0.0,0.45,0.25);

    glBegin(GL_POLYGON);

    glVertex2f(12.0,5.35);

    glVertex2f(12.3,5.55);

    glVertex2f(12.3,6.35);

    glVertex2f(12.0,6.55);

    glEnd();

    // green stripe

    glColor3f(0.0,0.45,0.25);

    glBegin(GL_QUADS);

    glVertex2f(0.5,5.6);

    glVertex2f(12.0,5.6);

    glVertex2f(12.0,5.72);

    glVertex2f(0.5,5.72);

    glEnd();

    // windows

    glColor3f(0.15,0.15,0.15);

    for(float x = 0.8; x < 11.5; x += 1.1)

    {

        glBegin(GL_QUADS);

        glVertex2f(x,5.9);

        glVertex2f(x+0.45,5.9);

        glVertex2f(x+0.45,6.28);

        glVertex2f(x,6.28);

        glEnd();

    }

    // doors

    glColor3f(0.95,0.65,0.22);

    for(float x = 1.8; x < 11.0; x += 2.2)

    {

        glBegin(GL_QUADS);

        glVertex2f(x,5.55);

        glVertex2f(x+0.25,5.55);

        glVertex2f(x+0.25,6.35);

        glVertex2f(x,6.35);

        glEnd();

    }

    // wheels

    glColor3f(0.10,0.10,0.10);

    for(float x = 1.2; x <= 11.2; x += 1.2)

    {

        scene1_circle(x,5.18,0.09);

    }

    glPopMatrix();

}

// animation

void scene1_update(int value)
{
    // train always moves
    scene1_trainPosition += scene1_trainSpeed;

    if(scene1_night == 0)
    {
        // sun
        scene1_sunPosition += scene1_sunSpeed;

        if(scene1_sunPosition > 21.0f)
        {
            scene1_sunPosition = -2.0f;
        }

        // clouds
        scene1_cloudPosition += scene1_cloudSpeed;

        if(scene1_cloudPosition > 21.0f)
        {
            scene1_cloudPosition = -4.0f;
        }

        // birds
        scene1_birdPosition += scene1_birdSpeed;

        if(scene1_birdPosition > 21.0f)
        {
            scene1_birdPosition = -4.0f;
        }

        // Day -> Night
        if(scene1_trainPosition > 20.0f)
        {
            scene1_night = 1;
            scene1_trainPosition = -12.5f;
            scene1_moonPosition = -2.0f;
        }
    }
    else
    {
        // moon
        scene1_moonPosition += scene1_moonSpeed;

        if(scene1_moonPosition > 21.0f)
        {
            scene1_moonPosition = -2.0f;
        }

        // Night -> Day
        if(scene1_trainPosition > 20.0f)
        {
            scene1_night = 0;
            scene1_trainPosition = -12.5f;
            scene1_sunPosition = -2.0f;
        }
    }

    if(activeScene == 1)
        updateMetroSound((scene1_trainPosition + 12.3f > 0.0f) &&
                         (scene1_trainPosition + 0.5f < 20.0f));

    glutPostRedisplay();
    glutTimerFunc(30, scene1_update, 0);
}

// scene1_display

void scene1_display()

{

    glClear(GL_COLOR_BUFFER_BIT);

    // sky

    if(scene1_night == 0)

    {

        glBegin(GL_QUADS);

        glColor3f(0.98,0.68,0.20);

        glVertex2f(0,0);

        glVertex2f(20,0);

        glColor3f(0.95,0.40,0.18);

        glVertex2f(20,10);

        glVertex2f(0,10);

        glEnd();

    }

    else

    {

        glBegin(GL_QUADS);

        glColor3f(0.04,0.08,0.20);

        glVertex2f(0,0);

        glVertex2f(20,0);

        glColor3f(0.02,0.04,0.12);

        glVertex2f(20,10);

        glVertex2f(0,10);

        glEnd();

    }

    // clouds

    if(scene1_night == 0)

    {

        scene1_drawCloud(scene1_cloudPosition,8.35);

        scene1_drawCloud(scene1_cloudPosition+8.0,8.70);

        scene1_drawCloud(scene1_cloudPosition+14.0,9.05);

    }

    // birds

    if(scene1_night == 0)

    {

        scene1_drawBird(scene1_birdPosition,9.0);

        scene1_drawBird(scene1_birdPosition+2.0,8.55);

        scene1_drawBird(scene1_birdPosition+4.0,9.25);

        scene1_drawBird(scene1_birdPosition+6.0,8.85);

        scene1_drawBird(scene1_birdPosition+8.0,9.35);

    }

    // sun

    if(scene1_night == 0)

    {

        glColor3f(1.0,0.86,0.35);

        scene1_circle(scene1_sunPosition,8.0,0.85);

    }

    // moon

    if(scene1_night == 1)

    {

        glColor3f(1.0,1.0,1.0);

        scene1_circle(scene1_moonPosition,8.5,0.65);

    }

    // stars

    scene1_drawStars();

    // buildings

    scene1_building(2.9,3.7,1.7,3.5);

    scene1_building(5.0,5.9,1.7,3.8);

    scene1_building(15.0,16.0,1.7,4.3);

    scene1_building(16.2,17.2,1.7,4.5);

    scene1_building(17.5,18.8,1.7,4.7);

    scene1_building(19.0,19.8,1.7,3.9);

    // left tree

    glColor3f(0.35,0.18,0.08);

    glBegin(GL_QUADS);

    glVertex2f(1.0,1.8);

    glVertex2f(1.2,1.8);

    glVertex2f(1.2,2.9);

    glVertex2f(1.0,2.9);

    glEnd();

    glColor3f(0.10,0.35,0.12);

    scene1_circle(0.5,3.30,0.55);

    scene1_circle(1.1,3.30,0.55);

    scene1_circle(1.7,3.35,0.55);

    scene1_circle(1.1,4.15,0.50);

    // middle tree

    glColor3f(0.35,0.18,0.08);

    glBegin(GL_QUADS);

    glVertex2f(4.0,1.8);

    glVertex2f(4.2,1.8);

    glVertex2f(4.2,2.9);

    glVertex2f(4.0,2.9);

    glEnd();

    glColor3f(0.10,0.35,0.12);

    scene1_circle(3.5,3.30,0.55);

    scene1_circle(4.1,3.30,0.55);

    scene1_circle(4.7,3.35,0.55);

    scene1_circle(4.1,4.15,0.50);

    // right tree

    glColor3f(0.35,0.18,0.08);

    glBegin(GL_QUADS);

    glVertex2f(7.0,1.8);

    glVertex2f(7.2,1.8);

    glVertex2f(7.2,2.9);

    glVertex2f(7.0,2.9);

    glEnd();

    glColor3f(0.10,0.35,0.12);

    scene1_circle(6.5,3.30,0.55);

    scene1_circle(7.1,3.30,0.55);

    scene1_circle(7.7,3.35,0.55);

    scene1_circle(7.1,4.15,0.50);

    // green land

    if(scene1_night == 0)

        glColor3f(0.18,0.45,0.12);

    else

        glColor3f(0.08,0.22,0.08);

    glBegin(GL_QUADS);

    glVertex2f(0,1.8);

    glVertex2f(20,1.8);

    glVertex2f(20,2.2);

    glVertex2f(0,2.2);

    glEnd();

    // water

    glColor3f(0.18,0.49,0.85);

    glBegin(GL_QUADS);

    glVertex2f(0,0);

    glVertex2f(20,0);

    glVertex2f(20,1.8);

    glVertex2f(0,1.8);

    glEnd();

    // bridge

    glColor3f(0.62,0.62,0.64);

    glBegin(GL_QUADS);

    glVertex2f(0,5.0);

    glVertex2f(20,5.0);

    glVertex2f(20,6.0);

    glVertex2f(0,6.0);

    glEnd();

    glColor3f(0.25,0.25,0.28);

    glBegin(GL_QUADS);

    glVertex2f(0,4.55);

    glVertex2f(20,4.55);

    glVertex2f(20,5.0);

    glVertex2f(0,5.0);

    glEnd();

    // pillar

    glColor3f(0.55,0.55,0.58);

    glBegin(GL_QUADS);

    glVertex2f(11.8,1.8);

    glVertex2f(12.6,1.8);

    glVertex2f(12.6,4.6);

    glVertex2f(11.8,4.6);

    glEnd();

    glBegin(GL_QUADS);

    glVertex2f(11.6,4.6);

    glVertex2f(12.8,4.6);

    glVertex2f(12.8,5.0);

    glVertex2f(11.6,5.0);

    glEnd();

    // rail

    glColor3f(0.12,0.12,0.12);

    glBegin(GL_LINES);

    glVertex2f(0,6.40);

    glVertex2f(20,6.40);

    glEnd();

    // upper wires

    glColor3f(0.25,0.25,0.25);

    glBegin(GL_LINES);

    glVertex2f(0,6.95);

    glVertex2f(20,6.95);

    glVertex2f(0,7.20);

    glVertex2f(20,7.20);

    glVertex2f(0,7.45);

    glVertex2f(20,7.45);

    glEnd();

    // wire connectors

    glColor3f(0.20,0.20,0.20);

    glBegin(GL_LINES);

    glVertex2f(2.0,6.40);

    glVertex2f(2.0,6.95);

    glVertex2f(5.0,6.40);

    glVertex2f(5.0,6.95);

    glVertex2f(8.0,6.40);

    glVertex2f(8.0,6.95);

    glVertex2f(11.0,6.40);

    glVertex2f(11.0,6.95);

    glVertex2f(14.0,6.40);

    glVertex2f(14.0,6.95);

    glVertex2f(17.0,6.40);

    glVertex2f(17.0,6.95);

    glVertex2f(20.0,6.40);

    glVertex2f(20.0,6.95);

    glEnd();

    // wire supports

    glColor3f(0.20,0.20,0.20);

    for(float x = 0; x <= 20; x += 3)

    {

        glBegin(GL_LINES);

        glVertex2f(x,6.90);

        glVertex2f(x,7.50);

        glEnd();

    }

    // electric pole

    glColor3f(0.20,0.20,0.20);

    glBegin(GL_LINES);

    glVertex2f(13.3,6.0);

    glVertex2f(13.3,8.0);

    glVertex2f(14.2,6.0);

    glVertex2f(14.2,8.0);

    glVertex2f(13.3,8.0);

    glVertex2f(14.1,8.3);

    glVertex2f(14.1,8.3);

    glVertex2f(14.2,8.0);

    glEnd();

    // train

    if(scene1_animationFinished == 0)

    {

        scene1_drawTrain();

    }

    // track line

    glColor3f(0.10,0.10,0.10);

    glBegin(GL_LINES);

    glVertex2f(0.2,5.18);

    glVertex2f(20.0,5.18);

    glEnd();

    glFlush();

}

// initialization

void scene1_init()

{

    glClearColor(1,1,1,1);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(0,20,0,10);

}

// main

//Rupok


/* train variables */
float scene2_trainPosition = 0.0f;
float scene2_trainSpeed = 0.05f;

/* street traffic variables */
float scene2_bus1Position = 0.0f;  float scene2_bus1Speed = 0.028f;
float scene2_carPosition  = 0.0f;  float scene2_carSpeed  = 0.045f;
float scene2_cngPosition  = 0.0f;  float scene2_cngSpeed  = 0.035f;
float scene2_bus2Position = 0.0f;  float scene2_bus2Speed = 0.022f;

/* cloud / bird variables */
float scene2_cloudPosition = 0.0f;
float scene2_cloudSpeed = 0.004f;
float scene2_birdPosition = 0.0f;
float scene2_birdSpeed = 0.006f;

/* scene2_circle */
void scene2_circle(float cx, float cy, float r)
{
    glBegin(GL_POLYGON);
    for(int i = 0; i <= 360; i++)
    {
        float a = i * 3.1416 / 180.0;
        glVertex2f(cx + cos(a) * r, cy + sin(a) * r);
    }
    glEnd();
}

/* scene2_rectangle */
void scene2_rectangle(float x1, float y1, float x2, float y2)
{
    glBegin(GL_QUADS);
    glVertex2f(x1,y1);
    glVertex2f(x2,y1);
    glVertex2f(x2,y2);
    glVertex2f(x1,y2);
    glEnd();
}

/* line */
void scene2_lineSeg(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
}

/* bitmap scene2_text */
void scene2_text(float x, float y, const char *s, void *font)
{
    glRasterPos2f(x,y);
    for(; *s; s++) glutBitmapCharacter(font, *s);
}

/* stylised Bengali script */
void scene2_bengali(float x, float y, float w, float t)
{
    scene2_lineSeg(x,y,x+w,y);
    for(float xi = x+0.07; xi < x+w-0.03; xi += 0.24) scene2_lineSeg(xi,y,xi,y-t);
    for(float xi = x+0.17; xi < x+w-0.1; xi += 0.48) scene2_lineSeg(xi,y-t,xi+0.1,y-t);
}

/* sky */
void scene2_drawSky()
{
    glColor3f(0.55,0.81,0.94);
    scene2_rectangle(0,0,20,10);

    /* sun (no rotating arm) */
    glColor3f(0.0,0.0,0.0);
    scene2_circle(1.2,8.9,0.52);
    glColor3f(0.97,0.82,0.12);
    scene2_circle(1.2,8.9,0.45);

    /* clouds */
    float cx[2] = { 3.6f + scene2_cloudPosition, 11.2f + scene2_cloudPosition };
    float cy[2] = { 8.8, 9.0 };
    for(int i = 0; i < 2; i++)
    {
        glColor3f(0.0,0.0,0.0);
        scene2_circle(cx[i]-0.45,cy[i],0.32); scene2_circle(cx[i],cy[i]+0.18,0.4); scene2_circle(cx[i]+0.45,cy[i],0.32);
        scene2_rectangle(cx[i]-0.72,cy[i]-0.28,cx[i]+0.72,cy[i]+0.06);
        glColor3f(1.0,1.0,1.0);
        scene2_circle(cx[i]-0.45,cy[i],0.27); scene2_circle(cx[i],cy[i]+0.18,0.35); scene2_circle(cx[i]+0.45,cy[i],0.27);
        scene2_rectangle(cx[i]-0.68,cy[i]-0.24,cx[i]+0.68,cy[i]+0.02);
    }

    /* birds */
    glColor3f(0.1,0.1,0.1);
    float bx[3] = { 6.6f + scene2_birdPosition, 7.3f + scene2_birdPosition, 7.9f + scene2_birdPosition };
    float by[3] = { 9.1, 8.7, 8.95 };
    for(int i = 0; i < 3; i++)
    {
        scene2_lineSeg(bx[i]-0.15,by[i]+0.07,bx[i],by[i]);
        scene2_lineSeg(bx[i],by[i],bx[i]+0.15,by[i]+0.07);
    }
}

/* metro rail : sizes taken from the reference sample */
void scene2_drawRail()
{
    /* upper wires */
    glColor3f(0.25,0.25,0.25);
    glBegin(GL_LINES);
    glVertex2f(0,6.95); glVertex2f(20,6.95);
    glVertex2f(0,7.20); glVertex2f(20,7.20);
    glVertex2f(0,7.45); glVertex2f(20,7.45);
    glEnd();

    /* wire supports */
    glColor3f(0.20,0.20,0.20);
    for(float x = 0; x <= 20; x += 3)
        scene2_lineSeg(x,6.90,x,7.50);

    /* wire connectors */
    for(float x = 2; x <= 20; x += 3)
        scene2_lineSeg(x,6.40,x,6.95);

    /* rail */
    glColor3f(0.12,0.12,0.12);
    scene2_lineSeg(0,6.40,20,6.40);

    /* deck */
    glColor3f(0.77,0.78,0.79); scene2_rectangle(0,5.6,20,6.0);
    glColor3f(0.65,0.66,0.67); scene2_rectangle(0,5.0,20,5.6);
    glColor3f(0.49,0.51,0.53); scene2_rectangle(0,4.55,20,5.0);

    /* pillars */
    glColor3f(0.60,0.63,0.65); scene2_rectangle(9.2,4.6,10.4,5.0);
    glColor3f(0.65,0.66,0.67); scene2_rectangle(9.4,2.4,10.2,4.6);
    glColor3f(0.55,0.57,0.59); scene2_rectangle(10.05,2.4,10.2,4.6);
    glColor3f(0.60,0.63,0.65); scene2_rectangle(16.2,4.6,17.4,5.0);
    glColor3f(0.65,0.66,0.67); scene2_rectangle(16.4,2.4,17.2,4.6);
}

/* train */
void scene2_drawTrain()
{
    glPushMatrix();
    glTranslatef(scene2_trainPosition,0.0f,0.0f);

    /* pantograph */
    glColor3f(0.13,0.13,0.13);
    scene2_lineSeg(9.0,6.55,9.25,6.95);
    scene2_lineSeg(9.25,6.95,9.5,6.55);

    /* roof + body */
    glColor3f(0.29,0.31,0.33); scene2_rectangle(0.5,6.55,12.0,6.68);
    glColor3f(0.96,0.96,0.95); scene2_rectangle(0.5,5.35,12.0,6.55);

    /* green nose (front, left) + windscreen */
    glColor3f(0.0,0.45,0.25);
    glBegin(GL_POLYGON);
    glVertex2f(0.5,5.35); glVertex2f(0.2,5.55);
    glVertex2f(0.2,6.35); glVertex2f(0.5,6.55);
    glEnd();
    glColor3f(0.14,0.15,0.16); scene2_rectangle(0.26,5.75,0.71,6.65);

    /* green skirt + maroon underline + undercarriage */
    glColor3f(0.0,0.45,0.25); scene2_rectangle(0.5,5.35,12.0,5.6);
    glColor3f(0.55,0.12,0.12); scene2_rectangle(0.5,5.30,12.0,5.35);
    glColor3f(0.24,0.26,0.28); scene2_rectangle(0.6,5.18,11.9,5.30);

    /* doors */
    float dx[3] = { 3.4, 6.0, 8.6 };
    for(int i = 0; i < 3; i++)
    {
        float x = dx[i];
        glColor3f(0.14,0.15,0.16); scene2_rectangle(x,5.6,x+0.8,6.45);
        glColor3f(0.96,0.96,0.95); scene2_rectangle(x+0.04,5.63,x+0.38,6.42); scene2_rectangle(x+0.42,5.63,x+0.76,6.42);
        glColor3f(0.62,0.79,0.89); scene2_rectangle(x+0.09,5.9,x+0.33,6.35); scene2_rectangle(x+0.47,5.9,x+0.71,6.35);
    }

    /* windows */
    glColor3f(0.62,0.79,0.89);
    for(float x = 1.1; x < 11.2; x += 1.3)
    {
        if(x > 3.2 && x < 4.4) continue;
        if(x > 5.8 && x < 7.0) continue;
        if(x > 8.4 && x < 9.6) continue;
        scene2_rectangle(x,5.9,x+0.75,6.35);
    }

    /* wheels */
    glColor3f(0.10,0.10,0.10);
    for(float x = 1.2; x <= 11.2; x += 1.2)
        scene2_circle(x,5.18,0.09);

    glPopMatrix();
}

/* brick buildings (left sliver + Curzon Hall) */
void scene2_archWindow(float x, float y, float w, float h)
{
    glColor3f(0.25,0.14,0.11);
    scene2_rectangle(x,y,x+w,y+h);
    scene2_circle(x+w/2,y+h,w/2);
}
void scene2_drawBuildings()
{
    /* left sliver */
    glColor3f(0.61,0.25,0.18);
    scene2_rectangle(0,2.3,1.6,4.3);
    scene2_rectangle(0.1,4.3,0.65,4.75);
    scene2_circle(0.37,4.75,0.26);
    glColor3f(0.25,0.14,0.11);
    scene2_archWindow(0.3,3.2,0.38,0.75);
    scene2_archWindow(1.0,3.2,0.38,0.75);

    /* Curzon corner towers + domes */
    glColor3f(0.55,0.21,0.15);
    scene2_rectangle(11.3,2.3,11.9,4.55);
    scene2_rectangle(19.2,2.3,19.8,4.55);
    scene2_circle(11.6,4.55,0.3);
    scene2_circle(19.5,4.55,0.3);
    glColor3f(0.13,0.13,0.13);
    scene2_lineSeg(11.6,4.85,11.6,5.0);
    scene2_lineSeg(19.5,4.85,19.5,5.0);

    /* facade */
    glColor3f(0.61,0.25,0.18);
    scene2_rectangle(11.9,2.3,19.2,4.2);

    /* central block + dome */
    glColor3f(0.55,0.21,0.15);
    scene2_rectangle(14.6,2.3,16.4,4.55);
    scene2_circle(15.5,4.55,0.68);
    glColor3f(0.13,0.13,0.13);
    scene2_lineSeg(15.5,5.23,15.5,5.43);
    scene2_circle(15.5,5.47,0.05);

    /* chhatris */
    glColor3f(0.61,0.25,0.18);
    scene2_rectangle(14.05,4.2,14.32,4.55); scene2_rectangle(16.68,4.2,16.95,4.55);
    scene2_circle(14.18,4.55,0.2); scene2_circle(16.82,4.55,0.2);

    /* balustrades */
    glColor3f(0.94,0.91,0.85);
    scene2_rectangle(11.9,3.35,19.2,3.5);
    scene2_rectangle(14.6,3.95,16.4,4.08);

    /* window rows */
    float ux[6] = { 12.2, 13.1, 14.0, 16.9, 17.8, 18.7 };
    for(int i = 0; i < 6; i++) scene2_archWindow(ux[i],3.55,0.45,0.7);
    float lx[8] = { 12.1, 13.0, 13.9, 14.8, 15.7, 16.6, 17.5, 18.4 };
    for(int i = 0; i < 8; i++) scene2_archWindow(lx[i],2.5,0.48,0.8);

    /* grand arch */
    glColor3f(0.25,0.14,0.11);
    scene2_rectangle(15.0,2.3,16.0,4.0);
    scene2_circle(15.5,4.0,0.5);

    /* roof line */
    glColor3f(0.13,0.13,0.13);
    scene2_lineSeg(11.3,4.2,19.8,4.2);
}

/* trees and hedges */
void scene2_tree(float x)
{
    glColor3f(0.35,0.18,0.08);
    scene2_rectangle(x-0.1,2.4,x+0.1,3.1);
    glColor3f(0.13,0.13,0.13);
    scene2_circle(x-0.55,3.3,0.6); scene2_circle(x,3.3,0.6); scene2_circle(x+0.55,3.35,0.6); scene2_circle(x,4.1,0.55);
    glColor3f(0.10,0.35,0.12);
    scene2_circle(x-0.55,3.3,0.55); scene2_circle(x,3.3,0.55); scene2_circle(x+0.55,3.35,0.55); scene2_circle(x,4.1,0.5);
}
void scene2_hedge(float x1, float x2)
{
    glColor3f(0.18,0.48,0.20);
    scene2_rectangle(x1,2.55,x2,2.95);
    for(float x = x1+0.17; x < x2; x += 0.38)
        scene2_circle(x,2.95,0.17);
}
void scene2_drawFoliage()
{
    scene2_tree(0.9);
    scene2_tree(9.6);
    scene2_hedge(8.1,11.3);
    scene2_hedge(18.6,20.0);
}

/* metro station building */
void scene2_drawStation()
{
    /* roof slab */
    glColor3f(0.43,0.45,0.47); scene2_rectangle(1.4,4.45,8.9,4.55);
    glColor3f(0.60,0.63,0.65); scene2_rectangle(1.4,4.35,8.9,4.45);

    /* glass wing */
    glColor3f(0.62,0.79,0.89); scene2_rectangle(7.5,2.3,8.9,4.35);
    glColor3f(0.93,0.96,0.98);
    scene2_lineSeg(7.95,2.3,7.95,4.35);
    scene2_lineSeg(8.4,2.3,8.4,4.35);
    scene2_lineSeg(7.5,3.6,8.9,3.0);
    scene2_lineSeg(7.5,2.9,8.9,2.3);

    /* wall */
    glColor3f(0.93,0.93,0.92); scene2_rectangle(1.4,2.3,7.5,4.35);

    /* sign board */
    glColor3f(0.65,0.31,0.16); scene2_rectangle(1.42,3.5,7.48,4.35);
    glColor3f(0.97,0.95,0.89); scene2_rectangle(1.52,3.62,7.38,4.23);
    glColor3f(0.04,0.35,0.16);
    scene2_bengali(2.6,4.13,3.7,0.08);
    scene2_text(1.64,3.78,"DHAKA UNIVERSITY METRO STATION",GLUT_BITMAP_HELVETICA_18);

    /* entrance */
    glColor3f(0.37,0.39,0.41); scene2_rectangle(2.6,2.3,6.4,3.5);
    glColor3f(0.05,0.48,0.24); scene2_rectangle(2.6,3.2,6.4,3.5);
    glColor3f(1.0,1.0,1.0);
    scene2_lineSeg(2.98,3.44,2.98,3.26); scene2_lineSeg(2.98,3.26,2.9,3.33); scene2_lineSeg(2.98,3.26,3.06,3.33);
    scene2_lineSeg(6.2,3.26,6.2,3.44); scene2_lineSeg(6.2,3.44,6.12,3.37); scene2_lineSeg(6.2,3.44,6.28,3.37);
    scene2_text(3.2,3.28,"Entrance",GLUT_BITMAP_HELVETICA_12);
    scene2_text(5.35,3.28,"Exit",GLUT_BITMAP_HELVETICA_12);

    /* fare gates */
    for(int i = 0; i < 4; i++)
    {
        float x = 3.2 + i*0.72;
        glColor3f(0.55,0.57,0.58); scene2_rectangle(x,2.55,x+0.45,3.0);
        glColor3f(0.14,0.15,0.16); scene2_rectangle(x,2.92,x+0.45,3.0);
    }

    /* steps */
    glColor3f(0.77,0.78,0.79); scene2_rectangle(2.4,2.5,6.6,2.62);
    glColor3f(0.69,0.70,0.71); scene2_rectangle(2.3,2.4,6.7,2.5);
    glColor3f(0.77,0.78,0.79); scene2_rectangle(2.2,2.3,6.8,2.4);

    /* handrails */
    glColor3f(0.93,0.93,0.92);
    scene2_lineSeg(2.6,2.75,2.3,2.3);
    scene2_lineSeg(6.4,2.75,6.7,2.3);

    /* stone monument + DU sign */
    glColor3f(0.77,0.78,0.79);
    scene2_rectangle(15.85,2.95,16.25,3.08); scene2_rectangle(15.92,2.45,16.18,2.95); scene2_rectangle(15.85,2.32,16.25,2.45);
    glColor3f(0.60,0.63,0.65); scene2_rectangle(18.55,2.3,18.7,3.1);
    glColor3f(1.0,1.0,1.0);     scene2_rectangle(16.5,3.1,18.9,4.0);
    glColor3f(0.04,0.42,0.23);  scene2_rectangle(16.55,3.15,18.85,3.95);
    glColor3f(1.0,1.0,1.0);
    scene2_bengali(16.95,3.84,1.5,0.08);
    scene2_text(16.72,3.42,"DHAKA UNIVERSITY",GLUT_BITMAP_HELVETICA_12);
}

/* grass, pavement, fences */
void scene2_drawGround()
{
    glColor3f(0.50,0.75,0.42);
    scene2_rectangle(0,2.4,1.6,3.0);
    scene2_rectangle(12.6,2.4,15.9,2.85);
    glColor3f(0.33,0.55,0.28);
    scene2_lineSeg(12.6,2.85,15.9,2.85);

    glColor3f(0.73,0.74,0.75); scene2_rectangle(0,1.8,20,2.4);

    glColor3f(0.10,0.10,0.10);
    scene2_lineSeg(0,2.55,1.8,2.55); scene2_lineSeg(0,3.0,1.8,3.0);
    for(float x = 0.04; x <= 1.8; x += 0.12) scene2_lineSeg(x,2.5,x,3.05);
    scene2_lineSeg(18.6,2.55,20,2.55); scene2_lineSeg(18.6,3.0,20,3.0);
    for(float x = 18.64; x <= 20; x += 0.12) scene2_lineSeg(x,2.5,x,3.05);
}

/* pedestrians */
void scene2_person(float x, float y, float sr, float sg, float sb)
{
    glColor3f(0.13,0.13,0.13); scene2_circle(x,y,0.13);
    glColor3f(0.95,0.78,0.61); scene2_circle(x,y-0.03,0.10);
    glColor3f(sr,sg,sb);       scene2_rectangle(x-0.12,y-0.45,x+0.12,y-0.22);
    glColor3f(0.13,0.13,0.13);
    scene2_lineSeg(x-0.12,y-0.27,x-0.19,y-0.58);
    scene2_lineSeg(x+0.12,y-0.27,x+0.19,y-0.58);
    scene2_lineSeg(x-0.05,y-0.45,x-0.15,y-0.85);
    scene2_lineSeg(x+0.05,y-0.45,x+0.15,y-0.85);
}
void scene2_drawPeople()
{
    scene2_person(4.8,3.1,0.23,0.43,0.65);
    scene2_person(6.1,3.1,0.90,0.56,0.64);
    scene2_person(9.4,3.15,0.90,0.56,0.64);
    scene2_person(11.0,3.15,0.48,0.31,0.55);
    scene2_person(13.9,3.1,0.48,0.31,0.55);
    scene2_person(15.1,3.1,0.91,0.77,0.28);
}

/* road */
void scene2_drawRoad()
{
    glColor3f(0.35,0.35,0.36); scene2_rectangle(0,0,20,1.8);

    for(float x = 0; x < 20; x += 1.2)
    {
        glColor3f(0.10,0.10,0.10); scene2_rectangle(x,1.68,x+0.6,1.8);
        glColor3f(0.95,0.95,0.95); scene2_rectangle(x+0.6,1.68,x+1.2,1.8);
    }
    glColor3f(0.95,0.95,0.95);
    for(float x = 0.2; x < 20; x += 1.5) scene2_rectangle(x,0.85,x+0.7,0.97);
}

/* scene2_wheel */
void scene2_wheel(float cx, float cy, float r)
{
    glColor3f(0.10,0.10,0.10); scene2_circle(cx,cy,r+0.04); scene2_circle(cx,cy,r);
    glColor3f(0.77,0.78,0.79); scene2_circle(cx,cy,r*0.45);
}

/* street vehicles */
void scene2_drawVehicles()
{
    /* green bus */
    glPushMatrix(); glTranslatef(scene2_bus1Position,0,0);
    glColor3f(0.10,0.10,0.10); scene2_rectangle(0.9,0.3,5.74,1.5);
    glColor3f(0.12,0.54,0.23); scene2_rectangle(0.93,0.33,5.71,1.47);
    glColor3f(0.09,0.42,0.17); scene2_rectangle(0.93,1.36,5.71,1.47);
    glColor3f(0.62,0.79,0.89);
    for(int i = 0; i < 5; i++) scene2_rectangle(1.15+i*0.78,0.85,1.75+i*0.78,1.35);
    scene2_rectangle(5.0,0.82,5.6,1.37);
    glColor3f(0.13,0.13,0.13); scene2_lineSeg(4.95,0.35,4.95,1.45);
    glColor3f(0.76,0.22,0.17); scene2_rectangle(0.93,0.62,5.71,0.75);
    glColor3f(0.97,0.82,0.12); scene2_rectangle(0.93,0.55,5.71,0.62);
    scene2_wheel(2.1,0.3,0.28); scene2_wheel(4.6,0.3,0.28);
    glPopMatrix();

    /* white car */
    glPushMatrix(); glTranslatef(scene2_carPosition,0,0);
    glColor3f(0.10,0.10,0.10);
    scene2_rectangle(8.4,0.35,12.15,1.15);
    glBegin(GL_TRIANGLES);
    glVertex2f(8.97,1.12); glVertex2f(9.4,1.45); glVertex2f(11.6,1.12);
    glVertex2f(8.97,1.12); glVertex2f(11.1,1.45); glVertex2f(11.6,1.12);
    glEnd();
    glColor3f(0.96,0.96,0.95); scene2_rectangle(8.43,0.38,12.12,1.12);
    glBegin(GL_QUADS);
    glVertex2f(9.0,1.12); glVertex2f(9.4,1.42); glVertex2f(11.1,1.42); glVertex2f(11.5,1.12);
    glEnd();
    glColor3f(0.62,0.79,0.89); scene2_rectangle(9.5,1.16,10.2,1.38); scene2_rectangle(10.3,1.16,11.05,1.38);
    glColor3f(0.97,0.82,0.12); scene2_rectangle(12.0,0.62,12.1,0.77);
    glColor3f(0.80,0.15,0.15); scene2_rectangle(8.43,0.62,8.53,0.77);
    scene2_wheel(9.3,0.35,0.24); scene2_wheel(11.2,0.35,0.24);
    glPopMatrix();

    /* CNG auto rickshaw */
    glPushMatrix(); glTranslatef(scene2_cngPosition,0,0);
    glColor3f(0.10,0.10,0.10); scene2_rectangle(14.9,0.4,17.52,1.68);
    glColor3f(0.14,0.15,0.16); scene2_rectangle(14.93,1.25,17.49,1.65);
    glColor3f(0.12,0.54,0.23); scene2_rectangle(14.93,0.43,17.49,1.25);
    glColor3f(0.14,0.15,0.16); scene2_rectangle(15.07,1.0,16.07,1.34);
    glColor3f(0.62,0.79,0.89); scene2_rectangle(16.98,1.05,17.36,1.41);
    scene2_wheel(15.5,0.4,0.2); scene2_wheel(16.98,0.4,0.2);
    glPopMatrix();

    /* second green bus (far lane) */
    glPushMatrix(); glTranslatef(scene2_bus2Position,0,0);
    glColor3f(0.10,0.10,0.10); scene2_rectangle(17.4,0.95,20.0,2.55);
    glColor3f(0.12,0.54,0.23); scene2_rectangle(17.43,0.98,19.97,2.52);
    glColor3f(0.62,0.79,0.89);
    for(int i = 0; i < 4; i++) scene2_rectangle(17.6+i*0.62,1.9,18.08+i*0.62,2.35);
    glColor3f(0.97,0.82,0.12); scene2_rectangle(17.43,1.5,19.97,1.68);
    scene2_wheel(18.1,0.98,0.25); scene2_wheel(19.6,0.98,0.25);
    glPopMatrix();
}

/* animation */
void scene2_update(int value)
{
    /* train runs left along the viaduct */
    scene2_trainPosition -= scene2_trainSpeed;
    if(12.0 + scene2_trainPosition < -0.6)
        scene2_trainPosition = 20.6;

    /* street traffic runs right */
    scene2_bus1Position += scene2_bus1Speed; if(0.9 + scene2_bus1Position > 20.6)  scene2_bus1Position = -6.6;
    scene2_carPosition  += scene2_carSpeed;  if(8.4 + scene2_carPosition > 20.6)   scene2_carPosition = -12.9;
    scene2_cngPosition  += scene2_cngSpeed;  if(14.9 + scene2_cngPosition > 20.6)  scene2_cngPosition = -18.3;
    scene2_bus2Position += scene2_bus2Speed; if(17.4 + scene2_bus2Position > 20.6) scene2_bus2Position = -23.3;

    /* clouds and birds drift */
    scene2_cloudPosition += scene2_cloudSpeed; if(scene2_cloudPosition > 1.5) scene2_cloudPosition = -1.5;
    scene2_birdPosition += scene2_birdSpeed;   if(scene2_birdPosition > 1.5)  scene2_birdPosition = -1.5;

    if(activeScene == 2)
        updateMetroSound((scene2_trainPosition + 12.0f > 0.0f) &&
                         (scene2_trainPosition + 0.2f < 20.0f));

    glutPostRedisplay();
    glutTimerFunc(30, scene2_update, 0);
}

/* scene2_display */
void scene2_display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    scene2_drawSky();
    scene2_drawRail();
    scene2_drawTrain();

    /* track line */
    glColor3f(0.10,0.10,0.10);
    scene2_lineSeg(0.2,5.18,20.0,5.18);

    scene2_drawBuildings();
    scene2_drawFoliage();
    scene2_drawStation();
    scene2_drawGround();
    scene2_drawPeople();
    scene2_drawRoad();
    scene2_drawVehicles();

    glFlush();
}

/* initialization */
void scene2_init()
{
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,20,0,10);
}

/* scene2_main */

//sadia
// Global animation position variables
GLfloat scene3_trainPos = 1.0f;
GLfloat scene3_busPos = 1.2f;
GLfloat scene3_carPos = -1.4f;
GLfloat scene3_cngPos = 1.5f;

// Pedestrian position & walking cycle variables
GLfloat scene3_person1Pos = -0.8f;
GLfloat scene3_person2Pos = -0.6f;
GLfloat scene3_person3Pos = 0.4f;
GLfloat scene3_person4Pos = 0.6f;
GLfloat scene3_walkAngle = 0.0f; // Controls leg swinging animation

// Speeds for animated objects
GLfloat scene3_speedTrain = 0.015f;
GLfloat scene3_speedBus = 0.010f;
GLfloat scene3_speedCar = 0.018f;
GLfloat scene3_speedCng = 0.012f;
GLfloat scene3_speedWalk = 0.003f;

void scene3_update(int value) {
    // Metro train animation loop (Right to Left)
    if (scene3_trainPos < -2.2f)
        scene3_trainPos = 1.2f;
    scene3_trainPos -= scene3_speedTrain;

    // Bus animation loop (Right to Left)
    if (scene3_busPos < -1.8f)
        scene3_busPos = 1.8f;
    scene3_busPos -= scene3_speedBus;

    // Car animation loop (Left to Right)
    if (scene3_carPos > 1.8f)
        scene3_carPos = -1.8f;
    scene3_carPos += scene3_speedCar;

    // CNG animation loop (Right to Left)
    if (scene3_cngPos < -1.8f)
        scene3_cngPos = 1.8f;
    scene3_cngPos -= scene3_speedCng;

    // Pedestrian Movement & Leg Swinging
    scene3_walkAngle += 0.2f; // Step cycle increment

    scene3_person1Pos += scene3_speedWalk;
    if (scene3_person1Pos > 0.9f) scene3_person1Pos = -0.9f;

    scene3_person2Pos += scene3_speedWalk;
    if (scene3_person2Pos > 0.9f) scene3_person2Pos = -0.9f;

    scene3_person3Pos -= scene3_speedWalk;
    if (scene3_person3Pos < -0.9f) scene3_person3Pos = 0.9f;

    scene3_person4Pos -= scene3_speedWalk;
    if (scene3_person4Pos < -0.9f) scene3_person4Pos = 0.9f;

    if(activeScene == 3)
        updateMetroSound((scene3_trainPos + 0.9f > -1.0f) &&
                         (scene3_trainPos - 0.2f < 1.0f));

    glutPostRedisplay();
    glutTimerFunc(30, scene3_update, 0);
}

void scene3_init() {
    glClearColor(0.53f, 0.81f, 0.98f, 1.0f); // Light sky blue
}

void scene3_drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        glVertex2f(cx + r * cosf(theta), cy + r * sinf(theta));
    }
    glEnd();
}

void scene3_drawTree(float x, float y) {
    // Trunk
    glColor3f(0.4f, 0.25f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.015f, y);
        glVertex2f(x + 0.015f, y);
        glVertex2f(x + 0.015f, y + 0.12f);
        glVertex2f(x - 0.015f, y + 0.12f);
    glEnd();

    // Foliage
    glColor3f(0.15f, 0.6f, 0.2f);
    scene3_drawCircle(x, y + 0.18f, 0.07f, 20);
    scene3_drawCircle(x - 0.04f, y + 0.15f, 0.05f, 20);
    scene3_drawCircle(x + 0.04f, y + 0.15f, 0.05f, 20);
}

// Animated Pedestrian Function
void scene3_drawAnimatedPerson(float x, float y, float r, float g, float b, float legAngle) {
    glPushMatrix();
        glTranslatef(x, y, 0.0f);

        // Head
        glColor3f(0.9f, 0.75f, 0.65f);
        scene3_drawCircle(0.0f, 0.06f, 0.015f, 15);

        // Shirt
        glColor3f(r, g, b);
        glBegin(GL_QUADS);
            glVertex2f(-0.015f, 0.01f);
            glVertex2f(0.015f, 0.01f);
            glVertex2f(0.012f, 0.045f);
            glVertex2f(-0.012f, 0.045f);
        glEnd();

        // Animated Swinging Legs
        float legSwing = sinf(legAngle) * 0.015f;
        glColor3f(0.15f, 0.15f, 0.2f);
        glLineWidth(2.5f);
        glBegin(GL_LINES);
            // Left Leg
            glVertex2f(-0.006f, 0.01f);
            glVertex2f(-0.006f + legSwing, -0.03f);
            // Right Leg
            glVertex2f(0.006f, 0.01f);
            glVertex2f(0.006f - legSwing, -0.03f);
        glEnd();
    glPopMatrix();
}

void scene3_display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // 1. Sun and Clouds
    glColor3f(1.0f, 0.85f, 0.0f);
    scene3_drawCircle(-0.85f, 0.85f, 0.08f, 30);

    glColor3f(1.0f, 1.0f, 1.0f);
    scene3_drawCircle(-0.5f, 0.8f, 0.06f, 20);
    scene3_drawCircle(-0.43f, 0.82f, 0.08f, 20);
    scene3_drawCircle(-0.36f, 0.8f, 0.06f, 20);

    scene3_drawCircle(0.4f, 0.82f, 0.05f, 20);
    scene3_drawCircle(0.46f, 0.84f, 0.07f, 20);
    scene3_drawCircle(0.52f, 0.82f, 0.05f, 20);

    // 2. Background Buildings
    glColor3f(0.72f, 0.78f, 0.82f);
    glBegin(GL_QUADS);
        glVertex2f(-0.95f, -0.2f); glVertex2f(-0.85f, -0.2f); glVertex2f(-0.85f, 0.2f); glVertex2f(-0.95f, 0.2f);
        glVertex2f(0.6f, -0.2f);   glVertex2f(0.72f, -0.2f);  glVertex2f(0.72f, 0.25f); glVertex2f(0.6f, 0.25f);
        glVertex2f(0.85f, -0.2f);  glVertex2f(0.98f, -0.2f);  glVertex2f(0.98f, 0.18f); glVertex2f(0.85f, 0.18f);
    glEnd();

    // 3. Elevated Metro Track & Pillars
    glColor3f(0.6f, 0.62f, 0.65f);
    glBegin(GL_QUADS);
        glVertex2f(-0.8f, -0.2f); glVertex2f(-0.7f, -0.2f); glVertex2f(-0.7f, 0.5f); glVertex2f(-0.8f, 0.5f);
        glVertex2f(0.7f, -0.2f);  glVertex2f(0.8f, -0.2f);  glVertex2f(0.8f, 0.5f);  glVertex2f(0.7f, 0.5f);
    glEnd();

    // Viaduct Deck
    glColor3f(0.75f, 0.75f, 0.77f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, 0.45f); glVertex2f(1.0f, 0.45f); glVertex2f(1.0f, 0.58f); glVertex2f(-1.0f, 0.58f);
    glEnd();

    // 4. Metro Train Animation (Right to Left)
    glPushMatrix();
        glTranslatef(scene3_trainPos, 0.0f, 0.0f);

        // Train Body
        glColor3f(0.9f, 0.92f, 0.93f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.2f, 0.59f); glVertex2f(0.9f, 0.59f);
            glVertex2f(0.9f, 0.80f);  glVertex2f(-0.16f, 0.80f);
            glVertex2f(-0.2f, 0.72f);
        glEnd();

        // Green Stripe
        glColor3f(0.0f, 0.5f, 0.25f);
        glBegin(GL_QUADS);
            glVertex2f(-0.19f, 0.76f); glVertex2f(0.9f, 0.76f); glVertex2f(0.9f, 0.79f); glVertex2f(-0.17f, 0.79f);
        glEnd();

        // Windows
        glColor3f(0.4f, 0.65f, 0.8f);
        for(float wx = -0.1f; wx <= 0.8f; wx += 0.12f) {
            glBegin(GL_QUADS);
                glVertex2f(wx, 0.67f); glVertex2f(wx + 0.08f, 0.67f);
                glVertex2f(wx + 0.08f, 0.75f); glVertex2f(wx, 0.75f);
            glEnd();
        }
    glPopMatrix();

    // Track Railing
    glColor3f(0.2f, 0.3f, 0.4f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(-1.0f, 0.60f); glVertex2f(1.0f, 0.60f);
        glVertex2f(-1.0f, 0.58f); glVertex2f(1.0f, 0.58f);
    glEnd();

    // 5. Mirpur 10 Station Structure
    glColor3f(0.94f, 0.9f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(-0.6f, -0.3f); glVertex2f(0.6f, -0.3f); glVertex2f(0.6f, 0.2f); glVertex2f(-0.6f, 0.2f);
    glEnd();

    // Roof Line
    glColor3f(0.2f, 0.4f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(-0.62f, 0.2f); glVertex2f(0.62f, 0.2f); glVertex2f(0.62f, 0.23f); glVertex2f(-0.62f, 0.23f);
    glEnd();

    // Signboard
    glColor3f(0.9f, 0.92f, 0.86f);
    glBegin(GL_QUADS);
        glVertex2f(-0.5f, 0.22f); glVertex2f(0.5f, 0.22f); glVertex2f(0.5f, 0.44f); glVertex2f(-0.5f, 0.44f);
    glEnd();

    // Signboard Border
    glColor3f(0.2f, 0.2f, 0.2f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.5f, 0.22f); glVertex2f(0.5f, 0.22f); glVertex2f(0.5f, 0.44f); glVertex2f(-0.5f, 0.44f);
    glEnd();

    // Metro Logo Icon
    glColor3f(0.0f, 0.5f, 0.25f); scene3_drawCircle(-0.3f, 0.33f, 0.07f, 30);
    glColor3f(0.85f, 0.1f, 0.1f); scene3_drawCircle(-0.3f, 0.33f, 0.05f, 30);
    glColor3f(0.9f, 0.92f, 0.86f); scene3_drawCircle(-0.3f, 0.33f, 0.03f, 30);

    // Station Name Block
    glColor3f(0.0f, 0.4f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.32f); glVertex2f(0.35f, 0.32f); glVertex2f(0.35f, 0.37f); glVertex2f(-0.15f, 0.37f);
    glEnd();

    // Station Windows
    glColor3f(0.4f, 0.65f, 0.85f);
    glBegin(GL_QUADS);
        glVertex2f(-0.52f, -0.1f); glVertex2f(-0.43f, -0.1f); glVertex2f(-0.43f, 0.12f); glVertex2f(-0.52f, 0.12f);
        glVertex2f(-0.38f, -0.1f); glVertex2f(-0.29f, -0.1f); glVertex2f(-0.29f, 0.12f); glVertex2f(-0.38f, 0.12f);
        glVertex2f(0.29f, -0.1f);  glVertex2f(0.38f, -0.1f);  glVertex2f(0.38f, 0.12f);  glVertex2f(0.29f, 0.12f);
        glVertex2f(0.43f, -0.1f);  glVertex2f(0.52f, -0.1f);  glVertex2f(0.52f, 0.12f);  glVertex2f(0.43f, 0.12f);
    glEnd();

    // Entrance
    glColor3f(0.25f, 0.28f, 0.26f);
    glBegin(GL_QUADS);
        glVertex2f(-0.22f, 0.0f); glVertex2f(0.22f, 0.0f); glVertex2f(0.22f, 0.12f); glVertex2f(-0.22f, 0.12f);
    glEnd();

    glColor3f(0.15f, 0.15f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-0.22f, -0.3f); glVertex2f(0.22f, -0.3f); glVertex2f(0.22f, 0.0f); glVertex2f(-0.22f, 0.0f);
    glEnd();

    // Station Stairs
    glColor3f(0.7f, 0.7f, 0.72f);
    for(int step = 0; step < 6; step++) {
        float y_pos = -0.45f + step * 0.025f;
        float offset = step * 0.015f;
        glBegin(GL_QUADS);
            glVertex2f(-0.28f + offset, y_pos);
            glVertex2f(0.28f - offset, y_pos);
            glVertex2f(0.28f - offset, y_pos + 0.025f);
            glVertex2f(-0.28f + offset, y_pos + 0.025f);
        glEnd();
    }

    // 6. Side Trees and Fence
    scene3_drawTree(-0.85f, -0.3f);
    scene3_drawTree(0.85f, -0.3f);

    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(-1.0f, -0.28f); glVertex2f(1.0f, -0.28f);
        glVertex2f(-1.0f, -0.23f); glVertex2f(1.0f, -0.23f);
        for(float fx = -1.0f; fx <= 1.0f; fx += 0.03f) {
            glVertex2f(fx, -0.3f); glVertex2f(fx, -0.18f);
        }
    glEnd();

    // 7. Footpath and Road
    for(float bx = -1.0f; bx < 1.0f; bx += 0.08f) {
        glColor3f(0.1f, 0.1f, 0.1f);
        glBegin(GL_QUADS);
            glVertex2f(bx, -0.48f); glVertex2f(bx + 0.04f, -0.48f);
            glVertex2f(bx + 0.04f, -0.45f); glVertex2f(bx, -0.45f);
        glEnd();
        glColor3f(0.9f, 0.9f, 0.9f);
        glBegin(GL_QUADS);
            glVertex2f(bx + 0.04f, -0.48f); glVertex2f(bx + 0.08f, -0.48f);
            glVertex2f(bx + 0.08f, -0.45f); glVertex2f(bx + 0.04f, -0.45f);
        glEnd();
    }

    // Animated Pedestrians walking on the footpath
    scene3_drawAnimatedPerson(scene3_person1Pos, -0.44f, 0.1f, 0.4f, 0.8f, scene3_walkAngle);
    scene3_drawAnimatedPerson(scene3_person2Pos, -0.44f, 0.8f, 0.2f, 0.4f, -scene3_walkAngle);
    scene3_drawAnimatedPerson(scene3_person3Pos, -0.44f, 0.4f, 0.1f, 0.6f, scene3_walkAngle);
    scene3_drawAnimatedPerson(scene3_person4Pos, -0.44f, 0.9f, 0.7f, 0.1f, -scene3_walkAngle);

    // Asphalt Road
    glColor3f(0.3f, 0.3f, 0.32f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f); glVertex2f(1.0f, -1.0f); glVertex2f(1.0f, -0.48f); glVertex2f(-1.0f, -0.48f);
    glEnd();

    // Road Markings
    glColor3f(1.0f, 1.0f, 1.0f);
    for(float rx = -0.9f; rx < 1.0f; rx += 0.2f) {
        glBegin(GL_QUADS);
            glVertex2f(rx, -0.74f); glVertex2f(rx + 0.1f, -0.74f);
            glVertex2f(rx + 0.1f, -0.72f); glVertex2f(rx, -0.72f);
        glEnd();
    }

    // 8. Vehicle Animations

    // Green Bus (Right to Left)
    glPushMatrix();
        glTranslatef(scene3_busPos, 0.0f, 0.0f);

        glColor3f(0.1f, 0.55f, 0.25f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.35f, -0.88f); glVertex2f(-0.9f, -0.88f);
            glVertex2f(-0.9f, -0.68f);  glVertex2f(-0.87f, -0.62f);
            glVertex2f(-0.35f, -0.62f);
        glEnd();

        glColor3f(0.85f, 0.15f, 0.1f);
        glBegin(GL_QUADS);
            glVertex2f(-0.9f, -0.8f); glVertex2f(-0.35f, -0.8f);
            glVertex2f(-0.35f, -0.77f); glVertex2f(-0.9f, -0.77f);
        glEnd();

        glColor3f(0.5f, 0.75f, 0.85f);
        for(float bw = -0.85f; bw <= -0.45f; bw += 0.1f) {
            glBegin(GL_QUADS);
                glVertex2f(bw, -0.74f); glVertex2f(bw + 0.07f, -0.74f);
                glVertex2f(bw + 0.07f, -0.64f); glVertex2f(bw, -0.64f);
            glEnd();
        }

        glColor3f(0.15f, 0.15f, 0.15f);
        scene3_drawCircle(-0.78f, -0.88f, 0.045f, 20);
        scene3_drawCircle(-0.48f, -0.88f, 0.045f, 20);
    glPopMatrix();

    // Car (Left to Right)
    glPushMatrix();
        glTranslatef(scene3_carPos, 0.0f, 0.0f);

        glColor3f(0.95f, 0.95f, 0.95f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.2f, -0.92f); glVertex2f(0.25f, -0.92f);
            glVertex2f(0.23f, -0.82f); glVertex2f(0.16f, -0.72f);
            glVertex2f(-0.08f, -0.72f); glVertex2f(-0.15f, -0.82f);
        glEnd();

        glColor3f(0.2f, 0.45f, 0.65f);
        glBegin(GL_QUADS);
            glVertex2f(-0.06f, -0.8f); glVertex2f(0.02f, -0.8f);
            glVertex2f(0.02f, -0.74f);  glVertex2f(-0.04f, -0.74f);

            glVertex2f(0.04f, -0.8f);  glVertex2f(0.14f, -0.8f);
            glVertex2f(0.12f, -0.74f);  glVertex2f(0.04f, -0.74f);
        glEnd();

        glColor3f(0.15f, 0.15f, 0.15f);
        scene3_drawCircle(-0.1f, -0.92f, 0.04f, 20);
        scene3_drawCircle(0.15f, -0.92f, 0.04f, 20);
    glPopMatrix();

    // CNG Auto-Rickshaw (Right to Left)
    glPushMatrix();
        glTranslatef(scene3_cngPos, 0.0f, 0.0f);

        glColor3f(0.0f, 0.5f, 0.2f);
        glBegin(GL_POLYGON);
            glVertex2f(0.2f, -0.93f);  glVertex2f(-0.1f, -0.93f);
            glVertex2f(-0.08f, -0.8f); glVertex2f(-0.02f, -0.7f);
            glVertex2f(0.18f, -0.7f);  glVertex2f(0.2f, -0.8f);
        glEnd();

        glColor3f(0.15f, 0.15f, 0.15f);
        glBegin(GL_QUADS);
            glVertex2f(0.19f, -0.72f); glVertex2f(-0.03f, -0.72f);
            glVertex2f(-0.02f, -0.69f); glVertex2f(0.18f, -0.69f);
        glEnd();

        glColor3f(0.6f, 0.8f, 0.9f);
        glBegin(GL_QUADS);
            glVertex2f(0.15f, -0.82f); glVertex2f(-0.02f, -0.82f);
            glVertex2f(0.0f, -0.74f);   glVertex2f(0.14f, -0.74f);
        glEnd();

        glColor3f(0.15f, 0.15f, 0.15f);
        scene3_drawCircle(0.15f, -0.93f, 0.03f, 20);
        scene3_drawCircle(-0.05f, -0.93f, 0.035f, 20);
    glPopMatrix();

    glFlush();
}

//kaif


GLfloat scene4_position = 0.0f;
GLfloat scene4_speed = 0.1f;
GLfloat scene4_trainPosition = 0.0f;
GLfloat scene4_dayNight = 0.0f;

void scene4_update(int value)
{
    if(scene4_position > 20.0f)
        scene4_position = -20.0f;

    scene4_position = scene4_position + scene4_speed;

    if(scene4_trainPosition > 14.7f)
        scene4_trainPosition = -13.7f;

    scene4_trainPosition = scene4_trainPosition + scene4_speed;

    scene4_dayNight = scene4_dayNight + 0.005f;

    if(scene4_dayNight > 2.0f)
        scene4_dayNight = 0.0f;

    if(activeScene == 4)
        updateMetroSound((14.62f - scene4_trainPosition > 0.0f) &&
                         (6.33f - scene4_trainPosition < 20.0f));

    glutPostRedisplay();
    glutTimerFunc(100, scene4_update, 0);
}

// =====================================================
// Draw Text
// =====================================================
void scene4_drawText(const char *text, float x, float y)
{
    glRasterPos2f(x, y);

    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

// =====================================================
// Draw Window
// =====================================================
void scene4_drawWindow(float x, float y)
{
    // Frame
    glColor3f(0.88f, 0.86f, 0.78f);

    glBegin(GL_QUADS);

        glVertex2f(x, y);
        glVertex2f(x + 0.34f, y);
        glVertex2f(x + 0.34f, y + 0.36f);
        glVertex2f(x, y + 0.36f);

    glEnd();

    // Blue glass
    glColor3f(0.10f, 0.34f, 0.49f);

    glBegin(GL_QUADS);

        glVertex2f(x + 0.04f, y + 0.04f);
        glVertex2f(x + 0.30f, y + 0.04f);
        glVertex2f(x + 0.30f, y + 0.32f);
        glVertex2f(x + 0.04f, y + 0.32f);

    glEnd();

    // Middle line
    glColor3f(0.55f, 0.72f, 0.78f);

    glBegin(GL_LINES);

        glVertex2f(x + 0.17f, y + 0.04f);
        glVertex2f(x + 0.17f, y + 0.32f);

    glEnd();
}

// =====================================================
// Draw Vehicle Wheel
// =====================================================
void scene4_drawVehicleWheel(float x, float y, float radius)
{
    // Tire
    glColor3f(0.04f, 0.04f, 0.04f);

    glBegin(GL_POLYGON);

    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416f / 180.0f;

        glVertex2f(
            x + radius * cos(angle),
            y + radius * sin(angle)
        );
    }

    glEnd();

    // Rim
    glColor3f(0.52f, 0.53f, 0.52f);

    glBegin(GL_POLYGON);

    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416f / 180.0f;

        glVertex2f(
            x + radius * 0.46f * cos(angle),
            y + radius * 0.46f * sin(angle)
        );
    }

    glEnd();

    // Centre
    glColor3f(0.15f, 0.16f, 0.16f);

    glBegin(GL_POLYGON);

    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416f / 180.0f;

        glVertex2f(
            x + radius * 0.18f * cos(angle),
            y + radius * 0.18f * sin(angle)
        );
    }

    glEnd();
}

// =====================================================
// Initialization
// =====================================================
void scene4_init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, 20, 0, 10);
}

// =====================================================
// Display
// =====================================================
void scene4_display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float light;

    if(scene4_dayNight < 1.0f)
        light = 1.0f - scene4_dayNight;
    else
        light = scene4_dayNight - 1.0f;

    // =================================================
    // SKY
    // =================================================

    glColor3f(
        0.03f + 0.27f * light,
        0.05f + 0.63f * light,
        0.15f + 0.79f * light
    );

    glBegin(GL_QUADS);

        glVertex2f(0, 5.2f);
        glVertex2f(20, 5.2f);
        glVertex2f(20, 10);
        glVertex2f(0, 10);

    glEnd();

    // =================================================
    // SUN AND MOON
    // =================================================

    if(light >= 0.5f)
        glColor3f(1.0f, 0.78f, 0.05f);
    else
        glColor3f(0.92f, 0.94f, 0.88f);

    glBegin(GL_POLYGON);

    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416f / 180.0f;

        glVertex2f(
            18.2f + 0.45f * cos(angle),
            9.25f + 0.45f * sin(angle)
        );
    }

    glEnd();

    // =================================================
    // CLOUDS
    // =================================================

    glPushMatrix();
    glTranslatef(scene4_position, 0.0f, 0.0f);

    glColor3f(1, 1, 1);

    float cloudX[4] = {1.0f, 4.6f, 10.5f, 17.7f};
    float cloudY[4] = {9.25f, 8.85f, 9.10f, 8.90f};

    for (int c = 0; c < 4; c++)
    {
        // Left cloud
        glBegin(GL_POLYGON);

        for (int i = 0; i <= 360; i++)
        {
            float angle = i * 3.1416f / 180.0f;

            glVertex2f(
                cloudX[c] - 0.35f + 0.35f * cos(angle),
                cloudY[c] + 0.28f * sin(angle)
            );
        }

        glEnd();

        // Middle cloud
        glBegin(GL_POLYGON);

        for (int i = 0; i <= 360; i++)
        {
            float angle = i * 3.1416f / 180.0f;

            glVertex2f(
                cloudX[c] + 0.10f + 0.48f * cos(angle),
                cloudY[c] + 0.42f * sin(angle)
            );
        }

        glEnd();

        // Right cloud
        glBegin(GL_POLYGON);

        for (int i = 0; i <= 360; i++)
        {
            float angle = i * 3.1416f / 180.0f;

            glVertex2f(
                cloudX[c] + 0.58f + 0.34f * cos(angle),
                cloudY[c] + 0.25f * sin(angle)
            );
        }

        glEnd();
    }

    glPopMatrix();

    // =================================================
    // BIRDS
    // =================================================

    glPushMatrix();
    glTranslatef(scene4_position, 0.0f, 0.0f);

    glColor3f(0.05f, 0.08f, 0.10f);

    glLineWidth(1.5f);

    glBegin(GL_LINES);

        // Bird 1
        glVertex2f(7.8f, 8.9f);
        glVertex2f(7.9f, 8.96f);

        glVertex2f(7.9f, 8.96f);
        glVertex2f(8.0f, 8.9f);

        // Bird 2
        glVertex2f(8.2f, 9.1f);
        glVertex2f(8.3f, 9.16f);

        glVertex2f(8.3f, 9.16f);
        glVertex2f(8.4f, 9.1f);

        // Bird 3
        glVertex2f(8.6f, 8.9f);
        glVertex2f(8.7f, 8.96f);

        glVertex2f(8.7f, 8.96f);
        glVertex2f(8.8f, 8.9f);

        // Bird 4
        glVertex2f(11.8f, 9.35f);
        glVertex2f(11.9f, 9.42f);

        glVertex2f(11.9f, 9.42f);
        glVertex2f(12.0f, 9.35f);

        // Bird 5
        glVertex2f(12.25f, 9.15f);
        glVertex2f(12.35f, 9.22f);

        glVertex2f(12.35f, 9.22f);
        glVertex2f(12.45f, 9.15f);

        // Bird 6
        glVertex2f(12.65f, 9.40f);
        glVertex2f(12.75f, 9.47f);

        glVertex2f(12.75f, 9.47f);
        glVertex2f(12.85f, 9.40f);

        // Bird 7
        glVertex2f(3.1f, 8.45f);
        glVertex2f(3.2f, 8.52f);

        glVertex2f(3.2f, 8.52f);
        glVertex2f(3.3f, 8.45f);

        // Bird 8
        glVertex2f(3.55f, 8.65f);
        glVertex2f(3.65f, 8.72f);

        glVertex2f(3.65f, 8.72f);
        glVertex2f(3.75f, 8.65f);

    glEnd();

    glPopMatrix();

    // =================================================
    // CITY BUILDINGS
    // =================================================

    // Sky color behind the narrow building gaps
    glColor3f(
        0.03f + 0.27f * light,
        0.05f + 0.63f * light,
        0.15f + 0.79f * light
    );

    glBegin(GL_QUADS);

        glVertex2f(0.00f,3.18f);
        glVertex2f(14.25f,3.18f);
        glVertex2f(14.25f,7.05f);
        glVertex2f(0.00f,7.05f);

    glEnd();

    glBegin(GL_QUADS);

        // Building 1
        glColor3f(0.72f, 0.72f, 0.66f);

        glVertex2f(0.00f, 3.18f);
        glVertex2f(1.48f, 3.18f);
        glVertex2f(1.48f, 7.05f);
        glVertex2f(0.00f, 7.05f);

        // Building 2
        glColor3f(0.78f, 0.64f, 0.55f);

        glVertex2f(1.55f, 3.18f);
        glVertex2f(3.10f, 3.18f);
        glVertex2f(3.10f, 7.05f);
        glVertex2f(1.55f, 7.05f);

        // Building 3
        glColor3f(0.69f, 0.75f, 0.75f);

        glVertex2f(3.18f, 3.18f);
        glVertex2f(4.65f, 3.18f);
        glVertex2f(4.65f, 7.05f);
        glVertex2f(3.18f, 7.05f);

        // Building 4
        glColor3f(0.83f, 0.72f, 0.57f);

        glVertex2f(4.72f, 3.18f);
        glVertex2f(6.37f, 3.18f);
        glVertex2f(6.37f, 7.05f);
        glVertex2f(4.72f, 7.05f);

        // Building 5
        glColor3f(0.71f, 0.67f, 0.73f);

        glVertex2f(6.45f, 3.18f);
        glVertex2f(7.95f, 3.18f);
        glVertex2f(7.95f, 7.05f);
        glVertex2f(6.45f, 7.05f);

        // Building 6
        glColor3f(0.78f, 0.72f, 0.62f);

        glVertex2f(8.02f, 3.18f);
        glVertex2f(9.54f, 3.18f);
        glVertex2f(9.54f, 7.05f);
        glVertex2f(8.02f, 7.05f);

        // Building 7
        glColor3f(0.66f, 0.73f, 0.68f);

        glVertex2f(9.62f, 3.18f);
        glVertex2f(11.10f, 3.18f);
        glVertex2f(11.10f, 7.05f);
        glVertex2f(9.62f, 7.05f);

        // Building 8
        glColor3f(0.78f, 0.67f, 0.58f);

        glVertex2f(11.18f, 3.18f);
        glVertex2f(13.26f, 3.18f);
        glVertex2f(13.26f, 7.05f);
        glVertex2f(11.18f, 7.05f);

        // Building 9 - Transition building
        glColor3f(0.70f, 0.70f, 0.66f);

        glVertex2f(13.33f, 3.18f);
        glVertex2f(14.18f, 3.18f);
        glVertex2f(14.18f, 7.05f);
        glVertex2f(13.33f, 7.05f);

    glEnd();

    // =================================================
    // BUILDING ROOF LINES
    // =================================================

    glColor3f(0.90f, 0.87f, 0.78f);

    glLineWidth(5);

    glBegin(GL_LINES);

        glVertex2f(0.00f, 7.05f);
        glVertex2f(1.48f, 7.05f);

        glVertex2f(1.55f, 7.05f);
        glVertex2f(3.10f, 7.05f);

        glVertex2f(3.18f, 7.05f);
        glVertex2f(4.65f, 7.05f);

        glVertex2f(4.72f, 7.05f);
        glVertex2f(6.37f, 7.05f);

        glVertex2f(6.45f, 7.05f);
        glVertex2f(7.95f, 7.05f);

        glVertex2f(8.02f, 7.05f);
        glVertex2f(9.54f, 7.05f);

        glVertex2f(9.62f, 7.05f);
        glVertex2f(11.10f, 7.05f);

        glVertex2f(11.18f, 7.05f);
        glVertex2f(13.26f, 7.05f);

        glVertex2f(13.33f, 7.05f);
        glVertex2f(14.18f, 7.05f);

    glEnd();

    // =================================================
    // BUILDING WINDOWS
    // =================================================

    // Building 1
    scene4_drawWindow(0.18f,3.74f);
    scene4_drawWindow(0.58f,3.74f);
    scene4_drawWindow(0.98f,3.74f);

    scene4_drawWindow(0.18f,4.30f);
    scene4_drawWindow(0.58f,4.30f);
    scene4_drawWindow(0.98f,4.30f);

    scene4_drawWindow(0.18f,4.84f);
    scene4_drawWindow(0.58f,4.84f);
    scene4_drawWindow(0.98f,4.84f);

    scene4_drawWindow(0.18f,5.95f);
    scene4_drawWindow(0.58f,5.95f);
    scene4_drawWindow(0.98f,5.95f);

    scene4_drawWindow(0.18f,6.48f);
    scene4_drawWindow(0.58f,6.48f);
    scene4_drawWindow(0.98f,6.48f);

    // Building 2
    scene4_drawWindow(1.72f,3.74f);
    scene4_drawWindow(2.16f,3.74f);
    scene4_drawWindow(2.60f,3.74f);

    scene4_drawWindow(1.72f,4.30f);
    scene4_drawWindow(2.16f,4.30f);
    scene4_drawWindow(2.60f,4.30f);

    scene4_drawWindow(1.72f,4.84f);
    scene4_drawWindow(2.16f,4.84f);
    scene4_drawWindow(2.60f,4.84f);

    scene4_drawWindow(1.72f,5.95f);
    scene4_drawWindow(2.16f,5.95f);
    scene4_drawWindow(2.60f,5.95f);

    scene4_drawWindow(1.72f,6.48f);
    scene4_drawWindow(2.16f,6.48f);
    scene4_drawWindow(2.60f,6.48f);

    // Building 3
    scene4_drawWindow(3.34f,3.74f);
    scene4_drawWindow(3.76f,3.74f);
    scene4_drawWindow(4.18f,3.74f);

    scene4_drawWindow(3.34f,4.30f);
    scene4_drawWindow(3.76f,4.30f);
    scene4_drawWindow(4.18f,4.30f);

    scene4_drawWindow(3.34f,4.84f);
    scene4_drawWindow(3.76f,4.84f);
    scene4_drawWindow(4.18f,4.84f);

    scene4_drawWindow(3.34f,5.95f);
    scene4_drawWindow(3.76f,5.95f);
    scene4_drawWindow(4.18f,5.95f);

    scene4_drawWindow(3.34f,6.48f);
    scene4_drawWindow(3.76f,6.48f);
    scene4_drawWindow(4.18f,6.48f);

    // Building 4
    scene4_drawWindow(4.90f,3.74f);
    scene4_drawWindow(5.38f,3.74f);
    scene4_drawWindow(5.86f,3.74f);

    scene4_drawWindow(4.90f,4.30f);
    scene4_drawWindow(5.38f,4.30f);
    scene4_drawWindow(5.86f,4.30f);

    scene4_drawWindow(4.90f,4.84f);
    scene4_drawWindow(5.38f,4.84f);
    scene4_drawWindow(5.86f,4.84f);

    scene4_drawWindow(4.90f,5.95f);
    scene4_drawWindow(5.38f,5.95f);
    scene4_drawWindow(5.86f,5.95f);

    scene4_drawWindow(4.90f,6.48f);
    scene4_drawWindow(5.38f,6.48f);
    scene4_drawWindow(5.86f,6.48f);

    // Building 5
    scene4_drawWindow(6.62f,3.74f);
    scene4_drawWindow(7.06f,3.74f);
    scene4_drawWindow(7.50f,3.74f);

    scene4_drawWindow(6.62f,4.30f);
    scene4_drawWindow(7.06f,4.30f);
    scene4_drawWindow(7.50f,4.30f);

    scene4_drawWindow(6.62f,4.84f);
    scene4_drawWindow(7.06f,4.84f);
    scene4_drawWindow(7.50f,4.84f);

    scene4_drawWindow(6.62f,5.95f);
    scene4_drawWindow(7.06f,5.95f);
    scene4_drawWindow(7.50f,5.95f);

    scene4_drawWindow(6.62f,6.48f);
    scene4_drawWindow(7.06f,6.48f);
    scene4_drawWindow(7.50f,6.48f);

    // Building 6
    scene4_drawWindow(8.20f,3.74f);
    scene4_drawWindow(8.64f,3.74f);
    scene4_drawWindow(9.08f,3.74f);

    scene4_drawWindow(8.20f,4.30f);
    scene4_drawWindow(8.64f,4.30f);
    scene4_drawWindow(9.08f,4.30f);

    scene4_drawWindow(8.20f,4.84f);
    scene4_drawWindow(8.64f,4.84f);
    scene4_drawWindow(9.08f,4.84f);

    scene4_drawWindow(8.20f,5.95f);
    scene4_drawWindow(8.64f,5.95f);
    scene4_drawWindow(9.08f,5.95f);

    scene4_drawWindow(8.20f,6.48f);
    scene4_drawWindow(8.64f,6.48f);
    scene4_drawWindow(9.08f,6.48f);

    // Building 7
    scene4_drawWindow(9.78f,3.74f);
    scene4_drawWindow(10.20f,3.74f);
    scene4_drawWindow(10.62f,3.74f);

    scene4_drawWindow(9.78f,4.30f);
    scene4_drawWindow(10.20f,4.30f);
    scene4_drawWindow(10.62f,4.30f);

    scene4_drawWindow(9.78f,4.84f);
    scene4_drawWindow(10.20f,4.84f);
    scene4_drawWindow(10.62f,4.84f);

    scene4_drawWindow(9.78f,5.95f);
    scene4_drawWindow(10.20f,5.95f);
    scene4_drawWindow(10.62f,5.95f);

    scene4_drawWindow(9.78f,6.48f);
    scene4_drawWindow(10.20f,6.48f);
    scene4_drawWindow(10.62f,6.48f);

    // Building 8
    scene4_drawWindow(11.38f,3.74f);
    scene4_drawWindow(11.88f,3.74f);
    scene4_drawWindow(12.38f,3.74f);
    scene4_drawWindow(12.82f,3.74f);

    scene4_drawWindow(11.38f,4.30f);
    scene4_drawWindow(11.88f,4.30f);
    scene4_drawWindow(12.38f,4.30f);
    scene4_drawWindow(12.82f,4.30f);

    scene4_drawWindow(11.38f,4.84f);
    scene4_drawWindow(11.88f,4.84f);
    scene4_drawWindow(12.38f,4.84f);
    scene4_drawWindow(12.82f,4.84f);

    scene4_drawWindow(11.38f,5.95f);
    scene4_drawWindow(11.88f,5.95f);
    scene4_drawWindow(12.38f,5.95f);
    scene4_drawWindow(12.82f,5.95f);

    scene4_drawWindow(11.38f,6.48f);
    scene4_drawWindow(11.88f,6.48f);
    scene4_drawWindow(12.38f,6.48f);
    scene4_drawWindow(12.82f,6.48f);

    // Building 9
    scene4_drawWindow(13.40f,3.74f);
    scene4_drawWindow(13.79f,3.74f);

    scene4_drawWindow(13.40f,4.30f);
    scene4_drawWindow(13.79f,4.30f);

    scene4_drawWindow(13.40f,4.84f);
    scene4_drawWindow(13.79f,4.84f);

    scene4_drawWindow(13.40f,5.95f);
    scene4_drawWindow(13.79f,5.95f);

    scene4_drawWindow(13.40f,6.48f);
    scene4_drawWindow(13.79f,6.48f);

    // =================================================
    // ENTRANCE DOORS
    // =================================================

    glColor3f(0.19f,0.27f,0.29f);

    glBegin(GL_QUADS);

        glVertex2f(0.58f,3.18f);
        glVertex2f(0.90f,3.18f);
        glVertex2f(0.90f,3.62f);
        glVertex2f(0.58f,3.62f);

        glVertex2f(2.15f,3.18f);
        glVertex2f(2.48f,3.18f);
        glVertex2f(2.48f,3.62f);
        glVertex2f(2.15f,3.62f);

        glVertex2f(3.75f,3.18f);
        glVertex2f(4.08f,3.18f);
        glVertex2f(4.08f,3.62f);
        glVertex2f(3.75f,3.62f);

        glVertex2f(5.38f,3.18f);
        glVertex2f(5.71f,3.18f);
        glVertex2f(5.71f,3.62f);
        glVertex2f(5.38f,3.62f);

        glVertex2f(7.02f,3.18f);
        glVertex2f(7.35f,3.18f);
        glVertex2f(7.35f,3.62f);
        glVertex2f(7.02f,3.62f);

        glVertex2f(8.62f,3.18f);
        glVertex2f(8.95f,3.18f);
        glVertex2f(8.95f,3.62f);
        glVertex2f(8.62f,3.62f);

        glVertex2f(10.18f,3.18f);
        glVertex2f(10.51f,3.18f);
        glVertex2f(10.51f,3.62f);
        glVertex2f(10.18f,3.62f);

        glVertex2f(12.00f,3.18f);
        glVertex2f(12.38f,3.18f);
        glVertex2f(12.38f,3.62f);
        glVertex2f(12.00f,3.62f);

        glVertex2f(13.58f,3.18f);
        glVertex2f(13.92f,3.18f);
        glVertex2f(13.92f,3.62f);
        glVertex2f(13.58f,3.62f);

    glEnd();

    // =================================================
    // GRASS IN FRONT OF CITY BUILDINGS
    // =================================================

    glColor3f(0.20f,0.55f,0.12f);

    glBegin(GL_QUADS);

        glVertex2f(0.00f,2.76f);
        glVertex2f(14.18f,2.76f);
        glVertex2f(14.18f,3.16f);
        glVertex2f(0.00f,3.16f);

    glEnd();

    // =================================================
    // IDB BHABAN
    // =================================================

    glColor3f(0.78f,0.68f,0.54f);

    glBegin(GL_QUADS);

        glVertex2f(14.25f,2.75f);
        glVertex2f(18.55f,2.75f);
        glVertex2f(18.55f,7.95f);
        glVertex2f(14.25f,7.45f);

    glEnd();

    // Inner front
    glColor3f(0.94f,0.86f,0.72f);

    glBegin(GL_QUADS);

        glVertex2f(14.48f,2.92f);
        glVertex2f(18.32f,2.92f);
        glVertex2f(18.32f,7.68f);
        glVertex2f(14.48f,7.28f);

    glEnd();

    // Side wing
    glColor3f(0.82f,0.73f,0.60f);

    glBegin(GL_POLYGON);

        glVertex2f(18.32f,2.75f);
        glVertex2f(20.00f,2.75f);
        glVertex2f(20.00f,7.03f);
        glVertex2f(18.32f,7.35f);

    glEnd();

    // Side inner
    glColor3f(0.90f,0.82f,0.68f);

    glBegin(GL_QUADS);

        glVertex2f(18.52f,3.00f);
        glVertex2f(19.85f,3.00f);
        glVertex2f(19.85f,6.78f);
        glVertex2f(18.52f,7.02f);

    glEnd();

    // Roof
    glColor3f(0.98f,0.91f,0.78f);

    glBegin(GL_POLYGON);

        glVertex2f(14.20f,7.40f);
        glVertex2f(18.58f,7.90f);
        glVertex2f(18.58f,8.14f);
        glVertex2f(14.20f,7.62f);

    glEnd();

    // Ground base
    glColor3f(0.67f,0.57f,0.44f);

    glBegin(GL_QUADS);

        glVertex2f(14.15f,2.72f);
        glVertex2f(20.00f,2.72f);
        glVertex2f(20.00f,2.96f);
        glVertex2f(14.15f,2.96f);

    glEnd();

    // =================================================
    // IDB BLUE WINDOWS
    // =================================================

    glColor3f(0.06f,0.25f,0.39f);

    for (float x = 14.78f; x <= 17.92f; x += 0.63f)
    {
        glBegin(GL_QUADS);

            glVertex2f(x,3.28f);
            glVertex2f(x+0.31f,3.28f);
            glVertex2f(x+0.31f,7.05f);
            glVertex2f(x,7.05f);

        glEnd();
    }

    for (float x = 18.65f; x <= 19.35f; x += 0.36f)
    {
        glBegin(GL_QUADS);

            glVertex2f(x,3.25f);
            glVertex2f(x+0.20f,3.25f);
            glVertex2f(x+0.20f,6.62f);
            glVertex2f(x,6.66f);

        glEnd();
    }

    // Last side window
    glBegin(GL_QUADS);

        glVertex2f(19.52f,3.25f);
        glVertex2f(19.72f,3.25f);
        glVertex2f(19.72f,6.68f);
        glVertex2f(19.52f,6.72f);

    glEnd();

    // Cream columns
    glColor3f(0.91f,0.82f,0.68f);

    for (float x = 14.62f; x < 18.25f; x += 0.63f)
    {
        glBegin(GL_QUADS);

            glVertex2f(x,3.10f);
            glVertex2f(x+0.13f,3.10f);
            glVertex2f(x+0.13f,7.30f);
            glVertex2f(x,7.30f);

        glEnd();
    }

    // IDB text
    glColor3f(0.05f,0.17f,0.30f);

    scene4_drawText("IDB BHABAN", 15.10f, 7.42f);

    // =================================================
    // TREES
    // =================================================

    // Trees on the left side
    for (float tx = 0.75f; tx < 12.0f; tx += 3.40f)
    {
        // Tree trunk
        glColor3f(0.30f,0.18f,0.07f);

        glBegin(GL_QUADS);

            glVertex2f(tx-0.04f,2.76f);
            glVertex2f(tx+0.04f,2.76f);
            glVertex2f(tx+0.04f,3.48f);
            glVertex2f(tx-0.04f,3.48f);

        glEnd();

        // Tree top
        glColor3f(0.10f,0.40f,0.07f);

        glBegin(GL_POLYGON);

        for (int i = 0; i <= 360; i++)
        {
            float angle = i * 3.1416f / 180.0f;

            glVertex2f(
                tx + 0.34f*cos(angle),
                3.58f + 0.38f*sin(angle)
            );
        }

        glEnd();
    }

    for (float tx = 13.7f; tx < 20.0f; tx += 0.72f)
    {
        // Tree trunk
        glColor3f(0.30f,0.18f,0.07f);

        glBegin(GL_QUADS);

            glVertex2f(tx-0.05f,2.65f);
            glVertex2f(tx+0.05f,2.65f);
            glVertex2f(tx+0.05f,3.55f);
            glVertex2f(tx-0.05f,3.55f);

        glEnd();

        // Tree top
        glColor3f(0.12f,0.42f,0.08f);

        glBegin(GL_POLYGON);

        for (int i = 0; i <= 360; i++)
        {
            float angle = i * 3.1416f / 180.0f;

            glVertex2f(
                tx + 0.42f*cos(angle),
                3.65f + 0.43f*sin(angle)
            );
        }

        glEnd();

        glBegin(GL_POLYGON);

        for (int i = 0; i <= 360; i++)
        {
            float angle = i * 3.1416f / 180.0f;

            glVertex2f(
                tx - 0.25f + 0.30f*cos(angle),
                3.48f + 0.31f*sin(angle)
            );
        }

        glEnd();
    }

    // =================================================
    // METRO VIADUCT PILLARS
    // =================================================

    for (float px = 1.5f; px < 20.0f; px += 3.2f)
    {
        // Pillar
        glColor3f(0.56f,0.57f,0.56f);

        glBegin(GL_QUADS);

            glVertex2f(px-0.28f,2.7f);
            glVertex2f(px+0.28f,2.7f);
            glVertex2f(px+0.28f,5.18f);
            glVertex2f(px-0.28f,5.18f);

        glEnd();

        // Pillar top
        glColor3f(0.68f,0.69f,0.68f);

        glBegin(GL_QUADS);

            glVertex2f(px-0.72f,5.18f);
            glVertex2f(px+0.72f,5.18f);
            glVertex2f(px+0.58f,5.47f);
            glVertex2f(px-0.58f,5.47f);

        glEnd();
    }

    // =================================================
    // METRO DECK
    // =================================================

    glColor3f(0.36f,0.37f,0.37f);

    glBegin(GL_QUADS);

        glVertex2f(0,5.24f);
        glVertex2f(20,5.24f);
        glVertex2f(20,5.50f);
        glVertex2f(0,5.50f);

    glEnd();

    glColor3f(0.67f,0.67f,0.65f);

    glBegin(GL_QUADS);

        glVertex2f(0,5.50f);
        glVertex2f(20,5.50f);
        glVertex2f(20,5.75f);
        glVertex2f(0,5.75f);

    glEnd();

    // Sleepers
    glColor3f(0.34f,0.34f,0.33f);

    for (float sl = 0.08f; sl < 19.95f; sl += 0.30f)
    {
        glBegin(GL_QUADS);

            glVertex2f(sl,5.72f);
            glVertex2f(sl+0.16f,5.72f);
            glVertex2f(sl+0.16f,5.81f);
            glVertex2f(sl,5.81f);

        glEnd();
    }

    // Rails
    glColor3f(0.15f,0.16f,0.16f);

    glLineWidth(3);

    glBegin(GL_LINES);

        glVertex2f(0,5.78f);
        glVertex2f(20,5.78f);

        glVertex2f(0,5.88f);
        glVertex2f(20,5.88f);

    glEnd();

    // =================================================
    // ELECTRIC POLES AND WIRES
    // =================================================

    glColor3f(0.17f,0.22f,0.22f);

    glLineWidth(1.5f);

    for (float ex = 0.85f; ex < 19.80f; ex += 2.25f)
    {
        glBegin(GL_LINES);

            glVertex2f(ex,5.75f);
            glVertex2f(ex,6.78f);

            glVertex2f(ex,6.78f);
            glVertex2f(ex+0.42f,6.78f);

            glVertex2f(ex+0.42f,6.78f);
            glVertex2f(ex+0.42f,6.65f);

        glEnd();
    }

    glBegin(GL_LINES);

        glVertex2f(0,6.66f);
        glVertex2f(20,6.66f);

        glVertex2f(0,6.48f);
        glVertex2f(20,6.48f);

    glEnd();

    // =================================================
    // AGARGAON STATION
    // =================================================

    // Green angular roof
    glColor3f(0.06f,0.30f,0.17f);

    glBegin(GL_POLYGON);

        glVertex2f(1.45f,7.46f);
        glVertex2f(5.55f,8.05f);
        glVertex2f(9.65f,7.46f);
        glVertex2f(9.65f,7.64f);
        glVertex2f(5.55f,8.25f);
        glVertex2f(1.45f,7.64f);

    glEnd();

    // Dark roof underside
    glColor3f(0.13f,0.15f,0.15f);

    glBegin(GL_POLYGON);

        glVertex2f(1.90f,7.32f);
        glVertex2f(5.55f,7.82f);
        glVertex2f(9.20f,7.32f);
        glVertex2f(9.20f,7.47f);
        glVertex2f(5.55f,8.02f);
        glVertex2f(1.90f,7.47f);

    glEnd();

    // Left and right solid walls
    glColor3f(0.72f,0.73f,0.72f);

    glBegin(GL_QUADS);

        glVertex2f(1.90f,5.75f);
        glVertex2f(3.05f,5.75f);
        glVertex2f(3.05f,7.47f);
        glVertex2f(1.90f,7.47f);

        glVertex2f(8.05f,5.75f);
        glVertex2f(9.20f,5.75f);
        glVertex2f(9.20f,7.47f);
        glVertex2f(8.05f,7.47f);

    glEnd();

    // Central blue glass facade
    glColor3f(0.10f,0.36f,0.55f);

    glBegin(GL_QUADS);

        glVertex2f(3.05f,5.75f);
        glVertex2f(8.05f,5.75f);
        glVertex2f(8.05f,7.47f);
        glVertex2f(3.05f,7.47f);

    glEnd();

    // Glass frame and structural columns
    glColor3f(0.22f,0.28f,0.30f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);

        glVertex2f(3.05f,6.30f);
        glVertex2f(8.05f,6.30f);

        glVertex2f(3.05f,6.87f);
        glVertex2f(8.05f,6.87f);

        glVertex2f(4.05f,5.75f);
        glVertex2f(4.05f,7.47f);

        glVertex2f(5.05f,5.75f);
        glVertex2f(5.05f,7.47f);

        glVertex2f(6.05f,5.75f);
        glVertex2f(6.05f,7.47f);

        glVertex2f(7.05f,5.75f);
        glVertex2f(7.05f,7.47f);

    glEnd();

    // Front light-grey columns
    glColor3f(0.78f,0.79f,0.78f);

    glBegin(GL_QUADS);

        glVertex2f(2.90f,5.75f);
        glVertex2f(3.08f,5.75f);
        glVertex2f(3.08f,7.49f);
        glVertex2f(2.90f,7.49f);

        glVertex2f(5.46f,5.75f);
        glVertex2f(5.64f,5.75f);
        glVertex2f(5.64f,7.88f);
        glVertex2f(5.46f,7.88f);

        glVertex2f(8.02f,5.75f);
        glVertex2f(8.20f,5.75f);
        glVertex2f(8.20f,7.49f);
        glVertex2f(8.02f,7.49f);

    glEnd();

    // =================================================
    // AGARGAON NAME BOARD
    // =================================================

    glColor3f(0.94f,0.94f,0.86f);

    glBegin(GL_QUADS);

        glVertex2f(4.25f,6.55f);
        glVertex2f(6.85f,6.55f);
        glVertex2f(6.85f,7.10f);
        glVertex2f(4.25f,7.10f);

    glEnd();

    // Board border
    glColor3f(0.04f,0.23f,0.13f);
    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);

        glVertex2f(4.25f,6.55f);
        glVertex2f(6.85f,6.55f);
        glVertex2f(6.85f,7.10f);
        glVertex2f(4.25f,7.10f);

    glEnd();

    glColor3f(0.05f,0.05f,0.05f);

    scene4_drawText("AGARGAON", 4.82f,6.75f);

    // =================================================
    // FRONT RAILWAY PATH - OPTION 2 STYLE
    // =================================================

    // Dark track bed
    glColor3f(0.25f,0.26f,0.25f);

    glBegin(GL_QUADS);

        glVertex2f(0.00f,5.68f);
        glVertex2f(20.00f,5.68f);
        glVertex2f(20.00f,5.80f);
        glVertex2f(0.00f,5.80f);

    glEnd();

    // Full-width sleepers
    glColor3f(0.48f,0.48f,0.45f);

    for (float sl = 0.08f; sl < 20.0f; sl += 0.30f)
    {
        glBegin(GL_QUADS);

            glVertex2f(sl,5.72f);
            glVertex2f(sl+0.16f,5.72f);
            glVertex2f(sl+0.16f,5.84f);
            glVertex2f(sl,5.84f);

        glEnd();
    }

    // Two continuous rails
    glColor3f(0.10f,0.11f,0.11f);
    glLineWidth(3.0f);

    glBegin(GL_LINES);

        glVertex2f(0.00f,5.82f);
        glVertex2f(20.00f,5.82f);

        glVertex2f(0.00f,5.88f);
        glVertex2f(20.00f,5.88f);

    glEnd();

    // =================================================
    // METRO TRAIN BODY
    // =================================================

    glPushMatrix();
    glTranslatef(-scene4_trainPosition, 0.0f, 0.0f);

    glColor3f(0.91f,0.93f,0.91f);

    glBegin(GL_POLYGON);

        glVertex2f(6.36f,5.92f);
        glVertex2f(14.55f,5.92f);
        glVertex2f(14.62f,6.08f);
        glVertex2f(14.60f,6.43f);
        glVertex2f(14.48f,6.50f);
        glVertex2f(6.74f,6.50f);
        glVertex2f(6.50f,6.43f);
        glVertex2f(6.33f,6.22f);

    glEnd();

    // =================================================
    // TRAIN GREEN STRIPES
    // =================================================

    glColor3f(0.02f,0.35f,0.20f);

    glBegin(GL_QUADS);

        // Lower stripe
        glVertex2f(6.39f,5.99f);
        glVertex2f(14.57f,5.99f);
        glVertex2f(14.59f,6.08f);
        glVertex2f(6.35f,6.08f);

        // Upper stripe
        glVertex2f(6.50f,6.39f);
        glVertex2f(14.59f,6.39f);
        glVertex2f(14.57f,6.47f);
        glVertex2f(6.61f,6.47f);

    glEnd();

    // =================================================
    // TRAIN UNDERBODY
    // =================================================

    glColor3f(0.16f,0.19f,0.19f);

    glBegin(GL_QUADS);

        glVertex2f(6.62f,5.88f);
        glVertex2f(14.35f,5.88f);
        glVertex2f(14.35f,5.97f);
        glVertex2f(6.62f,5.97f);

    glEnd();

    // =================================================
    // DRIVER CAB
    // =================================================

    glColor3f(0.02f,0.27f,0.17f);

    glBegin(GL_POLYGON);

        glVertex2f(6.36f,5.94f);
        glVertex2f(6.78f,5.94f);
        glVertex2f(6.78f,6.48f);
        glVertex2f(6.60f,6.46f);
        glVertex2f(6.43f,6.34f);
        glVertex2f(6.32f,6.19f);

    glEnd();

    // Driver window
    glColor3f(0.05f,0.17f,0.22f);

    glBegin(GL_POLYGON);

        glVertex2f(6.40f,6.18f);
        glVertex2f(6.70f,6.18f);
        glVertex2f(6.70f,6.39f);
        glVertex2f(6.57f,6.39f);
        glVertex2f(6.43f,6.30f);

    glEnd();

    // =================================================
    // FOUR COACHES
    // =================================================

    for (int coach = 0; coach < 4; coach++)
    {
        float cx = 6.82f + coach * 1.90f;

        // Windows
        glColor3f(0.05f,0.18f,0.23f);

        glBegin(GL_QUADS);

            // Window 1
            glVertex2f(cx+0.08f,6.14f);
            glVertex2f(cx+0.42f,6.14f);
            glVertex2f(cx+0.42f,6.36f);
            glVertex2f(cx+0.08f,6.36f);

            // Window 2
            glVertex2f(cx+1.45f,6.14f);
            glVertex2f(cx+1.79f,6.14f);
            glVertex2f(cx+1.79f,6.36f);
            glVertex2f(cx+1.45f,6.36f);

        glEnd();

        // Door
        glColor3f(0.04f,0.23f,0.25f);

        glBegin(GL_QUADS);

            glVertex2f(cx+0.56f,6.03f);
            glVertex2f(cx+1.31f,6.03f);
            glVertex2f(cx+1.31f,6.38f);
            glVertex2f(cx+0.56f,6.38f);

        glEnd();

        // Door middle line
        glColor3f(0.72f,0.78f,0.76f);

        glLineWidth(1.2f);

        glBegin(GL_LINES);

            glVertex2f(cx+0.935f,6.03f);
            glVertex2f(cx+0.935f,6.38f);

        glEnd();

        // Coach joint
        if (coach < 3)
        {
            glColor3f(0.10f,0.12f,0.12f);

            glBegin(GL_QUADS);

                glVertex2f(cx+1.84f,5.96f);
                glVertex2f(cx+1.91f,5.96f);
                glVertex2f(cx+1.91f,6.46f);
                glVertex2f(cx+1.84f,6.46f);

            glEnd();
        }
    }

    // =================================================
    // TRAIN LIGHTS
    // =================================================

    if(light < 0.5f)
        glColor3f(1.0f,0.90f,0.25f);
    else
        glColor3f(0.25f,0.25f,0.18f);

    glBegin(GL_QUADS);

        glVertex2f(6.34f,6.08f);
        glVertex2f(6.43f,6.08f);
        glVertex2f(6.43f,6.14f);
        glVertex2f(6.35f,6.14f);

        glVertex2f(14.54f,6.08f);
        glVertex2f(14.61f,6.08f);
        glVertex2f(14.60f,6.14f);
        glVertex2f(14.54f,6.14f);

    glEnd();

    // =================================================
    // METRO WHEELS
    // =================================================

    glColor3f(0.07f,0.08f,0.08f);

    for (float tw = 7.18f; tw < 14.10f; tw += 0.95f)
    {
        glBegin(GL_POLYGON);

        for (int i = 0; i <= 360; i++)
        {
            float angle = i * 3.1416f / 180.0f;

            glVertex2f(
                tw + 0.105f*cos(angle),
                5.89f + 0.105f*sin(angle)
            );
        }

        glEnd();
    }

    glPopMatrix();

    // =================================================
    // FOOTPATH
    // =================================================

    glColor3f(0.73f,0.72f,0.68f);

    glBegin(GL_QUADS);

        glVertex2f(0,2.1f);
        glVertex2f(20,2.1f);
        glVertex2f(20,2.75f);
        glVertex2f(0,2.75f);

    glEnd();

    // =================================================
    // FENCE
    // =================================================

    glColor3f(0.05f,0.12f,0.07f);

    glLineWidth(2);

    glBegin(GL_LINES);

        glVertex2f(0,2.78f);
        glVertex2f(20,2.78f);

        glVertex2f(0,3.05f);
        glVertex2f(20,3.05f);

    glEnd();

    for (float fx = 0; fx < 20; fx += 0.22f)
    {
        glBegin(GL_LINES);

            glVertex2f(fx,2.70f);
            glVertex2f(fx,3.18f);

        glEnd();
    }

    // =================================================
    // PEOPLE
    // =================================================

    glPushMatrix();
    glTranslatef(scene4_position, 0.0f, 0.0f);

    for (int p = 0; p < 16; p++)
    {
        float x = 2.8f + p * 0.88f;
        float walk = 0.11f * sin(scene4_position * 6.0f + p * 0.7f);

        // Head
        glColor3f(0.55f,0.31f,0.18f);

        glBegin(GL_POLYGON);

        for (int i = 0; i <= 360; i++)
        {
            float angle = i * 3.1416f / 180.0f;

            glVertex2f(
                x + 0.07f*cos(angle),
                2.64f + 0.09f*sin(angle)
            );
        }

        glEnd();

        // Body
        glColor3f(
            (p % 3) * 0.25f,
            0.25f + (p % 2) * 0.35f,
            0.30f + (p % 4) * 0.12f
        );

        glBegin(GL_QUADS);

            glVertex2f(x-0.08f,2.25f);
            glVertex2f(x+0.08f,2.25f);
            glVertex2f(x+0.10f,2.57f);
            glVertex2f(x-0.10f,2.57f);

        glEnd();

        // Moving arms
        glColor3f(0.55f,0.31f,0.18f);
        glLineWidth(2.0f);

        glBegin(GL_LINES);

            // Left upper arm
            glVertex2f(x-0.09f,2.50f);
            glVertex2f(x-0.08f-walk*0.45f,2.40f);

            // Left lower arm
            glVertex2f(x-0.08f-walk*0.45f,2.40f);
            glVertex2f(x-0.10f-walk*0.75f,2.30f);

            // Right upper arm
            glVertex2f(x+0.09f,2.50f);
            glVertex2f(x+0.08f+walk*0.45f,2.40f);

            // Right lower arm
            glVertex2f(x+0.08f+walk*0.45f,2.40f);
            glVertex2f(x+0.10f+walk*0.75f,2.30f);

        glEnd();

        // Legs
        glColor3f(0.08f,0.08f,0.08f);

        glBegin(GL_LINES);

            // Left thigh
            glVertex2f(x-0.04f,2.25f);
            glVertex2f(x-0.03f+walk*0.45f,2.17f);

            // Left lower leg
            glVertex2f(x-0.03f+walk*0.45f,2.17f);
            glVertex2f(x-0.02f+walk,2.10f);

            // Right thigh
            glVertex2f(x+0.04f,2.25f);
            glVertex2f(x+0.03f-walk*0.45f,2.17f);

            // Right lower leg
            glVertex2f(x+0.03f-walk*0.45f,2.17f);
            glVertex2f(x+0.02f-walk,2.10f);

        glEnd();
    }

    glPopMatrix();

    // =================================================
    // ROAD
    // =================================================

    glColor3f(0.25f,0.27f,0.28f);

    glBegin(GL_QUADS);

        glVertex2f(0,0.35f);
        glVertex2f(20,0.35f);
        glVertex2f(20,2.10f);
        glVertex2f(0,2.10f);

    glEnd();

    // =================================================
    // ROAD LANE MARKINGS
    // =================================================

    glColor3f(0.92f,0.91f,0.86f);

    for (float lx = 0.3f; lx < 20; lx += 2.0f)
    {
        glBegin(GL_QUADS);

            glVertex2f(lx,1.23f);
            glVertex2f(lx+1.0f,1.23f);
            glVertex2f(lx+1.0f,1.27f);
            glVertex2f(lx,1.27f);

        glEnd();
    }

    // =================================================
    // BLACK WHITE CURB
    // =================================================

    for (int k = 0; k < 40; k++)
    {
        if (k % 2 == 0)
            glColor3f(0.05f,0.05f,0.05f);
        else
            glColor3f(0.95f,0.95f,0.93f);

        glBegin(GL_QUADS);

            glVertex2f(k*0.5f,2.02f);
            glVertex2f(k*0.5f+0.5f,2.02f);
            glVertex2f(k*0.5f+0.5f,2.15f);
            glVertex2f(k*0.5f,2.15f);

        glEnd();
    }

    // =================================================
    // BLUE BUS
    // =================================================

    glPushMatrix();
    glTranslatef(-scene4_position, 0.0f, 0.0f);
    glTranslatef(0.16f, 0.10f, 0.0f);
    glScalef(0.60f, 0.60f, 1.0f);

    glColor3f(0.02f,0.25f,0.55f);

    glBegin(GL_POLYGON);

        glVertex2f(0.4f,0.55f);
        glVertex2f(5.25f,0.55f);
        glVertex2f(5.35f,0.75f);
        glVertex2f(5.25f,1.82f);
        glVertex2f(4.95f,1.95f);
        glVertex2f(0.55f,1.95f);
        glVertex2f(0.4f,1.70f);

    glEnd();

    // Bus windows
    glColor3f(0.05f,0.17f,0.23f);

    for (float bx = 0.65f; bx < 4.95f; bx += 0.58f)
    {
        glBegin(GL_QUADS);

            glVertex2f(bx,1.28f);
            glVertex2f(bx+0.42f,1.28f);
            glVertex2f(bx+0.42f,1.75f);
            glVertex2f(bx,1.75f);

        glEnd();
    }

    // Bus stripe
    glColor3f(1,1,1);

    glBegin(GL_POLYGON);

        glVertex2f(0.5f,0.82f);
        glVertex2f(2.3f,0.82f);
        glVertex2f(2.65f,0.62f);
        glVertex2f(4.95f,0.62f);
        glVertex2f(4.95f,0.78f);
        glVertex2f(2.7f,0.78f);
        glVertex2f(2.35f,1.0f);
        glVertex2f(0.5f,1.0f);

    glEnd();

    // Blue bus headlight
    if(light < 0.5f)
        glColor3f(1.0f,0.90f,0.20f);
    else
        glColor3f(0.25f,0.25f,0.18f);

    glBegin(GL_QUADS);

        glVertex2f(0.40f,1.02f);
        glVertex2f(0.58f,1.02f);
        glVertex2f(0.58f,1.18f);
        glVertex2f(0.40f,1.18f);

    glEnd();

    scene4_drawVehicleWheel(1.25f,0.55f,0.28f);
    scene4_drawVehicleWheel(4.35f,0.55f,0.28f);

    glPopMatrix();

    // =================================================
    // WHITE SEDAN
    // =================================================

    glPushMatrix();
    glTranslatef(scene4_position, 0.0f, 0.0f);

    // Opposite side of the road (upper lane)
    glPushMatrix();
    glTranslatef(2.22f, 0.887f, 0.0f);
    glScalef(0.65f, 0.65f, 1.0f);

    glColor3f(0.94f,0.94f,0.92f);

    glBegin(GL_POLYGON);

        glVertex2f(6.35f,0.82f);
        glVertex2f(6.42f,1.18f);
        glVertex2f(6.78f,1.30f);
        glVertex2f(7.18f,1.68f);
        glVertex2f(8.18f,1.68f);
        glVertex2f(8.63f,1.34f);
        glVertex2f(9.02f,1.25f);
        glVertex2f(9.10f,0.98f);
        glVertex2f(8.92f,0.82f);

    glEnd();

    // Car windows
    glColor3f(0.12f,0.25f,0.31f);

    glBegin(GL_POLYGON);

        glVertex2f(7.05f,1.34f);
        glVertex2f(7.34f,1.60f);
        glVertex2f(7.68f,1.60f);
        glVertex2f(7.68f,1.34f);

    glEnd();

    glBegin(GL_POLYGON);

        glVertex2f(7.76f,1.34f);
        glVertex2f(7.76f,1.60f);
        glVertex2f(8.12f,1.60f);
        glVertex2f(8.48f,1.34f);

    glEnd();

    glColor3f(0.17f,0.18f,0.18f);

    glBegin(GL_LINES);

        glVertex2f(7.72f,1.32f);
        glVertex2f(7.72f,1.62f);

        glVertex2f(8.53f,1.32f);
        glVertex2f(8.58f,0.94f);

    glEnd();

    // Light
    if(light < 0.5f)
        glColor3f(1.0f,0.90f,0.20f);
    else
        glColor3f(0.25f,0.25f,0.18f);

    glBegin(GL_QUADS);

        glVertex2f(8.82f,1.10f);
        glVertex2f(9.05f,1.08f);
        glVertex2f(9.04f,1.20f);
        glVertex2f(8.82f,1.23f);

    glEnd();

    // Bumper
    glColor3f(0.25f,0.25f,0.25f);

    glBegin(GL_QUADS);

        glVertex2f(6.35f,0.82f);
        glVertex2f(9.08f,0.82f);
        glVertex2f(9.08f,0.90f);
        glVertex2f(6.35f,0.90f);

    glEnd();

    scene4_drawVehicleWheel(6.88f,0.82f,0.22f);
    scene4_drawVehicleWheel(8.55f,0.82f,0.22f);

    glPopMatrix();

    glPopMatrix();

    // =================================================
    // GREEN CNG
    // =================================================

    glPushMatrix();
    glTranslatef(-scene4_position, 0.0f, 0.0f);
    glTranslatef(3.86f, 0.058f, 0.0f);
    glScalef(0.60f, 0.60f, 1.0f);

    glColor3f(0.04f,0.40f,0.18f);

    glBegin(GL_POLYGON);

        glVertex2f(9.48f,0.62f);
        glVertex2f(11.75f,0.62f);
        glVertex2f(11.70f,1.38f);
        glVertex2f(11.30f,1.72f);
        glVertex2f(10.25f,1.72f);
        glVertex2f(9.82f,1.40f);
        glVertex2f(9.58f,1.05f);

    glEnd();

    // CNG windows
    glColor3f(0.05f,0.15f,0.15f);

    glBegin(GL_POLYGON);

        glVertex2f(9.92f,1.24f);
        glVertex2f(10.28f,1.62f);
        glVertex2f(10.68f,1.62f);
        glVertex2f(10.68f,1.24f);

    glEnd();

    glBegin(GL_QUADS);

        glVertex2f(10.80f,1.24f);
        glVertex2f(11.42f,1.24f);
        glVertex2f(11.25f,1.62f);
        glVertex2f(10.80f,1.62f);

    glEnd();

    // CNG front bumper
    glColor3f(0.08f,0.10f,0.09f);

    glBegin(GL_QUADS);

        glVertex2f(9.43f,0.64f);
        glVertex2f(9.72f,0.64f);
        glVertex2f(9.72f,0.73f);
        glVertex2f(9.43f,0.73f);

    glEnd();

    // CNG headlight
    if(light < 0.5f)
        glColor3f(1.0f,0.90f,0.20f);
    else
        glColor3f(0.25f,0.25f,0.18f);

    glBegin(GL_QUADS);

        glVertex2f(9.55f,0.92f);
        glVertex2f(9.72f,0.92f);
        glVertex2f(9.72f,1.08f);
        glVertex2f(9.55f,1.08f);

    glEnd();

    scene4_drawVehicleWheel(10.08f,0.62f,0.19f);
    scene4_drawVehicleWheel(11.42f,0.62f,0.19f);

    glPopMatrix();

    // =================================================
    // GREY SUV
    // =================================================

    glPushMatrix();
    glTranslatef(scene4_position, 0.0f, 0.0f);

    // Opposite side of the road (upper lane)
    glPushMatrix();
    glTranslatef(4.29f, 0.887f, 0.0f);
    glScalef(0.65f, 0.65f, 1.0f);

    glColor3f(0.54f,0.56f,0.55f);

    glBegin(GL_POLYGON);

        glVertex2f(12.25f,0.82f);
        glVertex2f(12.32f,1.20f);
        glVertex2f(12.72f,1.34f);
        glVertex2f(13.18f,1.75f);
        glVertex2f(14.25f,1.75f);
        glVertex2f(14.78f,1.42f);
        glVertex2f(15.05f,1.35f);
        glVertex2f(15.16f,1.03f);
        glVertex2f(14.98f,0.82f);

    glEnd();

    // SUV windows
    glColor3f(0.12f,0.23f,0.28f);

    glBegin(GL_POLYGON);

        glVertex2f(13.02f,1.39f);
        glVertex2f(13.30f,1.68f);
        glVertex2f(13.70f,1.68f);
        glVertex2f(13.70f,1.39f);

    glEnd();

    glBegin(GL_POLYGON);

        glVertex2f(13.79f,1.39f);
        glVertex2f(13.79f,1.68f);
        glVertex2f(14.20f,1.68f);
        glVertex2f(14.62f,1.39f);

    glEnd();

    glColor3f(0.20f,0.21f,0.21f);

    glBegin(GL_LINES);

        glVertex2f(13.74f,1.37f);
        glVertex2f(13.74f,1.70f);

        glVertex2f(14.69f,1.38f);
        glVertex2f(14.73f,0.95f);

    glEnd();

    // SUV light
    if(light < 0.5f)
        glColor3f(1.0f,0.90f,0.20f);
    else
        glColor3f(0.25f,0.25f,0.18f);

    glBegin(GL_QUADS);

        glVertex2f(14.90f,1.13f);
        glVertex2f(15.10f,1.10f);
        glVertex2f(15.08f,1.24f);
        glVertex2f(14.89f,1.27f);

    glEnd();

    // SUV bumper
    glColor3f(0.19f,0.19f,0.19f);

    glBegin(GL_QUADS);

        glVertex2f(12.25f,0.82f);
        glVertex2f(15.14f,0.82f);
        glVertex2f(15.14f,0.91f);
        glVertex2f(12.25f,0.91f);

    glEnd();

    scene4_drawVehicleWheel(12.85f,0.82f,0.23f);
    scene4_drawVehicleWheel(14.65f,0.82f,0.23f);

    glPopMatrix();

    glPopMatrix();

    // =================================================
    // RED BUS
    // =================================================

    glPushMatrix();
    glTranslatef(-scene4_position, 0.0f, 0.0f);
    glTranslatef(6.18f, 0.10f, 0.0f);
    glScalef(0.60f, 0.60f, 1.0f);

    glColor3f(0.80f,0.12f,0.06f);

    glBegin(GL_POLYGON);

        glVertex2f(15.45f,0.55f);
        glVertex2f(19.75f,0.55f);
        glVertex2f(19.85f,0.75f);
        glVertex2f(19.75f,1.95f);
        glVertex2f(15.75f,1.95f);
        glVertex2f(15.45f,1.60f);

    glEnd();

    // Red bus windows
    glColor3f(0.07f,0.17f,0.20f);

    for (float rx = 15.75f; rx < 19.55f; rx += 0.52f)
    {
        glBegin(GL_QUADS);

            glVertex2f(rx,1.30f);
            glVertex2f(rx+0.37f,1.30f);
            glVertex2f(rx+0.37f,1.78f);
            glVertex2f(rx,1.78f);

        glEnd();
    }

    // Yellow stripe
    glColor3f(1.0f,0.70f,0.05f);

    glBegin(GL_POLYGON);

        glVertex2f(15.55f,0.85f);
        glVertex2f(17.5f,1.05f);
        glVertex2f(19.7f,0.78f);
        glVertex2f(19.7f,0.92f);
        glVertex2f(17.5f,1.20f);
        glVertex2f(15.55f,1.0f);

    glEnd();

    // Red bus headlight
    if(light < 0.5f)
        glColor3f(1.0f,0.90f,0.20f);
    else
        glColor3f(0.25f,0.25f,0.18f);

    glBegin(GL_QUADS);

        glVertex2f(15.45f,1.02f);
        glVertex2f(15.63f,1.02f);
        glVertex2f(15.63f,1.18f);
        glVertex2f(15.45f,1.18f);

    glEnd();

    scene4_drawVehicleWheel(16.05f,0.55f,0.27f);
    scene4_drawVehicleWheel(19.15f,0.55f,0.27f);

    glPopMatrix();

    // =================================================
    // BOTTOM GREEN DIVIDER
    // =================================================

    glColor3f(0.10f,0.42f,0.08f);

    glBegin(GL_QUADS);

        glVertex2f(0,0);
        glVertex2f(20,0);
        glVertex2f(20,0.34f);
        glVertex2f(0,0.34f);

    glEnd();

    // =================================================
    // TITLE BOX
    // =================================================

    glColor3f(0.93f,0.86f,0.70f);

    glBegin(GL_QUADS);

        glVertex2f(6.7f,0.02f);
        glVertex2f(13.2f,0.02f);
        glVertex2f(13.2f,0.31f);
        glVertex2f(6.7f,0.31f);

    glEnd();

    glColor3f(0.08f,0.08f,0.08f);

    scene4_drawText(
        "AGARGAON IDB AREA DHAKA",
        7.10f,
        0.08f
    );

    // =================================================
    // FINISH
    // =================================================

    glFlush();
}

// =====================================================
// Main
// =====================================================

//jawad

// ANIMATION OFFSETS
float scene5_cloudOffset = 0.0;
float scene5_birdOffset = 0.0;
float scene5_trainOffset = 0.0;
float scene5_carOffset = 0.0;
float scene5_horizCarOffset = 0.0;

// লেখাকে বক্সের ভেতর ফিট রাখা এবং সুন্দর দেখানোর জন্য ফাংশন
void scene5_drawStrokeText(const char* text, float x, float y, float scale, float lineWidth)
{
    glLineWidth(lineWidth); // লেখার পুরুত্ব (Thickness) কন্ট্রোল

    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glScalef(scale, -scale, 1.0); // উইন্ডোর সাইজের সাথে লেখা ছোট-বড় হবে
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }
    glPopMatrix();

    glLineWidth(1.0); // অন্য শেপগুলোর লাইন যেন মোটা না হয়ে যায় তাই রিসেট
}

void scene5_timer(int val)
{
    // Cloud drift
    scene5_cloudOffset -= 0.15;
    if (scene5_cloudOffset < -1600.0) scene5_cloudOffset = 0.0;

    // Bird flight
    scene5_birdOffset += 0.45;
    if (scene5_birdOffset > 1650.0) scene5_birdOffset = -500.0;

    // Metro Train movement along track
    scene5_trainOffset -= 3.5;
    if (scene5_trainOffset < -1700.0) scene5_trainOffset = 1150.0;

    // Car offset (Used for BOTH diagonal and horizontal cars to sync)
    scene5_carOffset += 0.7;
    if (scene5_carOffset > 1500.0) scene5_carOffset = -800.0;

    if(activeScene == 5)
        updateMetroSound((1600.0f + scene5_trainOffset > 0.0f) &&
                         (425.0f + scene5_trainOffset < 1550.0f));

    glutPostRedisplay();
    glutTimerFunc(16, scene5_timer, 0); // ~60 FPS
}

void scene5_init()
{
    glClearColor(0.38, 0.65, 0.94, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1550.0, 1000.0, 0.0);
}

void scene5_display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // SKY
    glBegin(GL_QUADS);
        glColor3f(0.38, 0.65, 0.94);
        glVertex2f(0, 0);
        glVertex2f(1600, 0);
        glColor3f(0.74, 0.86, 0.98);
        glVertex2f(1600, 480);
        glVertex2f(0, 480);
    glEnd();

    // CLOUDS (SMOOTH STYLE - WHITE)
    glPushMatrix();
    glTranslatef(scene5_cloudOffset, 0.0, 0.0);
    float cloudX[6] = {120, 780, 1420, 1720, 2380, 3020};
    float cloudY[6] = {90, 110, 120, 90, 110, 120};
    float cloudScale[6] = {1.1, 1.0, 0.8, 1.1, 1.0, 0.8};
    glColor3f(1.0, 1.0, 1.0); // White Clouds
    for (int c = 0; c < 6; c++)
    {
        float cx = cloudX[c], cy = cloudY[c], s = cloudScale[c];

        float circles[3][3] = {
            {cx, cy, 20 * s},
            {cx + 30 * s, cy - 10 * s, 28 * s},
            {cx + 60 * s, cy, 20 * s}
        };

        for (int k = 0; k < 3; k++)
        {
            glBegin(GL_POLYGON);
            for (int i = 0; i <= 360; i += 5)
            {
                float angle = i * PI / 180;
                glVertex2f(circles[k][0] + circles[k][2] * cos(angle),
                           circles[k][1] + circles[k][2] * sin(angle));
            }
            glEnd();
        }
    }
    glPopMatrix();

    // BIRDS
    glPushMatrix();
    glTranslatef(scene5_birdOffset, sin(scene5_birdOffset * 0.03) * 12.0, 0.0);
    glColor3f(0.15, 0.18, 0.20);
    glLineWidth(1.8);
    float birdX[4] = {330, 365, 400, 435};
    float birdY[4] = {155, 135, 110, 130};
    for (int i = 0; i < 4; i++)
    {
        glBegin(GL_LINE_STRIP);
            glVertex2f(birdX[i], birdY[i]);
            glVertex2f(birdX[i] + 7, birdY[i] - 6);
            glVertex2f(birdX[i] + 14, birdY[i]);
            glVertex2f(birdX[i] + 21, birdY[i] - 6);
            glVertex2f(birdX[i] + 28, birdY[i]);
        glEnd();
    }
    glPopMatrix();
    glLineWidth(1.0);

    // CURZON HALL AREA
    // Trees
    float treeX[4] = {70, 150, 220, 40};
    float treeY[4] = {270, 250, 265, 380};
    float treeRadius[4] = {75, 65, 55, 50};
    for (int t = 0; t < 4; t++)
    {
        glColor3f(0.20, 0.48, 0.22);
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 360; i += 10)
        {
            float angle = i * PI / 180;
            glVertex2f(treeX[t] + treeRadius[t] * cos(angle), treeY[t] + treeRadius[t] * sin(angle));
        }
        glEnd();
    }

    // Palm tree
    glColor3f(0.42, 0.24, 0.12);
    glLineWidth(5);
    glBegin(GL_LINES);
        glVertex2f(280, 440);
        glVertex2f(265, 270);
    glEnd();

    glColor3f(0.12, 0.48, 0.15);
    glLineWidth(3);
    glBegin(GL_LINES);
        glVertex2f(265, 270); glVertex2f(205, 240);
        glVertex2f(265, 270); glVertex2f(225, 210);
        glVertex2f(265, 270); glVertex2f(270, 195);
        glVertex2f(265, 270); glVertex2f(315, 215);
        glVertex2f(265, 270); glVertex2f(330, 250);
    glEnd();
    glLineWidth(1.0);

    // Hill
    glColor3f(0.38, 0.62, 0.25);
    glBegin(GL_QUADS);
        glVertex2f(0, 360);
        glVertex2f(600, 360);
        glVertex2f(600, 800);
        glVertex2f(0, 800);
    glEnd();

    // Curzon main building
    glBegin(GL_QUADS);
        glColor3f(0.68, 0.25, 0.18);
        glVertex2f(60, 430);
        glVertex2f(420, 430);
        glVertex2f(420, 610);
        glVertex2f(60, 610);

        glColor3f(0.74, 0.29, 0.20);
        glVertex2f(140, 400);
        glVertex2f(340, 400);
        glVertex2f(340, 610);
        glVertex2f(140, 610);
    glEnd();

    // Brick lines
    glColor3f(0.60, 0.22, 0.15);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    for (int row = 0; row < 10; row++)
    {
        float y = 435 + row * 17;
        if (y > 605) break;
        glVertex2f(62, y);
        glVertex2f(418, y);
    }
    glEnd();

    // Pediment
    glColor3f(0.55, 0.18, 0.12);
    glBegin(GL_TRIANGLES);
        glVertex2f(130, 400);
        glVertex2f(240, 345);
        glVertex2f(350, 400);
    glEnd();

    // Domes & pillars
    float domeX[2] = {100, 380};
    for (int d = 0; d < 2; d++)
    {
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 360; i += 5)
        {
            float angle = i * PI / 180;
            glVertex2f(domeX[d] + 24 * cos(angle), 400 + 24 * sin(angle));
        }
        glEnd();
    }
    glBegin(GL_QUADS);
        glVertex2f(90, 410);  glVertex2f(110, 410);
        glVertex2f(110, 440); glVertex2f(90, 440);
        glVertex2f(370, 410); glVertex2f(390, 410);
        glVertex2f(390, 440); glVertex2f(370, 440);
    glEnd();

    // Arched windows
    glColor3f(0.20, 0.10, 0.08);
    for (int i = 0; i < 5; i++)
    {
        float x1 = 80 + i * 65;
        float x2 = 105 + i * 65;
        float yBottom = 525;

        glBegin(GL_QUADS);
            glVertex2f(x1, 480);
            glVertex2f(x2, 480);
            glVertex2f(x2, yBottom);
            glVertex2f(x1, yBottom);
        glEnd();

        glBegin(GL_POLYGON);
        for (int j = 0; j <= 360; j += 10)
        {
            float angle = j * PI / 180;
            glVertex2f(92.5 + i * 65 + 12.5 * cos(angle), 480 + 12.5 * sin(angle));
        }
        glEnd();
    }

    // Upper floor windows
    for (int i = 0; i < 4; i++)
    {
        float x1 = 160 + i * 45, x2 = 185 + i * 45;
        glBegin(GL_QUADS);
            glVertex2f(x1, 425);
            glVertex2f(x2, 425);
            glVertex2f(x2, 460);
            glVertex2f(x1, 460);
        glEnd();
    }

    // Entrance door
    glBegin(GL_QUADS);
        glVertex2f(205, 530);
        glVertex2f(275, 530);
        glVertex2f(275, 610);
        glVertex2f(205, 610);
    glEnd();
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i += 5)
    {
        float angle = i * PI / 180;
        glVertex2f(240 + 35 * cos(angle), 530 + 35 * sin(angle));
    }
    glEnd();

    // Banner
    glColor3f(0.92, 0.88, 0.78);
    glBegin(GL_QUADS);
        glVertex2f(175, 500);
        glVertex2f(305, 500);
        glVertex2f(305, 520);
        glVertex2f(175, 520);
    glEnd();

    // Fixed Text: KARJON HALL (Centered with clear 1.5 thickness)
    glColor3f(0.1, 0.1, 0.1);
    scene5_drawStrokeText("KARJON HALL", 195, 515, 0.08, 1.5);

    // Pathway
    glColor3f(0.80, 0.76, 0.65);
    glBegin(GL_POLYGON);
        glVertex2f(210, 610);
        glVertex2f(270, 610);
        glVertex2f(290, 670);
        glVertex2f(160, 670);
    glEnd();

    // Fence
    glColor3f(0.12, 0.15, 0.15);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2f(0, 640);
        glVertex2f(470, 640);
        glVertex2f(0, 670);
        glVertex2f(470, 670);
        for (int x = 10; x < 470; x += 12)
        {
            glVertex2f(x, 625);
            glVertex2f(x, 670);
        }
    glEnd();
    glLineWidth(1.0);

    // DHAKA UNIVERSITY SIGNBOARD
    glColor3f(0.82, 0.84, 0.82);
    glBegin(GL_QUADS);
        glVertex2f(35, 680);
        glVertex2f(375, 680);
        glVertex2f(375, 815);
        glVertex2f(35, 815);
    glEnd();

    glColor3f(0.30, 0.32, 0.32);
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
        glVertex2f(35, 680);
        glVertex2f(375, 680);
        glVertex2f(375, 815);
        glVertex2f(35, 815);
    glEnd();

    glColor3f(0.10, 0.20, 0.48);
    glBegin(GL_QUADS);
        glVertex2f(60, 705);
        glVertex2f(125, 705);
        glVertex2f(125, 790);
        glVertex2f(60, 790);
    glEnd();

    glColor3f(0.85, 0.65, 0.10);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
        glVertex2f(65, 710);
        glVertex2f(120, 710);
        glVertex2f(120, 785);
        glVertex2f(65, 785);
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i += 10)
    {
        float angle = i * PI / 180;
        glVertex2f(92.5 + 14 * cos(angle), 745 + 14 * sin(angle));
    }
    glEnd();
    glLineWidth(1.0);

    // Fixed Text: DHAKA UNIVERSITY Signboard
    glColor3f(0.08, 0.08, 0.08);
    scene5_drawStrokeText("DHAKA UNIVERSITY", 165, 755, 0.10, 2.0);

    // Grass strip
    glColor3f(0.25, 0.50, 0.20);
    glBegin(GL_QUADS);
        glVertex2f(20, 810);
        glVertex2f(395, 810);
        glVertex2f(395, 835);
        glVertex2f(20, 835);
    glEnd();

    glColor3f(0.20, 0.42, 0.16);
    glLineWidth(1.5);
    glBegin(GL_LINES);
    for (int x = 22; x < 393; x += 5)
    {
        glVertex2f(x, 833);
        glVertex2f(x + 2, 820);
    }
    glEnd();
    glLineWidth(1.0);

    // METRO VIADUCT + TRACK
    glBegin(GL_QUADS);
        glColor3f(0.70, 0.72, 0.73);
        glVertex2f(0, 305);
        glVertex2f(1600, 275);
        glVertex2f(1600, 300);
        glVertex2f(0, 370);

        glColor3f(0.55, 0.57, 0.58);
        glVertex2f(0, 370);
        glVertex2f(1600, 300);
        glVertex2f(1600, 320);
        glVertex2f(0, 400);
    glEnd();

    // Pillars
    float pillarX[7] = {320, 680, 990, 1220, 1380, 1490, 1570};
    float pillarTopY[7] = {385, 335, 308, 290, 278, 270, 265};
    float pillarWidth[7] = {46, 36, 26, 20, 15, 11, 8};

    for (int i = 0; i < 7; i++)
    {
        glBegin(GL_QUADS);
            glColor3f(0.60, 0.62, 0.63);
            glVertex2f(pillarX[i] - pillarWidth[i] * 1.5, pillarTopY[i]);
            glVertex2f(pillarX[i] + pillarWidth[i] * 1.5, pillarTopY[i]);
            glVertex2f(pillarX[i] + pillarWidth[i], pillarTopY[i] + 35 - i * 3);
            glVertex2f(pillarX[i] - pillarWidth[i], pillarTopY[i] + 35 - i * 3);

            glColor3f(0.68, 0.70, 0.71);
            glVertex2f(pillarX[i] - pillarWidth[i] * 0.7, pillarTopY[i] + 35 - i * 3);
            glVertex2f(pillarX[i] + pillarWidth[i] * 0.7, pillarTopY[i] + 35 - i * 3);
            glVertex2f(pillarX[i] + pillarWidth[i] * 0.7, 620);
            glVertex2f(pillarX[i] - pillarWidth[i] * 0.7, 620);

            glColor3f(0.50, 0.52, 0.53);
            glVertex2f(pillarX[i] - pillarWidth[i] * 0.7, pillarTopY[i] + 35 - i * 3);
            glVertex2f(pillarX[i] - pillarWidth[i] * 0.3, pillarTopY[i] + 35 - i * 3);
            glVertex2f(pillarX[i] - pillarWidth[i] * 0.3, 620);
            glVertex2f(pillarX[i] - pillarWidth[i] * 0.7, 620);
        glEnd();
    }

    // Rail tracks
    glColor3f(0.25, 0.27, 0.28);
    glLineWidth(2.5);
    glBegin(GL_LINES);
        glVertex2f(0, 302); glVertex2f(1600, 273);
        glVertex2f(0, 318); glVertex2f(1600, 280);
    glEnd();
    glLineWidth(1.0);

    // METRO TRAIN
    glPushMatrix();
    glTranslatef(scene5_trainOffset, -scene5_trainOffset * 0.02, 0.0);

    float trainStartX = 465.0, trainEndX = 1600.0;
    float roofYStart = 205.0, roofYEnd = 265.0;
    float floorYStart = 300.0, floorYEnd = 293.0;

    glBegin(GL_QUADS);
        glColor3f(0.94, 0.95, 0.94);
        glVertex2f(trainStartX, roofYStart);
        glVertex2f(trainEndX, roofYEnd);
        glVertex2f(trainEndX, floorYEnd);
        glVertex2f(trainStartX, floorYStart);

        glColor3f(0.70, 0.72, 0.73);
        glVertex2f(trainStartX, roofYStart);
        glVertex2f(trainEndX, roofYEnd);
        glVertex2f(trainEndX, roofYEnd + 3);
        glVertex2f(trainStartX, roofYStart + 7);

        glColor3f(0.04, 0.42, 0.22);
        glVertex2f(trainStartX, roofYStart + 8);
        glVertex2f(trainEndX, roofYEnd + 3);
        glVertex2f(trainEndX, roofYEnd + 6);
        glVertex2f(trainStartX, roofYStart + 16);

        glVertex2f(trainStartX, floorYStart - 18);
        glVertex2f(trainEndX, floorYEnd - 5);
        glVertex2f(trainEndX, floorYEnd - 2);
        glVertex2f(trainStartX, floorYStart - 10);

        glColor3f(0.22, 0.24, 0.25);
        glVertex2f(trainStartX, floorYStart);
        glVertex2f(trainEndX, floorYEnd);
        glVertex2f(trainEndX, floorYEnd + 4);
        glVertex2f(trainStartX, floorYStart + 7);
    glEnd();

    // Train nose
    glColor3f(0.04, 0.42, 0.22);
    glBegin(GL_POLYGON);
        glVertex2f(trainStartX, roofYStart + 8);
        glVertex2f(trainStartX - 25, roofYStart + 18);
        glVertex2f(trainStartX - 40, roofYStart + 45);
        glVertex2f(trainStartX - 30, floorYStart - 15);
        glVertex2f(trainStartX, floorYStart);
    glEnd();

    // Driver windshield
    glColor3f(0.08, 0.16, 0.22);
    glBegin(GL_POLYGON);
        glVertex2f(trainStartX - 8, roofYStart + 20);
        glVertex2f(trainStartX - 32, roofYStart + 40);
        glVertex2f(trainStartX - 15, roofYStart + 65);
        glVertex2f(trainStartX, roofYStart + 65);
        glVertex2f(trainStartX, roofYStart + 20);
    glEnd();

    // Train red light
    glColor3f(0.85, 0.12, 0.12);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i += 10)
    {
        float angle = i * PI / 180;
        glVertex2f(trainStartX - 22 + 4 * cos(angle), floorYStart - 25 + 4 * sin(angle));
    }
    glEnd();

    // Coach windows
    float coachWindowSpans[][2] = {
        {0.015, 0.040}, {0.055, 0.085}, {0.095, 0.125}, {0.140, 0.170}, {0.185, 0.215}, {0.225, 0.255},
        {0.280, 0.305}, {0.318, 0.342}, {0.352, 0.376}, {0.390, 0.415}, {0.428, 0.452}, {0.462, 0.486},
        {0.510, 0.530}, {0.540, 0.560}, {0.570, 0.590}, {0.602, 0.622}, {0.632, 0.652}, {0.662, 0.682},
        {0.705, 0.722}, {0.730, 0.747}, {0.755, 0.772}, {0.785, 0.800}, {0.810, 0.825}, {0.835, 0.850},
        {0.865, 0.878}, {0.888, 0.901}, {0.910, 0.923}, {0.935, 0.946}, {0.954, 0.965}, {0.973, 0.984}
    };
    int windowCount = sizeof(coachWindowSpans) / sizeof(coachWindowSpans[0]);

    for (int i = 0; i < windowCount; i++)
    {
        float t1 = coachWindowSpans[i][0], t2 = coachWindowSpans[i][1];
        float wx1 = trainStartX + t1 * (trainEndX - trainStartX);
        float wx2 = trainStartX + t2 * (trainEndX - trainStartX);
        float topY1 = roofYStart + t1 * (roofYEnd - roofYStart);
        float topY2 = roofYStart + t2 * (roofYEnd - roofYStart);
        float botY1 = floorYStart + t1 * (floorYEnd - floorYStart);
        float botY2 = floorYStart + t2 * (floorYEnd - floorYStart);
        float bodyHeight1 = botY1 - topY1, bodyHeight2 = botY2 - topY2;
        float winTop1 = topY1 + bodyHeight1 * 0.28, winTop2 = topY2 + bodyHeight2 * 0.28;
        float winBot1 = topY1 + bodyHeight1 * 0.72, winBot2 = topY2 + bodyHeight2 * 0.72;

        glColor3f(0.08, 0.18, 0.24);
        glBegin(GL_QUADS);
            glVertex2f(wx1, winTop1);
            glVertex2f(wx2, winTop2);
            glVertex2f(wx2, winBot2);
            glVertex2f(wx1, winBot1);
        glEnd();

        glColor3f(0.40, 0.42, 0.44);
        glLineWidth(1.2);
        glBegin(GL_LINE_LOOP);
            glVertex2f(wx1, winTop1);
            glVertex2f(wx2, winTop2);
            glVertex2f(wx2, winBot2);
            glVertex2f(wx1, winBot1);
        glEnd();
    }
    glPopMatrix();

    // METRO STATION BUILDING
    glBegin(GL_QUADS);
        glColor3f(0.93, 0.91, 0.82);
        glVertex2f(520, 520);
        glVertex2f(1100, 520);
        glVertex2f(1100, 770);
        glVertex2f(520, 770);

        glColor3f(0.08, 0.40, 0.22);
        glVertex2f(520, 420);
        glVertex2f(1100, 420);
        glVertex2f(1100, 520);
        glVertex2f(520, 520);

        glColor3f(0.96, 0.95, 0.90);
        glVertex2f(590, 435);
        glVertex2f(990, 435);
        glVertex2f(990, 525);
        glVertex2f(590, 525);
    glEnd();

    glColor3f(0.22, 0.58, 0.34);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
        glVertex2f(520, 420);
        glVertex2f(1100, 420);
    glEnd();

    // STATION CANOPY ROOF
    float wallTopLx = 520,  wallTopLy = 420;
    float wallTopRx = 1100, wallTopRy = 420;
    float fasciaTopLx = 520,  fasciaTopLy = 405;
    float fasciaTopRx = 1100, fasciaTopRy = 405;
    float roofTopLx = 520,  roofTopLy = 375;
    float roofTopRx = 1100, roofTopRy = 375;

    glColor3f(0.03, 0.16, 0.09);
    glBegin(GL_QUADS);
        glVertex2f(wallTopLx, wallTopLy);
        glVertex2f(wallTopRx, wallTopRy);
        glVertex2f(wallTopRx, wallTopRy + 8);
        glVertex2f(wallTopLx, wallTopLy + 8);
    glEnd();

    glColor3f(0.05, 0.24, 0.13);
    glBegin(GL_QUADS);
        glVertex2f(fasciaTopLx, fasciaTopLy);
        glVertex2f(fasciaTopRx, fasciaTopRy);
        glVertex2f(wallTopRx, wallTopRy);
        glVertex2f(wallTopLx, wallTopLy);
    glEnd();

    glColor3f(0.10, 0.45, 0.25);
    glBegin(GL_QUADS);
        glVertex2f(roofTopLx, roofTopLy);
        glVertex2f(roofTopRx, roofTopRy);
        glVertex2f(fasciaTopRx, fasciaTopRy);
        glVertex2f(fasciaTopLx, fasciaTopLy);
    glEnd();

    glColor3f(0.06, 0.30, 0.16);
    glLineWidth(1.5);
    glBegin(GL_LINES);
    int panelCount = 12;
    for (int i = 0; i <= panelCount; i++)
    {
        float t = (float)i / panelCount;
        float topX = roofTopLx + t * (roofTopRx - roofTopLx);
        float topY = roofTopLy + t * (roofTopRy - roofTopLy);
        float botX = fasciaTopLx + t * (fasciaTopRx - fasciaTopLx);
        float botY = fasciaTopLy + t * (fasciaTopRy - fasciaTopLy);
        glVertex2f(topX, topY);
        glVertex2f(botX, botY);
    }
    glEnd();

    glColor3f(0.03, 0.16, 0.09);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
        glVertex2f(roofTopLx, roofTopLy);
        glVertex2f(roofTopRx, roofTopRy);
        glVertex2f(fasciaTopRx, fasciaTopRy);
        glVertex2f(wallTopRx, wallTopRy);
        glVertex2f(wallTopLx, wallTopLy);
        glVertex2f(fasciaTopLx, fasciaTopLy);
    glEnd();

    glColor3f(0.08, 0.35, 0.18);
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
        glVertex2f(590, 435);
        glVertex2f(990, 435);
        glVertex2f(990, 525);
        glVertex2f(590, 525);
    glEnd();
    glLineWidth(1.0);

    glColor3f(0.05, 0.45, 0.20);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i += 10)
    {
        float angle = i * PI / 180;
        glVertex2f(640 + 25 * cos(angle), 480 + 25 * sin(angle));
    }
    glEnd();

    glColor3f(0.85, 0.15, 0.12);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i += 10)
    {
        float angle = i * PI / 180;
        glVertex2f(648 + 14 * cos(angle), 473 + 14 * sin(angle));
    }
    glEnd();

    // Fixed Text: Metro Station Signboard (Perfectly readable and centered)
    glColor3f(0.05, 0.05, 0.05);
    scene5_drawStrokeText("DHAKA UNIVERSITY", 690, 475, 0.11, 2.0);
    scene5_drawStrokeText("METRO STATION", 720, 510, 0.10, 2.0);

    // Windows & entrance area
    glBegin(GL_QUADS);
        glColor3f(0.25, 0.52, 0.68);
        glVertex2f(560, 565); glVertex2f(595, 565); glVertex2f(595, 660); glVertex2f(560, 660);
        glVertex2f(620, 565); glVertex2f(655, 565); glVertex2f(655, 660); glVertex2f(620, 660);
        glVertex2f(965, 580); glVertex2f(995, 580); glVertex2f(995, 675); glVertex2f(965, 675);
        glVertex2f(1025, 580); glVertex2f(1055, 580); glVertex2f(1055, 675); glVertex2f(1025, 675);

        glColor3f(0.08, 0.22, 0.15);
        glVertex2f(695, 550); glVertex2f(925, 550); glVertex2f(925, 700); glVertex2f(695, 700);
    glEnd();

    // Fixed Text: Entrance/Exit
    glColor3f(1.0, 1.0, 1.0);
    scene5_drawStrokeText("Entrance", 735, 575, 0.06, 1.2);
    scene5_drawStrokeText("Exit", 845, 575, 0.06, 1.2);

    // Entrance/exit arrows
    glLineWidth(2.5);
    glBegin(GL_LINES);
        glVertex2f(715, 565); glVertex2f(715, 585);
        glVertex2f(715, 585); glVertex2f(710, 580);
        glVertex2f(715, 585); glVertex2f(720, 580);

        glVertex2f(890, 585); glVertex2f(890, 565);
        glVertex2f(890, 565); glVertex2f(885, 570);
        glVertex2f(890, 565); glVertex2f(895, 570);
    glEnd();
    glLineWidth(1.0);

    // Turnstiles
    for (int i = 0; i < 4; i++)
    {
        float gateX = 730 + i * 48;
        glColor3f(0.20, 0.22, 0.25);
        glBegin(GL_QUADS);
            glVertex2f(gateX, 635);
            glVertex2f(gateX + 24, 635);
            glVertex2f(gateX + 24, 700);
            glVertex2f(gateX, 700);
        glEnd();

        glColor3f(0.1, 0.9, 0.2);
        glBegin(GL_POLYGON);
        for (int j = 0; j <= 360; j += 10)
        {
            float angle = j * PI / 180;
            glVertex2f(gateX + 12 + 3 * cos(angle), 655 + 3 * sin(angle));
        }
        glEnd();
    }

    // Stairs
    glColor3f(0.70, 0.72, 0.72);
    glBegin(GL_QUADS);
        glVertex2f(640, 700);
        glVertex2f(980, 700);
        glVertex2f(1010, 765);
        glVertex2f(610, 765);
    glEnd();

    for (int s = 1; s <= 4; s++)
    {
        glColor3f(0.55, 0.57, 0.58);
        glLineWidth(2);
        glBegin(GL_LINES);
            glVertex2f(640 - s * 7, 700 + s * 16);
            glVertex2f(980 + s * 7, 700 + s * 16);
        glEnd();
    }
    glLineWidth(1.0);

    // ROAD + SIDEWALKS
    glBegin(GL_QUADS);
        glColor3f(0.80, 0.79, 0.76);
        glVertex2f(400, 765);
        glVertex2f(1120, 765);
        glVertex2f(1110, 815);
        glVertex2f(400, 815);
    glEnd();

    // Sidewalk curb
    for (int x = 400; x < 1110; x += 32)
    {
        if ((x / 32) % 2 == 0) glColor3f(0.95, 0.95, 0.95);
        else glColor3f(0.12, 0.12, 0.12);

        float xEnd = (x + 32 < 1110) ? x + 32 : 1110;
        glBegin(GL_QUADS);
            glVertex2f(x, 810);
            glVertex2f(xEnd, 810);
            glVertex2f(xEnd, 822);
            glVertex2f(x, 822);
        glEnd();
    }

    // Asphalt road
    glColor3f(0.38, 0.40, 0.44);
    glBegin(GL_QUADS);
        glVertex2f(1100, 822); glVertex2f(1550, 360);
        glVertex2f(1600, 360); glVertex2f(1600, 1000);

        glVertex2f(460, 822);  glVertex2f(1100, 822);
        glVertex2f(1600, 1000); glVertex2f(0, 1000);

        glVertex2f(0, 830);    glVertex2f(460, 822);
        glVertex2f(500, 1000); glVertex2f(0, 1000);
    glEnd();

    // Diagonal road curb
    for (int i = 0; i < 24; i++)
    {
        float t1 = (float)i / 24.0, t2 = (float)(i + 1) / 24.0;
        float x1 = 1110 + t1 * (1560 - 1110), y1 = 815 - t1 * (815 - 360);
        float x2 = 1110 + t2 * (1560 - 1110), y2 = 815 - t2 * (815 - 360);

        if (i % 2 == 0) glColor3f(0.95, 0.95, 0.95);
        else glColor3f(0.10, 0.10, 0.10);

        glBegin(GL_QUADS);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            glVertex2f(x2 + 10, y2);
            glVertex2f(x1 + 10, y1);
        glEnd();
    }

    // Footpath
    float sideDirX = -0.719, sideDirY = -0.695;
    float sidewalkWidth = 46.0;

    glColor3f(0.80, 0.79, 0.76);
    for (int i = 0; i < 24; i++)
    {
        float t1 = (float)i / 24.0, t2 = (float)(i + 1) / 24.0;
        float x1 = 1110 + t1 * (1560 - 1110), y1 = 815 - t1 * (815 - 360);
        float x2 = 1110 + t2 * (1560 - 1110), y2 = 815 - t2 * (815 - 360);

        glBegin(GL_QUADS);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            glVertex2f(x2 + sideDirX * sidewalkWidth, y2 + sideDirY * sidewalkWidth);
            glVertex2f(x1 + sideDirX * sidewalkWidth, y1 + sideDirY * sidewalkWidth);
        glEnd();
    }

    // Footpath edge curb
    for (int i = 0; i < 24; i++)
    {
        float t1 = (float)i / 24.0, t2 = (float)(i + 1) / 24.0;
        float x1 = 1110 + t1 * (1560 - 1110) + sideDirX * sidewalkWidth;
        float y1 = 815 - t1 * (815 - 360) + sideDirY * sidewalkWidth;
        float x2 = 1110 + t2 * (1560 - 1110) + sideDirX * sidewalkWidth;
        float y2 = 815 - t2 * (815 - 360) + sideDirY * sidewalkWidth;

        if (i % 2 == 0) glColor3f(0.95, 0.95, 0.95);
        else glColor3f(0.10, 0.10, 0.10);

        glBegin(GL_QUADS);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            glVertex2f(x2 + sideDirX * 8, y2 + sideDirY * 8);
            glVertex2f(x1 + sideDirX * 8, y1 + sideDirY * 8);
        glEnd();
    }

    // DIAGONAL CARS
    float baseCarX[3] = {1260, 1350, 1430};
    float baseCarY[3] = {910, 780, 640};
    float carColorR[3] = {0.88, 0.98, 0.10};
    float carColorG[3] = {0.90, 0.98, 0.45};
    float carColorB[3] = {0.92, 0.98, 0.85};

    for (int c = 0; c < 3; c++)
    {
        glPushMatrix();
        float cx = baseCarX[c] - scene5_carOffset * sin(32.0 * PI / 180.0);
        float cy = baseCarY[c] + scene5_carOffset * cos(32.0 * PI / 180.0);

        glTranslatef(cx, cy, 0.0);
        glRotatef(32.0, 0.0, 0.0, 1.0);
        glScalef(0.85, 0.85, 1.0);

        glColor3f(0.20, 0.22, 0.24);
        glBegin(GL_QUADS);
            glVertex2f(-30, -58); glVertex2f(30, -58);
            glVertex2f(30, 58);   glVertex2f(-30, 58);
        glEnd();

        glColor3f(carColorR[c], carColorG[c], carColorB[c]);
        glBegin(GL_POLYGON);
            glVertex2f(-26, -52); glVertex2f(26, -52);
            glVertex2f(28, 52);   glVertex2f(-28, 52);
        glEnd();

        glBegin(GL_QUADS);
            glColor3f(0.10, 0.18, 0.25);
            glVertex2f(-21, -30); glVertex2f(21, -30);
            glVertex2f(21, -10);  glVertex2f(-21, -10);

            glVertex2f(-21, 16); glVertex2f(21, 16);
            glVertex2f(21, 32);  glVertex2f(-21, 32);

            glColor3f(carColorR[c] * 0.85, carColorG[c] * 0.85, carColorB[c] * 0.85);
            glVertex2f(-19, -10); glVertex2f(19, -10);
            glVertex2f(19, 16);   glVertex2f(-19, 16);

            glColor3f(1.0, 0.95, 0.65);
            glVertex2f(-24, -54); glVertex2f(-13, -54);
            glVertex2f(-13, -50); glVertex2f(-24, -50);
            glVertex2f(13, -54);  glVertex2f(24, -54);
            glVertex2f(24, -50);  glVertex2f(13, -50);

            glColor3f(0.9, 0.1, 0.1);
            glVertex2f(-24, 50); glVertex2f(-13, 50);
            glVertex2f(-13, 54); glVertex2f(-24, 54);
            glVertex2f(13, 50);  glVertex2f(24, 50);
            glVertex2f(24, 54);  glVertex2f(13, 54);
        glEnd();

        glPopMatrix();
    }

    // HORIZONTAL CARS (Bottom Road)
    float hCarY_LR[4] = {870, 930, 870, 930};
    float hCarColorR_LR[4] = {0.15, 0.90, 0.30, 0.70};
    float hCarColorG_LR[4] = {0.65, 0.50, 0.40, 0.20};
    float hCarColorB_LR[4] = {0.85, 0.10, 0.80, 0.50};

    for (int c = 0; c < 4; c++)
    {
        glPushMatrix();
        float cx = (scene5_carOffset * 1.8) + 100 - (c * 280);
        float cy = hCarY_LR[c];

        glTranslatef(cx, cy, 0.0);
        glRotatef(-90.0, 0.0, 0.0, 1.0);
        glScalef(0.85, 0.85, 1.0);

        glColor3f(0.20, 0.22, 0.24);
        glBegin(GL_QUADS);
            glVertex2f(-30, -58); glVertex2f(30, -58);
            glVertex2f(30, 58);   glVertex2f(-30, 58);
        glEnd();

        glColor3f(hCarColorR_LR[c], hCarColorG_LR[c], hCarColorB_LR[c]);
        glBegin(GL_POLYGON);
            glVertex2f(-26, -52); glVertex2f(26, -52);
            glVertex2f(28, 52);   glVertex2f(-28, 52);
        glEnd();

        glBegin(GL_QUADS);
            glColor3f(0.10, 0.18, 0.25);
            glVertex2f(-21, -30); glVertex2f(21, -30);
            glVertex2f(21, -10);  glVertex2f(-21, -10);

            glVertex2f(-21, 16); glVertex2f(21, 16);
            glVertex2f(21, 32);  glVertex2f(-21, 32);

            glColor3f(hCarColorR_LR[c] * 0.85, hCarColorG_LR[c] * 0.85, hCarColorB_LR[c] * 0.85);
            glVertex2f(-19, -10); glVertex2f(19, -10);
            glVertex2f(19, 16);   glVertex2f(-19, 16);

            glColor3f(1.0, 0.95, 0.65);
            glVertex2f(-24, -54); glVertex2f(-13, -54);
            glVertex2f(-13, -50); glVertex2f(-24, -50);
            glVertex2f(13, -54);  glVertex2f(24, -54);
            glVertex2f(24, -50);  glVertex2f(13, -50);

            glColor3f(0.9, 0.1, 0.1);
            glVertex2f(-24, 50); glVertex2f(-13, 50);
            glVertex2f(-13, 54); glVertex2f(-24, 54);
            glVertex2f(13, 50);  glVertex2f(24, 50);
            glVertex2f(24, 54);  glVertex2f(13, 54);
        glEnd();

        glPopMatrix();
    }

    // TRAFFIC LIGHT
    float lightPoleX = 480, lightPoleY = 675;
    glBegin(GL_QUADS);
        glColor3f(0.18, 0.20, 0.22);
        glVertex2f(lightPoleX - 4, lightPoleY);
        glVertex2f(lightPoleX + 4, lightPoleY);
        glVertex2f(lightPoleX + 4, lightPoleY + 160);
        glVertex2f(lightPoleX - 4, lightPoleY + 160);

        glColor3f(0.08, 0.08, 0.08);
        glVertex2f(lightPoleX - 14, lightPoleY - 55);
        glVertex2f(lightPoleX + 14, lightPoleY - 55);
        glVertex2f(lightPoleX + 14, lightPoleY);
        glVertex2f(lightPoleX - 14, lightPoleY);
    glEnd();

    float lightY[3] = {lightPoleY - 43, lightPoleY - 27, lightPoleY - 11};
    float lightColor[3][3] = {{0.95, 0.10, 0.10}, {0.95, 0.70, 0.05}, {0.10, 0.85, 0.20}};
    for (int l = 0; l < 3; l++)
    {
        glColor3f(lightColor[l][0], lightColor[l][1], lightColor[l][2]);
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 360; i += 10)
        {
            float angle = i * PI / 180;
            glVertex2f(lightPoleX + 6 * cos(angle), lightY[l] + 6 * sin(angle));
        }
        glEnd();
    }

    // PEDESTRIANS
    float pedX[5] = {545, 610, 725, 980, 1060};
    float pedY[5] = {765, 765, 770, 785, 785};
    float pedScale[5] = {0.95, 0.95, 0.95, 0.90, 0.90};
    float pedColorR[5] = {0.12, 0.85, 0.15, 0.18, 0.88};
    float pedColorG[5] = {0.45, 0.25, 0.60, 0.22, 0.70};
    float pedColorB[5] = {0.80, 0.45, 0.25, 0.75, 0.15};

    for (int p = 0; p < 5; p++)
    {
        float px = pedX[p], py = pedY[p], s = pedScale[p];

        glColor3f(0.82, 0.58, 0.42);
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 360; i += 10)
        {
            float angle = i * PI / 180;
            float r = 6.5 * s;
            glVertex2f(px + r * cos(angle), py - 48 * s + r * sin(angle));
        }
        glEnd();

        glColor3f(pedColorR[p], pedColorG[p], pedColorB[p]);
        glBegin(GL_QUADS);
            glVertex2f(px - 6 * s, py - 40 * s);
            glVertex2f(px + 6 * s, py - 40 * s);
            glVertex2f(px + 6 * s, py - 18 * s);
            glVertex2f(px - 6 * s, py - 18 * s);
        glEnd();

        glColor3f(0.12, 0.15, 0.25);
        glLineWidth(3 * s);
        glBegin(GL_LINES);
            glVertex2f(px - 3 * s, py - 18 * s); glVertex2f(px - 7 * s, py);
            glVertex2f(px + 3 * s, py - 18 * s); glVertex2f(px + 7 * s, py);
            glVertex2f(px - 5 * s, py - 38 * s); glVertex2f(px - 10 * s, py - 22 * s);
            glVertex2f(px + 5 * s, py - 38 * s); glVertex2f(px + 10 * s, py - 22 * s);
        glEnd();
        glLineWidth(1.0);
    }

    glFlush();
}


void sound()
{
    PlaySound("a.wav", NULL, SND_ASYNC | SND_FILENAME);
}

void stopSound()
{
    PlaySound(NULL, NULL, 0);
}

void updateMetroSound(int visible)
{
    if(projectStarted == 0)
        return;

    if(soundMuted == 1)
        return;

    if(visible == 1 && metroSoundOn == 0)
    {
        sound();
        metroSoundOn = 1;
    }

    if(visible == 0 && metroSoundOn == 1)
    {
        stopSound();
        metroSoundOn = 0;
    }
}

void handleKeypress(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 13:   // ENTER
            if(currentPage == 0)
            {
                currentPage = 1;
                glutDisplayFunc(drawInstructionPage);
            }
            break;

        case 's':
        case 'S':
            if(currentPage == 1)
            {
                currentPage = 2;
                projectStarted = 1;
                activeScene = 1;
                scene1_init();
                glutDisplayFunc(scene1_display);
                updateMetroSound((scene1_trainPosition + 12.3f > 0.0f) &&
                                 (scene1_trainPosition + 0.5f < 20.0f));
            }
            break;

        case '1':
            currentPage = 2;
            projectStarted = 1;
            stopSound();
            metroSoundOn = 0;
            activeScene = 1;
            scene1_init();
            glutDisplayFunc(scene1_display);
            updateMetroSound((scene1_trainPosition + 12.3f > 0.0f) &&
                             (scene1_trainPosition + 0.5f < 20.0f));
            break;

        case '2':
            currentPage = 2;
            projectStarted = 1;
            stopSound();
            metroSoundOn = 0;
            activeScene = 2;
            scene2_init();
            glutDisplayFunc(scene2_display);
            updateMetroSound((scene2_trainPosition + 12.0f > 0.0f) &&
                             (scene2_trainPosition + 0.2f < 20.0f));
            break;

        case '3':
            currentPage = 2;
            projectStarted = 1;
            stopSound();
            metroSoundOn = 0;
            activeScene = 3;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(-1, 1, -1, 1);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            scene3_init();
            glutDisplayFunc(scene3_display);
            updateMetroSound((scene3_trainPos + 0.9f > -1.0f) &&
                             (scene3_trainPos - 0.2f < 1.0f));
            break;

        case '4':
            currentPage = 2;
            projectStarted = 1;
            stopSound();
            metroSoundOn = 0;
            activeScene = 4;
            scene4_init();
            glutDisplayFunc(scene4_display);
            updateMetroSound((14.62f - scene4_trainPosition > 0.0f) &&
                             (6.33f - scene4_trainPosition < 20.0f));
            break;

        case '5':
            currentPage = 2;
            projectStarted = 1;
            stopSound();
            metroSoundOn = 0;
            activeScene = 5;
            scene5_init();
            glutDisplayFunc(scene5_display);
            updateMetroSound((1600.0f + scene5_trainOffset > 0.0f) &&
                             (425.0f + scene5_trainOffset < 1550.0f));
            break;

        case 'm':
        case 'M':
            soundMuted = 1;
            stopSound();
            metroSoundOn = 0;
            break;

        case 'p':
        case 'P':
            soundMuted = 0;
            stopSound();
            metroSoundOn = 0;

            if(activeScene == 1)
                updateMetroSound((scene1_trainPosition + 12.3f > 0.0f) &&
                                 (scene1_trainPosition + 0.5f < 20.0f));

            else if(activeScene == 2)
                updateMetroSound((scene2_trainPosition + 12.0f > 0.0f) &&
                                 (scene2_trainPosition + 0.2f < 20.0f));

            else if(activeScene == 3)
                updateMetroSound((scene3_trainPos + 0.9f > -1.0f) &&
                                 (scene3_trainPos - 0.2f < 1.0f));

            else if(activeScene == 4)
                updateMetroSound((14.62f - scene4_trainPosition > 0.0f) &&
                                 (6.33f - scene4_trainPosition < 20.0f));

            else if(activeScene == 5)
                updateMetroSound((1600.0f + scene5_trainOffset > 0.0f) &&
                                 (425.0f + scene5_trainOffset < 1550.0f));
            break;

        case 27:
            stopSound();
            exit(0);
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 700);
    glutInitWindowPosition(50, 30);
    glutCreateWindow("Metro Rail Project");

    pageInit();

    glutDisplayFunc(drawCoverPage);
    glutKeyboardFunc(handleKeypress);
    glutTimerFunc(30, scene1_update, 0);
    glutTimerFunc(30, scene2_update, 0);
    glutTimerFunc(100, scene3_update, 0);
    glutTimerFunc(100, scene4_update, 0);
    glutTimerFunc(16, scene5_timer, 0);

    glutMainLoop();

    return 0;
}
