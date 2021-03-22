#include <GL/glut.h>
#include <math.h>
#include <stdio.h>



float red = 1.0f, green = 1.0f, blue = 1.0f;

//  angle of rotation of the camera direction around the y axis
float angle = 0.0f;
// actual vector representing the the camera's direction
float lx = 0.0f, lz = -1.0f;
// position of the camera
float x = 0.0f, z = 5.0f;

float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

void computePos(float deltaMove){
    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle){
    angle += deltaAngle;
    lx = sin(angle);
    lz = -cos(angle);
}

void render(){

    if(deltaMove) computePos(deltaMove);
    //if(deltaAngle) computeDir(deltaAngle);
    printf("%f ", angle);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(  x, 1.0f, z,
                x + lx, 1.0f,  z + lz,
                0.0f, 1.0f,  0.0f);


    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();

    glPushMatrix();
        glTranslatef(0.0, 2.0, 0.0);
        glutSolidSphere(1.0, 50.0, 50.0);
    glPopMatrix();


    glutSwapBuffers();
}

void reshape(int w, int h){

    if(h == 0) h = 1;

    float ratio = 1.0 * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
    int mod;
    switch(key){
        case 27:
            exit(0);
            break;
        case 'r':
            mod = glutGetModifiers();
            if(mod == GLUT_ACTIVE_ALT) red = 0.0;
            else red = 1.0;
    }
}

void keyboard_special(int key, int x, int y){


    switch(key){
        case GLUT_KEY_LEFT:
            deltaMove -= 0.5f;
            break;
        case GLUT_KEY_RIGHT:
            deltaMove += 0.5f;
            break;
        case GLUT_KEY_UP:
            deltaMove = 0.5f;
            break;
        case GLUT_KEY_DOWN:
            deltaMove = -0.5f;
            break;

    }
}

void keyboard_special_up(int key, int x, int y){

    switch(key){
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN: deltaMove = 0; break;

    }
}

void mouseButton(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) {

		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else  {
			xOrigin = x;
		}
	}
}

void mouseMove(int x, int y) {

	if (xOrigin >= 0) {

		deltaAngle = (x - xOrigin) * 0.001f;
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}


int main(int argc, char** argv){

    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Solar System");

    // register callbacks
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutIdleFunc(render);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboard_special);

    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(keyboard_special_up);

    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);

    // enter GLUT event processing cycle
    glutMainLoop();


    return 1;

}
