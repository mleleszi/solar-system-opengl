#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

float rotationSpeed = 0.0;
float rotationSpeed01 = 0.0;
float rotationSpeed02 = 0.0;
float rotationSpeed03 = 0.0;

float self_angle = 0.0f;

void createCircle(float radius){
    float angle = 0.0f;
    glLineWidth(3.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        int i;
        for(i = 0; i < 100; ++i){
            angle = 2 * M_PI * i / 100;
            glVertex3f(radius * cos(angle), 0.0, radius * sin(angle));
        }
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(-60.0, 40.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Sun
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.5f, 0.0f);
    glRotatef(self_angle, 0.0, 1.0, 0.0);
    glutSolidSphere(6.5, 15, 15);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    // Mercury
    createCircle(12.0);
    glPushMatrix();
    glTranslatef(12.0 * cos(rotationSpeed / 0.25), 0.0, 12.0 * sin(rotationSpeed / 0.25));
    glRotatef(self_angle, 0.0f, 1.0f, 0.0);
    glDisable(GL_LIGHTING);
    glColor3f(0.0f, 0.7f, 0.6f);
    glutSolidSphere(1.5, 15, 15);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    // Venus
    createCircle(19.0);
    glPushMatrix();
    glTranslatef(19.0 * cos(rotationSpeed01 / 0.25), 0.0, 19.0 * sin(rotationSpeed01 / 0.25));
    glRotatef(self_angle, 0.0f, 1.0f, 0.0);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.9f, 0.7f);
    glutSolidSphere(3.0, 15, 15);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    // Earth
    createCircle(27.0);
    glPushMatrix();
    glTranslatef(27.0 * cos(rotationSpeed02 / 0.25), 0.0, 27.0 * sin(rotationSpeed02 / 0.25));
    glRotatef(self_angle, 1.0f, 0.0f, 0.0);
    glDisable(GL_LIGHTING);
    glColor3f(0.0f, 0.5f, 0.9f);
    glutSolidSphere(3.5, 15, 15);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    glutSwapBuffers();

}

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    GLfloat MATRIX_SHININESS[] = {50.0};
    GLfloat MATRIX_SPECULAR[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat LIGHT_POSITION[] = {0.0, 1.0, 1.0, 0.0};

    glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27:
            exit(0);
            break;
    }
}

void spinning(){
    rotationSpeed += 0.0006;
    rotationSpeed01 += 0.0004;
    rotationSpeed02 += 0.0002;
    rotationSpeed03 += 0.0001;

    glutPostRedisplay();
}

void reshape(GLsizei w, GLsizei h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.4, 0.4, -0.3, 0.3, 0.5, 2000);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(900, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Solar System Model Test");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(spinning);

    glutKeyboardFunc(keyboard);
    glutTimerFunc(25, spinning, 0);
    glutMainLoop();

    return 0;
}
