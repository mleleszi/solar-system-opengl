#include <GL/glut.h>
#include "popupmenu.h"
#include "scene.h"


menu_flag = 0;
void process_menu_status(int status, int x, int y) {
	if (status == GLUT_MENU_IN_USE) menu_flag = 1;
	else menu_flag = 0;
}

void process_main_menu(int option){

}

void process_animation_menu(int option){
    switch(option){
        case ON: scene.animate = 1; break;
        case OFF: scene.animate = 0; break;
    }
}

void process_orbit_menu(int option){
    switch(option){
        case ON: scene.drawOrbit = 1; break;
        case OFF: scene.drawOrbit = 0; break;
    }
}

void create_popup_menus(){

    animation_menu = glutCreateMenu(process_animation_menu);
    glutAddMenuEntry("Turn On", ON);
    glutAddMenuEntry("Turn Off", OFF);

    orbit_menu = glutCreateMenu(process_orbit_menu);
    glutAddMenuEntry("Turn On", ON);
    glutAddMenuEntry("Turn Off", OFF);

    main_menu = glutCreateMenu(process_main_menu);

    glutAddSubMenu("Animation", animation_menu);
    glutAddSubMenu("Orbit Trails", orbit_menu);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMenuStatusFunc(process_menu_status);
}
