#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "scene.h"
#include "callbacks.h"
#include "file.h"


void init_scene(Scene* scene){
    load_model(&(scene->geoid), "data/models/planet.obj");
    load_model(&(scene->saturn_ring), "data/models/saturn_ring.obj");

    init_textures(scene);
    init_material(scene);
    init_planet(scene);

    scene->drawOrbit = 1;
    scene->animate = 1;
    scene->animation_speed = 1.0;
    scene->drawManual = 0;
    scene->planetNames = 0;
}

void init_planet(Scene* scene){

    FILE* fp = fopen("data/planet_data.csv", "r");
        if(fp == 0){
            printf("Could not open file");
            exit(1);
        }

    readFromFile(scene->planets, fp);

}

void init_textures(Scene* scene){
    scene->sun_texture_id = load_texture("data/textures/2k_sun.jpg");
    scene->mercury_texture_id = load_texture("data/textures/2k_mercury.jpg");
    scene->venus_texture_id = load_texture("data/textures/2k_venus.jpg");
    scene->earth_texture_id = load_texture("data/textures/2k_earth.jpg");
    scene->mars_texture_id = load_texture("data/textures/2k_mars.jpg");
    scene->jupiter_texture_id = load_texture("data/textures/2k_jupiter.jpg");
    scene->saturn_texture_id = load_texture("data/textures/2k_saturn.jpg");
    scene->uranus_texture_id = load_texture("data/textures/2k_uranus.jpg");
    scene->neptune_texture_id = load_texture("data/textures/2k_neptune.jpg");
    scene->pluto_texture_id = load_texture("data/textures/2k_pluto.jpg");
    scene->moon_texture_id = load_texture("data/textures/2k_moon.jpg");
    scene->skybox_texture_id = load_texture("data/textures/skybox.png");
}

void init_material(Scene* scene){
    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 100.0;

    scene->ambient.red = 0.4;
    scene->ambient.green = 0.4;
    scene->ambient.blue = 0.4;
}
void set_lighting(Scene* scene){

    float ambient_light[] = { scene->ambient.red, scene->ambient.green, scene->ambient.blue, 1.0f};
    float diffuse_light[] = { 0.8f, 0.8f, 0.8f, 1.0f};
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f};
    float position[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material){

    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

draw_manual(){
    glMatrixMode(GL_PROJECTION);

    glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, w, h, 0);
    	   glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPushMatrix();
        glLoadIdentity();
        renderBitmapString(5, 25, 0, GLUT_BITMAP_HELVETICA_18, "USER MANUAL");
        renderBitmapString(5, 75, 0, GLUT_BITMAP_HELVETICA_18, "Use WASD to move around");
        renderBitmapString(5, 100, 0, GLUT_BITMAP_HELVETICA_18, "Use SPACE and C to fly up and down");
        renderBitmapString(5, 125, 0, GLUT_BITMAP_HELVETICA_18, "The direction of the camera can be changed with the mouse while the left mouse button is being held down");
        renderBitmapString(5, 150, 0, GLUT_BITMAP_HELVETICA_18, "Use B to start/stop the animation");
        renderBitmapString(5, 175, 0, GLUT_BITMAP_HELVETICA_18, "Use N to draw the orbits");
        renderBitmapString(5, 200, 0, GLUT_BITMAP_HELVETICA_18, "Use +/- to adjust the intensity of ambient light");
        renderBitmapString(5, 225, 0, GLUT_BITMAP_HELVETICA_18, "Press RMB to access the Pop-up menu");
        renderBitmapString(5, 250, 0, GLUT_BITMAP_HELVETICA_18, "Press ESC to exit the simulation");
        renderBitmapString(5, 300, 0, GLUT_BITMAP_HELVETICA_18, "PRESS F1 TO CLOSE THE USER MANUAL");
        renderBitmapString(5, 350, 0, GLUT_BITMAP_HELVETICA_18, "Marcell Leleszi 2021");
	glPopMatrix();

    glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);


}


