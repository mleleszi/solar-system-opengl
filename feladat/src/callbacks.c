#include "callbacks.h"
#include "scene.h"

#define VIEWPORT_RATIO (16.0 / 9.0)
#define VIEWPORT_ASPECT 50.0

struct {
    int x;
    int y;
} mouse_position;



void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        set_view(&camera);
        draw_planets(&scene);
    glPopMatrix();


    if(scene.drawManual) draw_manual();
    else calc_fps();

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height){

    w = width;
    h = height;
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
    case 'b':
        if(scene.animate) scene.animate = 0;
        else scene.animate = 1;
        break;
    case 'n':
        if(scene.drawOrbit) scene.drawOrbit = 0;
        else scene.drawOrbit = 1;
        break;

    case 43: // +
        if(scene.ambient.red <= 0.95f){
            scene.ambient.red += 0.05;
            scene.ambient.green += 0.05;
            scene.ambient.blue += 0.05;
        }
        break;
    case 45: // -
        if(scene.ambient.red >= 0.05f){
            scene.ambient.red -= 0.05;
            scene.ambient.green -= 0.05;
            scene.ambient.blue -= 0.05;
        }
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

void specialFunc(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		if (scene.drawManual) {
			scene.drawManual = 0;
		}else {
			scene.drawManual = 1;
		}
        break;
	}

}


void calc_fps(){
    frame++;
    glBindTexture(NULL, NULL);
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s,"FPS:%4.2f",
			frame*1000.0/(time-timebase));
		timebase = time;
		frame = 0;
    }
    glMatrixMode(GL_PROJECTION);

    glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, w, h, 0);
	    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPushMatrix();
	    glLoadIdentity();
	    renderBitmapString(5,30,0,GLUT_BITMAP_HELVETICA_18,s);
        renderBitmapString(5,55,0,GLUT_BITMAP_HELVETICA_18,"PRESS F1 TO OPEN USER MANUAL");
	glPopMatrix();

    glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
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
    if(scene.animate){
        increment_orbit(&scene, elapsed_time);
        increment_rotation(&scene, elapsed_time);
    }

    glutPostRedisplay();
}
