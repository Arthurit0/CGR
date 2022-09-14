// gcc castle.c -lglut -lGL -lGLU -lm -o castle && ./castle

#include <GL/glut.h>

// Rotation
static GLfloat yRot = 0.0f;
static GLfloat xRot = 0.0f;

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
    gluPerspective(35.0f, fAspect, 1.0, 40.0);

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
    glClearColor(0.0f, 0.8f, 0.8f, 1.0f);
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

    yRot = (GLfloat)((const int)yRot % 360);
    xRot = (GLfloat)((const int)xRot % 360);

    // Refresh the Window
    glutPostRedisplay();
}

void drawBox(double l, double a, double c, double o)  // O CUBO
{
    glBegin(GL_QUADS);

    // FRONT
    glVertex3f(-l, -o, c);
    glVertex3f(o, -o, c);
    glVertex3f(o, a, c);
    glVertex3f(-l, a, c);
    // BACK
    glVertex3f(-l, -o, -o);
    glVertex3f(-l, a, -o);
    glVertex3f(o, a, -o);
    glVertex3f(o, -o, -o);

    // LEFT
    glVertex3f(-l, -o, c);
    glVertex3f(-l, a, c);
    glVertex3f(-l, a, -o);
    glVertex3f(-l, -o, -o);

    // RIGHT
    glVertex3f(o, -o, -o);
    glVertex3f(o, a, -o);
    glVertex3f(o, a, c);
    glVertex3f(o, -o, c);

    // TOP
    glVertex3f(-l, a, c);
    glVertex3f(o, a, c);
    glVertex3f(o, a, -o);
    glVertex3f(-l, a, -o);

    // BOTTOM
    glVertex3f(-l, -o, c);
    glVertex3f(-l, -o, -o);
    glVertex3f(o, -o, -o);
    glVertex3f(o, -o, c);

    glEnd();
}

