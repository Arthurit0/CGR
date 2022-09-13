#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "engine.c"

static int wtm = 800;
static int htm = 600;
static GLfloat yRot = 0.0f;
static GLfloat xRot = 0.0f;
static GLfloat perspective = 70.0f;
static GLfloat rtt = 0.0f;

// Change viewing volume and viewport.  Called when window is resized
// Ajusta a janela (tamanho)
void ChangeSize(int w, int h) {
    GLfloat fAspect;

    // Prevent a divide by zero
    if (h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w / (GLfloat)h;

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Produce the perspective projection
    gluPerspective(perspective, fAspect, 1.0, 40.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.
// Renderização
void SetupRC() {
    // Light values and coordinates
    GLfloat whiteLight[] = {0.05f, 0.05f, 0.05f, 1.0f};
    GLfloat sourceLight[] = {0.25f, 0.25f, 0.25f, 1.0f};
    GLfloat lightPos[] = {-10.f, 5.0f, 5.0f, 1.0f};

    glEnable(GL_DEPTH_TEST);  // Hidden surface removal
    glFrontFace(GL_CCW);      // Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);   // Do not calculate inside

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Black blue background
    glClearColor(0.0f, 0.4f, 0.0f, 0.0f);
}

// Respond to arrow keys (rotate snowman)
// Move a camera para esquerda e para Direita
void SpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT)
        yRot -= 5.0f;

    if (key == GLUT_KEY_RIGHT)
        yRot += 5.0f;

    if (key == GLUT_KEY_UP)
        xRot -= 5.0f;

    if (key == GLUT_KEY_DOWN)
        xRot += 5.0f;

    ChangeSize(800, 600);
    yRot = (GLfloat)((const int)yRot % 360);
    xRot = (GLfloat)((const int)xRot % 360);

    // Refresh the Window
    glutPostRedisplay();
}

void mouseClick(int btn, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        switch (btn) {
            case GLUT_LEFT_BUTTON:
                break;
            case GLUT_RIGHT_BUTTON:
                break;
            case GLUT_MIDDLE_BUTTON:
                break;
            case 3:
                perspective += 3.0f;
                ChangeSize(wtm, htm);
                break;
            case 4:
                perspective -= 3.0f;
                ChangeSize(wtm, htm);
                break;
            default:
                break;
        }
    }

    glutPostRedisplay();
}
void NormalKeyHandler(unsigned char key, int x, int y) {
    if (key == 'w')
        rtt += 1.0f;
    else if (key == 's')
        rtt -= 1.0f;
    ;

    glutPostRedisplay();
}

void paint(void) {
    GLfloat tm = -3.0f;

    Element *e = criaElement(tl(-1.0f, -1.0f, -5.0f), rt(yRot, 0.0f, 1.0f, 0.0f), rt(xRot, 1.0f, 0.0f, 0.0f), cl(1.0f, 0.0f, 0.0f));

    // esfera(e, cordE(0.25f, 0.25f, 0.25f), tl(1.0f,0.0f,0.0f), rt(0.0f,0.0f,0.0f,0.0f), cl(1.0f,0.0f,0.0f));
    // cilindro(e, cordC(0.25f, 0.25f, 0.5f, 26, 13), tl(1.0f,rtt,0.0f), rt(90,1.0f,0.0f,0.0f), cl(1.0f,0.0f,0.0f));

    // Perna 1
    cubo(e, cordP(0.25f, 0.25f, 0.25f, 1.0f), tl(0.0f, 0.0f + tm, 0.0f), rt(90, 1.0f, 0.0f, 0.0f), cl(1.0f, 0.0f, 0.0f));
    cubo(e, cordP(0.05f, 1.0f, 0.05f, 0.7f), tl(0.02f, 1.6f + tm, -0.05f), rt(0, 1.0f, 0.0f, 0.0f), cl(0.0f, 0.0f, 1.0f));

    // Perna 2
    cubo(e, cordP(0.25f, 0.25f, 0.25f, 1.0f), tl(1.6f, 0.0f + tm, 0.0f), rt(90, 1.0f, 0.0f, 0.0f), cl(1.0f, 0.0f, 0.0f));
    cubo(e, cordP(0.05f, 1.0f, 0.05f, 0.7f), tl(1.62f, 1.6f + tm, -0.05f), rt(0, 1.0f, 0.0f, 0.0f), cl(0.0f, 0.0f, 1.0f));

    // Corpo
    cubo(e, cordP(2.0f, 2.0f, 0.5f, 1.0f), tl(1.65f, 3.5f + tm, 0.0f), rt(0, 1.0f, 0.0f, 0.0f), cl(1.0f, 1.0f, 0.0f));

    // Braço 1
    cubo(e, cordP(0.05f, 1.5f, 0.05f, 0.7f), tl(2.5f, 4.5f + tm, 0.0f), rt(90, 1.0f, 0.0f, 0.0f), cl(0.0f, 0.0f, 1.0f));

    // Braço 2
    cubo(e, cordP(0.05f, 1.5f, 0.05f, 0.7f), tl(-1.0f, 4.5f + tm, 0.0f), rt(90, 1.0f, 0.0f, 0.0f), cl(0.0f, 0.0f, 1.0f));

    // Cabeça
    cubo(e, cordP(1.0f, 1.0f, 0.5f, 1.0f), tl(1.15f, 6.5f + tm, 0.0f), rt(0, 1.0f, 0.0f, 0.0f), cl(1.0f, 1.0f, 1.0f));

    // olho 1
    cilindro(e, cordC(0.0f, 0.0f, 0.0f, 26, 13), tl(1.15f, 5.5f + tm, 2.0f), rt(0, 1.0f, 0.0f, 0.0f), cl(1.0f, 0.0f, 0.0f));

    // disco(e, cordD(0.25f, 0.25f, 1, 1), tl(1.15f,5.5f + tm,2.0f),rt(0,1.0f,0.0f,0.0f), cl(1.0f,0.0f,0.0f));

    // Boca
    cubo(e, cordP(1.0f, 0.1f, 0.1f, 0.2f), tl(1.6f, 6.0f + tm, 0.55f), rt(0, 1.0f, 0.0f, 0.0f), cl(0.0f, 0.0f, 0.0f));

    // cubo(e, cordP(70.0f, 0.0f, 0.0f, 0.1f), tl(0.0f,0.0f,0.0f),rt(90,1.0f,0.0f,0.0f), cl(0.0f,0.0f,1.0f));
    // cubo(e, cordP(0.0, 70.0f, 0.0f, 0.1f), tl(0.0f,0.0f,0.0f),rt(90,1.0f,0.0f,0.0f), cl(0.0f,0.0f,1.0f));
    // cubo(e, cordP(0.0f, 0.0f, -70.0f, 0.1f), tl(0.0f,0.0f,0.0f),rt(90,1.0f,0.0f,0.0f), cl(0.0f,0.0f,1.0f));

    compile(e);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(wtm, htm);
    glutCreateWindow("ROBO");

    glutMouseFunc(mouseClick);
    glutKeyboardFunc(NormalKeyHandler);

    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(paint);
    SetupRC();
    glutMainLoop();

    return 0;
}
