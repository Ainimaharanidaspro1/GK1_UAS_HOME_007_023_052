#include <glut.h>
#include <iostream>

float cameraX = 0.0f, cameraY = 5.0f, cameraZ = 15.0f;
float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;


float angleX = 0.0f, angleY = 0.0f;

void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightPos[] = { 0.0f, 10.0f, 10.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    GLfloat lightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
}

void drawCloud(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(0.5, 20, 20);
    glPushMatrix();
    glTranslatef(0.5f, 0.2f, 0.0f);
    glutSolidSphere(0.4, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.5f, 0.2f, 0.0f);
    glutSolidSphere(0.4, 20, 20);
    glPopMatrix();
    glPopMatrix();
}

void drawHouse() {
    glPushMatrix();
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);



    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.8f, 0.9f);
    glPushMatrix();
    glScalef(4.0f, 4.0f, 4.0f);
    glutSolidCube(1.0f);
    glPopMatrix();


    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    glScalef(5.0f, 2.0f, 5.0f);
    glutSolidOctahedron();
    glPopMatrix();


    glEnable(GL_LIGHTING);

    glColor3f(0.5f, 0.25f, 0.1f);
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 2.1f);
    glScalef(0.8f, 1.6f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();


    glColor3f(0.2f, 0.5f, 1.0f);
    glPushMatrix();
    glTranslatef(-1.5f, 0.5f, 2.1f);
    glScalef(0.6f, 0.6f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.5f, 0.5f, 2.1f);
    glScalef(0.6f, 0.6f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glColor3f(0.8f, 0.8f, 0.8f);
    for (int i = -3; i <= 3; ++i) {
        glPushMatrix();
        glTranslatef(i * 0.8f, -1.8f, 3.0f);
        glScalef(0.1f, 1.0f, 0.1f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
    glPopMatrix();

    drawCloud(-3.5f, 5.5f, -2.5f);
    drawCloud(3.5f, 5.5f, -2.5f);
    drawCloud(-2.0f, 4.0f, -3.0f);
    drawCloud(2.0f, 4.5f, -4.0f);
    drawCloud(0.0f, 5.0f, 0.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, centerX, centerY, centerZ, 0.0f, 1.0f, 0.0f);

    initLighting();
    drawHouse();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': cameraY += 1.0f; break;
    case 's': cameraY -= 1.0f; break;
    case 'a': cameraX -= 1.0f; break;
    case 'd': cameraX += 1.0f; break;
    case 'z': cameraZ += 1.0f; break;
    case 'x': cameraZ -= 1.0f; break;
    case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP: angleX -= 5.0f; break;
    case GLUT_KEY_DOWN: angleX += 5.0f; break;
    case GLUT_KEY_LEFT: angleY -= 5.0f; break;
    case GLUT_KEY_RIGHT: angleY += 5.0f; break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Enhanced 3D House with Clouds");

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.7f, 0.7f, 1.0f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}