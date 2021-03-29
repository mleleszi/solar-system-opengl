#ifndef POPUPMENU_H
#define POPUPMENU_H

#include "scene.h"
#include "callbacks.h"

#define ON 1
#define OFF 0

int animation_menu, animation_speed_menu, orbit_menu, audio_menu, name_menu, main_menu;
int menu_flag;

// create pop up menus
void create_popup_menus();

// menu status
void process_menu_status(int status, int x, int y);

// main menu
void process_main_menu(int option);

// animation menu
void process_animation_menu(int option);

// animation speed menu
void process_animation_speed_menu(int option);

// orbit trail menu
void process_orbit_menu(int option);

// audio menu
void process_audio_menu(int option);

// planet names menus
void process_name_menu(int option);




#endif
