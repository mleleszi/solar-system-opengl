#include <GL/glut.h>
#include <windows.h>
#include <MMsystem.h>
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
        case 1: scene.animate = 1; break;
        case 0: scene.animate = 0; break;
    }
}

void process_animation_speed_menu(int option){
	switch(option){
		case 0: scene.animation_speed = 0.2; break;
		case 1: scene.animation_speed = 0.5; break;
		case 2: scene.animation_speed = 1.0; break;
		case 3: scene.animation_speed = 2.0; break;
		case 4: scene.animation_speed = 5.0; break;
	}
}

void process_orbit_menu(int option){
    switch(option){
        case 1: scene.drawOrbit = 1; break;
        case 0: scene.drawOrbit = 0; break;
    }
}

void process_audio_menu(int option){
	switch(option){
		case 0: PlaySound(TEXT("data/audio/notime.wav"), NULL, SND_ASYNC); break;
		case 1: PlaySound(TEXT("data/audio/stay.wav"), NULL, SND_ASYNC); break;
		case 2: PlaySound(NULL, NULL, SND_ASYNC); break;
	}
}

void process_name_menu(int option){
	switch(option){
		case 1: scene.planetNames = 1; break;
		case 0: scene.planetNames = 0; break;
	}
}

void create_popup_menus(){

    animation_menu = glutCreateMenu(process_animation_menu);
    glutAddMenuEntry("Turn On", 1);
    glutAddMenuEntry("Turn Off", 0);

	animation_speed_menu = glutCreateMenu(process_animation_speed_menu);
	glutAddMenuEntry("0.2x", 0);
	glutAddMenuEntry("0.5x", 1);
    glutAddMenuEntry("1x", 2);
	glutAddMenuEntry("2x", 3);
	glutAddMenuEntry("5x", 4);


    orbit_menu = glutCreateMenu(process_orbit_menu);
    glutAddMenuEntry("Turn On", 1);
    glutAddMenuEntry("Turn Off", 0);

	audio_menu = glutCreateMenu(process_audio_menu);
    glutAddMenuEntry("Hans Zimmer - No Time For Caution", 0);
    glutAddMenuEntry("Hans Zimmer - S.T.A.Y", 1);
	glutAddMenuEntry("Turn Off", 2);

	name_menu = glutCreateMenu(process_name_menu);
    glutAddMenuEntry("Turn On", 1);
    glutAddMenuEntry("Turn Off", 0);


    main_menu = glutCreateMenu(process_main_menu);

    glutAddSubMenu("Animation", animation_menu);
	glutAddSubMenu("Animation Speed", animation_speed_menu);
    glutAddSubMenu("Orbit Trails", orbit_menu);
	glutAddSubMenu("Audio", audio_menu);
	glutAddSubMenu("Planet Names", name_menu);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMenuStatusFunc(process_menu_status);
}