void draw_planets(Scene* scene){
    set_material(&(scene->material));
    set_lighting(scene);
    glPushMatrix();

    // Skybox
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->skybox_texture_id);
        glScalef(50, 50, 50);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Sun
    glPushMatrix();
        if(scene->planetNames) renderBitmapString(0.2 * scene->planets[0].radius, 0.0f, scene->planets[0].radius, GLUT_BITMAP_HELVETICA_12  ,"Sun");
        glBindTexture(GL_TEXTURE_2D, scene->sun_texture_id);
        glScalef(scene->planets[0].radius, scene->planets[0].radius, scene->planets[0].radius);
        glRotatef(scene->planets[0].rotation, 0.0f, 0.0f, 1.0f);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Mercury
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(scene->planets[1].distance);
        glRotatef(scene->planets[1].orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(scene->planets[1].distance, 0.0f, 0.0f);
        if(scene->planetNames) renderBitmapString(0.2 * scene->planets[1].radius, 0.0f, scene->planets[1].radius, GLUT_BITMAP_HELVETICA_12  ,"Mercury");
        glRotatef(scene->planets[1].axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(scene->planets[1].rotation, 0.0f, 0.0f, 1.0f);
        glScalef(scene->planets[1].radius, scene->planets[1].radius, scene->planets[1].radius);
        glBindTexture(GL_TEXTURE_2D, scene->mercury_texture_id);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Venus
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(scene->planets[2].distance);
        glRotatef(scene->planets[2].orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(scene->planets[2].distance, 0.0f, 0.0f);
        if(scene->planetNames) renderBitmapString(0.2 * scene->planets[2].radius, 0.0f, scene->planets[2].radius, GLUT_BITMAP_HELVETICA_12  ,"Venus");
        glRotatef(scene->planets[2].axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(scene->planets[2].rotation, 0.0f, 0.0f, 1.0f);
        glScalef(scene->planets[2].radius, scene->planets[2].radius, scene->planets[2].radius);
        glBindTexture(GL_TEXTURE_2D, scene->venus_texture_id);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Earth
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(scene->planets[3].distance);
        glRotatef(scene->planets[3].orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(scene->planets[3].distance, 0.0f, 0.0f);
        if(scene->planetNames) renderBitmapString(0.2 * scene->planets[3].radius, 0.0f, scene->planets[3].radius, GLUT_BITMAP_HELVETICA_12  ,"Earth");
        glRotatef(scene->planets[3].axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(scene->planets[3].rotation, 0.0f, 0.0f, 1.0f);
        glScalef(scene->planets[3].radius, scene->planets[3].radius, scene->planets[3].radius);
        glBindTexture(GL_TEXTURE_2D, scene->earth_texture_id);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Moon
    glPushMatrix();
        glRotatef(scene->planets[3].orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(scene->planets[3].distance, 0.0f, 0.0f);
        glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
        if(scene->drawOrbit) draw_orbit_trail(scene->planets[10].distance);
        glRotatef(scene->planets[10].orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(scene->planets[10].distance, 0.0f, 0.0f);
        glRotatef(scene->planets[10].rotation, 0.0f, 0.0f, 1.0f);
        glScalef(scene->planets[10].radius, scene->planets[10].radius, scene->planets[10].radius);
        glBindTexture(GL_TEXTURE_2D, scene->moon_texture_id);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Mars
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(scene->planets[4].distance);
        glRotatef(scene->planets[4].orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(scene->planets[4].distance, 0.0f, 0.0f);
        if(scene->planetNames) renderBitmapString(0.2 * scene->planets[4].radius, 0.0f, scene->planets[4].radius, GLUT_BITMAP_HELVETICA_12  ,"Mars");
        glRotatef(scene->planets[4].axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(scene->planets[4].rotation, 0.0f, 0.0f, 1.0f);
        glScalef(scene->planets[4].radius, scene->planets[4].radius, scene->planets[4].radius);
        glBindTexture(GL_TEXTURE_2D, scene->mars_texture_id);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Jupiter
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(scene->planets[5].distance);
        glRotatef(scene->planets[5].orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(scene->planets[5].distance, 0.0f, 0.0f);
        if(scene->planetNames) renderBitmapString(0.2 * scene->planets[5].radius, 0.0f, scene->planets[5].radius, GLUT_BITMAP_HELVETICA_12  ,"Jupiter");
        glRotatef(scene->planets[5].axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(scene->planets[5].rotation, 0.0f, 0.0f, 1.0f);
        glScalef(scene->planets[5].radius, scene->planets[5].radius, scene->planets[5].radius);
        glBindTexture(GL_TEXTURE_2D, scene->jupiter_texture_id);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Saturn
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(scene->planets[6].distance);
        glRotatef(scene->planets[6].orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(scene->planets[6].distance, 0.0f, 0.0f);
        if(scene->planetNames) renderBitmapString(0.2 * scene->planets[6].radius, 0.0f, scene->planets[6].radius, GLUT_BITMAP_HELVETICA_12  ,"Saturn");
        glRotatef(scene->planets[6].axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(scene->planets[6].rotation, 0.0f, 0.0f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, scene->saturn_texture_id);
        draw_model(&(scene->saturn_ring));
        glScalef(scene->planets[6].radius, scene->planets[6].radius, scene->planets[6].radius);
        draw_model(&(scene->geoid));

    glPopMatrix();

    // Uranus
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(scene->planets[7].distance);
        glRotatef(scene->planets[7].orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(scene->planets[7].distance, 0.0f, 0.0f);
        if(scene->planetNames) renderBitmapString(0.2 * scene->planets[7].radius, 0.0f, scene->planets[7].radius, GLUT_BITMAP_HELVETICA_12  ,"Uranus");
        glRotatef(scene->planets[7].axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(scene->planets[7].rotation, 0.0f, 0.0f, 1.0f);
        glScalef(scene->planets[7].radius, scene->planets[7].radius, scene->planets[7].radius);
        glBindTexture(GL_TEXTURE_2D, scene->uranus_texture_id);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Neptune
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(scene->planets[8].distance);
        glRotatef(scene->planets[8].orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(scene->planets[8].distance, 0.0f, 0.0f);
        if(scene->planetNames) renderBitmapString(0.2 * scene->planets[8].radius, 0.0f, scene->planets[8].radius, GLUT_BITMAP_HELVETICA_12  ,"Neptune");
        glRotatef(scene->planets[8].axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(scene->planets[8].rotation, 0.0f, 0.0f, 1.0f);
        glScalef(scene->planets[8].radius, scene->planets[8].radius, scene->planets[8].radius);
        glBindTexture(GL_TEXTURE_2D, scene->neptune_texture_id);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Pluto
    glPushMatrix();
        glRotatef(17.0f, 0.0f, 1.0f, 0.0f);
        if(scene->drawOrbit) draw_orbit_trail(scene->planets[9].distance);
        glRotatef(scene->planets[9].orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(scene->planets[9].distance, 0.0f, 0.0f);
        if(scene->planetNames) renderBitmapString(0.2 * scene->planets[9].radius, 0.0f, scene->planets[9].radius, GLUT_BITMAP_HELVETICA_12  ,"Pluto");
        glRotatef(scene->planets[9].axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(scene->planets[9].rotation, 0.0f, 0.0f, 1.0f);
        glScalef(scene->planets[9].radius, scene->planets[9].radius, scene->planets[9].radius);
        glBindTexture(GL_TEXTURE_2D, scene->pluto_texture_id);
        draw_model(&(scene->geoid));
    glPopMatrix();


    glPopMatrix();
}

void draw_orbit_trail(float radius){
    glBindTexture(GL_TEXTURE_2D, NULL);
    glBegin(GL_LINE_STRIP);
        float angle;
        for(angle = 0.0f; angle < 2 * M_PI; angle += 0.05f){
            glVertex3f(sin(angle) * radius,cos(angle) * radius, 0.0f);
        }
        glVertex3f(0.0f, radius, 0.0f);
    glEnd();
}

void increment_orbit(Scene* scene, double time){
    int i;
    for(i = 0; i < 11; i++)
        scene->planets[i].orbit += scene->planets[i].orbit_speed * scene->animation_speed * time;
}

void increment_rotation(Scene* scene, double time){
    int i;
    for(i = 0; i < 11; i++)
        scene->planets[i].rotation += scene->planets[i].rotation_speed * scene->animation_speed * time;
}

void renderBitmapString(float x, float y, float z, void *font, char *string) {
	char *c;
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, NULL);
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
    glEnable(GL_LIGHTING);
}
