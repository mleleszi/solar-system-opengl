#include <stdio.h>
#include <GL/glut.h>

void display(void);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Teszt");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.5f);
        glVertex3f(0.0f, 0.0f, -0.5f);
    glEnd();

    glutSwapBuffers();
    glutKeyboardFunc(keyboard);

}

void keyboard(unsigned char key, int x, int y){
    if(key == 27)
        exit(0);
    if(key == 'f')
        glutFullScreen();
}
