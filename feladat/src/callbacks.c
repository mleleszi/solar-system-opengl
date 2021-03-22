#include "callbacks.h"

#define VIEWPORT_RATIO (16.0 / 9.0)
#define VIEWPORT_ASPECT 50.0

struct {
    int x;
    int y;
} mouse_position;

float earth_rotation = 0.0f;
float moon_rotation = 0.0f;

void update(double time){
    earth_rotation += 20.0 * time;
    moon_rotation += 60.0 * time;
}

void display(){



    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);




    glPushMatrix();

        set_view(&camera);

        // sun
        glColor3f(1.0f, 1.0f, 0.0);
        glutSolidSphere(3.0f, 15, 15);


        // earth
        glColor3f(0.0f, 1.0f, 0.0f);
        glRotatef(earth_rotation, 0.0f, 0.0f, 1.0f);
        glTranslatef(10.0f, 0.0f, 0.0f);
        //glRotatef(rotation, 0.0f, 0.0f, 1.0f); forgas?
        glutSolidSphere(1.0f, 15, 15);

        // motion
        glColor3f(0.0f, 0.0f, 1.0f);
        glRotatef(moon_rotation, 0.0f, 0.0f, 1.0f);
        glTranslatef(1.5f, 0.0f, 0.0f);
        glutSolidSphere(0.3f, 15, 15);


    glPopMatrix();


    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height){
    if (height == 0)
		height = 1;

	float ratio =  width * 1.0 / height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y){
    mouse_position.x = x;
    mouse_position.y = y;
}

void motion(int x, int y){
    rotate_camera(&camera, mouse_position.x - x, mouse_position.y - y);
    mouse_position.x = x;
    mouse_position.y = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){

    switch (key) {
    case 'w':
        set_camera_speed(&camera, 1);
        break;
    case 's':
        set_camera_speed(&camera, -1);
        break;
    case 'a':
        set_camera_side_speed(&camera, 1);
        break;
    case 'd':
        set_camera_side_speed(&camera, -1);
        break;
    case 32:
        set_camera_vertical_speed(&camera, 1);
        break;
    case 'c':
        set_camera_vertical_speed(&camera, -1);
        break;
    case 27:
        exit(0);
        break;
    }

    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
    case 's':
        set_camera_speed(&camera, 0.0);
        break;
    case 'a':
    case 'd':
        set_camera_side_speed(&camera, 0.0);
        break;
    case 32:
    case 'c':
        set_camera_vertical_speed(&camera, 0.0);
        break;
    }

    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;

    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    update_camera(&camera, elapsed_time);
    update(elapsed_time);

    glutPostRedisplay();
}
