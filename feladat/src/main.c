#include <GL/glut.h>
#include <stdio.h>
#include <windows.h>
#include <MMsystem.h>
#include "callbacks.h"
#include "popupmenu.h"
#include "init.h"

// register callbacks
void set_callbacks(){
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutSpecialFunc(specialFunc);
    glutIdleFunc(idle);
}


int main(int argc, char* argv[]){


    int window;

    glutInit(&argc, argv);

    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    window = glutCreateWindow("Solar System");
    glutSetWindow(window);

    init_opengl();
    init_scene(&scene);
    init_camera(&camera);
    set_callbacks();

    create_popup_menus();

    PlaySound(TEXT("data/audio/notime.wav"), NULL, SND_ASYNC);
    glutMainLoop();

    return 0;
}