// Called to draw scene
// Desenho em si
void RenderScene(void) {
    // cria objeto
    GLUquadricObj *pObj;

    // limpa tudo
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // inicia a pilha da matrix
    glPushMatrix();
    // Informação principais
    // Move object back and do in place rotation
    glTranslatef(0.0f, -1.0f, -5.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    // Draw something
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);

    // Desenho
    // cilindro 1
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-1.0f, 1.0f, 0.2f);
    glRotatef(90, 1.2f, 0.0f, 0.0f);
    // (obj, raio-baixo, raio-alto, altura, fatias , pilhas)
    gluCylinder(pObj, 0.25f, 0.25f, 0.5f, 26, 13);
    glPopMatrix();
    // cilindro2 do lado do c1
    glPushMatrix();
    glTranslatef(0.5f, 1.0f, 0.2f);
    glRotatef(90, 1.2f, 0.0f, 0.0f);
    // (obj, raio-baixo, raio-alto, altura, fatias , pilhas)
    gluCylinder(pObj, 0.25f, 0.25f, 0.5f, 26, 13);
    glPopMatrix();
    // cilindro3 atrás do c1
    glPushMatrix();
    glTranslatef(-1.0f, 1.0f, 1.7f);
    glRotatef(90, 1.2f, 0.0f, 0.0f);
    // (obj, raio-baixo, raio-alto, altura, fatias , pilhas)
    gluCylinder(pObj, 0.25f, 0.25f, 0.5f, 26, 13);
    glPopMatrix();
    // cilindro4 atrás do c2
    glPushMatrix();
    glTranslatef(0.5f, 1.0f, 1.7f);
    glRotatef(90, 1.2f, 0.0f, 0.0f);
    // (obj, raio-baixo, raio-alto, altura, fatias , pilhas)
    gluCylinder(pObj, 0.25f, 0.25f, 0.5f, 26, 13);
    glPopMatrix();
    // cilindro central
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-0.25f, 1.4f, 0.95f);
    glRotatef(90, 1.2f, 0.0f, 0.0f);
    // (obj, raio-baixo, raio-alto, altura, fatias , pilhas)
    gluCylinder(pObj, 0.25f, 0.25f, 0.9f, 26, 13);
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-0.25f, 1.6f, 0.95f);
    glRotatef(90, 1.2f, 0.0f, 0.0f);
    // (obj, raio-baixo, raio-alto, altura, fatias , pilhas)
    gluCylinder(pObj, 0.28f, 0.28f, 0.3f, 26, 13);
    glPopMatrix();
    // telhado Central
    glColor3f(0.5f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(-0.25f, 1.89f, 0.95f);
    glRotatef(90, 1.2f, 0.0f, 0.0f);
    // (obj, raio-baixo, raio-alto, altura, fatias , pilhas)
    gluCylinder(pObj, 0.0f, 0.3f, 0.3f, 26, 13);
    glPopMatrix();

    // Parede 1 entre c1 e c2
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.25f, 0.5f, 0.1f);
    // largura, altura, comprimento
    drawBox(1.0f, 0.5f, 0.2f, 0.0f);
    glPopMatrix();

    // Parede 2 entre c3 e c4
    glPushMatrix();
    glTranslatef(0.25f, 0.5f, 1.6f);
    // largura, altura, comprimento
    drawBox(1.0f, 0.5f, 0.2f, 0.0f);
    glPopMatrix();

    // Parede 3 entre c1 e c2
    glPushMatrix();
    glTranslatef(-1.0f, 0.5f, 0.45f);
    // largura, altura, comprimento
    drawBox(0.2f, 0.5f, 1.0f, 0.0f);
    glPopMatrix();
    // Parede 4 entre c1 e c3
    glPushMatrix();
    glTranslatef(0.575f, 0.5f, 0.45f);
    // largura, altura, comprimento
    drawBox(0.2f, 0.5f, 1.0f, 0.0f);
    glPopMatrix();

    // telhado 4
    glColor3f(0.5f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(0.5f, 1.3f, 1.7f);
    glRotatef(90, 1.2f, 0.0f, 0.0f);
    // (obj, raio-baixo, raio-alto, altura, fatias , pilhas)
    gluCylinder(pObj, 0.0f, 0.25f, 0.3f, 26, 13);
    glPopMatrix();
    // telhado 1
    glPushMatrix();
    glTranslatef(-1.0f, 1.3f, 0.2f);
    glRotatef(90, 1.2f, 0.0f, 0.0f);
    // (obj, raio-baixo, raio-alto, altura, fatias , pilhas)
    gluCylinder(pObj, 0.0f, 0.25f, 0.3f, 26, 13);
    glPopMatrix();
    // telhado 2
    glPushMatrix();
    glTranslatef(0.5f, 1.3f, 0.2f);
    glRotatef(90, 1.2f, 0.0f, 0.0f);
    // (obj, raio-baixo, raio-alto, altura, fatias , pilhas)
    gluCylinder(pObj, 0.0f, 0.25f, 0.3f, 26, 13);
    glPopMatrix();
    // telhado 3
    glPushMatrix();
    glTranslatef(-1.0f, 1.3f, 1.7f);
    glRotatef(90, 1.2f, 0.0f, 0.0f);
    // (obj, raio-baixo, raio-alto, altura, fatias , pilhas)
    gluCylinder(pObj, 0.0f, 0.25f, 0.3f, 26, 13);
    glPopMatrix();

    // Chao
    glColor3f(0.0f, 1.0f, 0.7f);
    glPushMatrix();
    double tm = 100.0f;
    glTranslatef((tm / 2), 0.49f, -(tm / 2) + 0.7);
    // largura, altura, comprimento
    drawBox(tm, 0.0f, tm, 0.0f);
    glPopMatrix();

    // finaliza a pilha da matrix
    glPopMatrix();

    // Buffer
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Modelando com quadricas!");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}
