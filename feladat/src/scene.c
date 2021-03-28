#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "scene.h"
#include "callbacks.h"



void init_scene(Scene* scene){
    load_model(&(scene->geoid), "data/models/planet.obj");// geoid - jo fps, geoid2 - jo texturazas planet- joooo

    scene->sun_texture_id = load_texture("data/textures/2k_sun.jpg");


    scene->mercury_texture_id = load_texture("data/textures/2k_mercury.jpg");
    scene->venus_texture_id = load_texture("data/textures/2k_venus.jpg");
    scene->earth_texture_id = load_texture("data/textures/2k_earth.jpg");
    scene->mars_texture_id = load_texture("data/textures/2k_mars.jpg");
    scene->jupiter_texture_id = load_texture("data/textures/2k_jupiter.jpg");
    scene->saturn_texture_id = load_texture("data/textures/2k_saturn.jpg");
    scene->uranus_texture_id = load_texture("data/textures/2k_uranus.jpg");
    scene->neptune_texture_id = load_texture("data/textures/2k_neptune.jpg");
    //scene->pluto_texture_id = load_texture("data/textures/2k_neptune.jpg");
    scene->moon_texture_id = load_texture("data/textures/2k_moon.jpg");

    scene->skybox_texture_id = load_texture("data/textures/skybox.png");


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

    scene->drawOrbit = 1;
    scene->animate = 1;
    scene->animation_speed = 1.0;
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


Planet sun = {6.0f/10, 0.0f/10, 0.0f, 0.0f, 20.0f, 30.0f, 0.0f};
Planet mercury = {0.4f/10, 8.0f/10, 40.0f, 0.0f, 20.0f, 0.0f, 0.0f};
Planet venus = {0.95f/10, 16.0f/10, 30.0f, 0.0f, 10.0f, 0.0f, -177.3f};
Planet earth = {1.0f/10, 24.0f/10, 20.0f, 0.0f, 100.0f, 0.0f, -23.4f};
Planet mars = {0.65f/10, 30.0f/10, 10.0f, 0.0f, 100.0f, 0.0f, -25.2f};
Planet jupiter = {3.0f/10, 38.0f/10, 8.0f, 0.0f, 400.0f, 0.0f, -3.1f};
Planet saturn = {2.5f/10, 50.0f/10, 6.0f, 0.0f, 400.0f, 0.0f, -26.7f};
Planet uranus = {1.9f/10, 60.0f/10, 4.0f, 0.0f, 600.0f, 0.0f, -97.8f};
Planet neptune = {1.8f/10, 70.0f/10, 2.0f, 0.0f, 550.0f, 0.0f, -28.3f};
Planet pluto = {0.3f/10, 80.0f/10, 1.5f, 0.0f, 550.0f, 0.0f, -120.f};
Planet moon = {0.3f/10, 2.0f/10, 40.0f, 0.0f, 16.0f, 0.0f, 0.0f};

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
        glBindTexture(GL_TEXTURE_2D, scene->sun_texture_id);
        glScalef(sun.radius, sun.radius, sun.radius);
        glRotatef(sun.rotation, 0.0f, 0.0f, 1.0f);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Mercury
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(mercury.distance);
        glBindTexture(GL_TEXTURE_2D, scene->mercury_texture_id);
        glRotatef(mercury.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(mercury.distance, 0.0f, 0.0f);
        glRotatef(mercury.axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(mercury.rotation, 0.0f, 0.0f, 1.0f);
        glScalef(mercury.radius, mercury.radius, mercury.radius);
        draw_model(&(scene->geoid));

    glPopMatrix();

    // Venus
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(venus.distance);
        glBindTexture(GL_TEXTURE_2D, scene->venus_texture_id);
        glRotatef(venus.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(venus.distance, 0.0f, 0.0f);
        glRotatef(venus.axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(venus.rotation, 0.0f, 0.0f, 1.0f);
        glScalef(venus.radius, venus.radius, venus.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Earth
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(earth.distance);
        glBindTexture(GL_TEXTURE_2D, scene->earth_texture_id);
        glRotatef(earth.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(earth.distance, 0.0f, 0.0f);
        glRotatef(earth.axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(earth.rotation, 0.0f, 0.0f, 1.0f);
        glScalef(earth.radius, earth.radius, earth.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Moon
    glPushMatrix();
        glRotatef(earth.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(earth.distance, 0.0f, 0.0f);
        glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
        if(scene->drawOrbit) draw_orbit_trail(moon.distance);
        glBindTexture(GL_TEXTURE_2D, scene->moon_texture_id);
        glRotatef(moon.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(moon.distance, 0.0f, 0.0f);
        glRotatef(moon.rotation, 0.0f, 0.0f, 1.0f);
        glScalef(moon.radius, moon.radius, moon.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Mars
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(mars.distance);
        glBindTexture(GL_TEXTURE_2D, scene->mars_texture_id);
        glRotatef(mars.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(mars.distance, 0.0f, 0.0f);
        glRotatef(mars.axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(mars.rotation, 0.0f, 0.0f, 1.0f);
        glScalef(mars.radius, mars.radius, mars.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Jupiter
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(jupiter.distance);
        glBindTexture(GL_TEXTURE_2D, scene->jupiter_texture_id);
        glRotatef(jupiter.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(jupiter.distance, 0.0f, 0.0f);
        glRotatef(jupiter.axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(jupiter.rotation, 0.0f, 0.0f, 1.0f);
        glScalef(jupiter.radius, jupiter.radius, jupiter.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Saturn
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(saturn.distance);
        glBindTexture(GL_TEXTURE_2D, scene->saturn_texture_id);
        glRotatef(saturn.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(saturn.distance, 0.0f, 0.0f);
        glRotatef(saturn.axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(saturn.rotation, 0.0f, 0.0f, 1.0f);
        glScalef(saturn.radius, saturn.radius, saturn.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Uranus
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(uranus.distance);
        glBindTexture(GL_TEXTURE_2D, scene->uranus_texture_id);
        glRotatef(uranus.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(uranus.distance, 0.0f, 0.0f);
        glRotatef(uranus.axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(uranus.rotation, 0.0f, 0.0f, 1.0f);
        glScalef(uranus.radius, uranus.radius, uranus.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Neptune
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(neptune.distance);
        glBindTexture(GL_TEXTURE_2D, scene->neptune_texture_id);
        glRotatef(neptune.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(neptune.distance, 0.0f, 0.0f);
        glRotatef(neptune.axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(uranus.rotation, 0.0f, 0.0f, 1.0f);
        glScalef(neptune.radius, neptune.radius, neptune.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Pluto

    /*
    glPushMatrix();
        if(scene->drawOrbit) draw_orbit_trail(pluto.distance);
        glRotatef(100.0f, 0.0f, 1.0f, 0.0f);
        glBindTexture(GL_TEXTURE_2D, scene->pluto_texture_id);
        glRotatef(pluto.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(pluto.distance, 0.0f, 0.0f);
        glRotatef(pluto.axis_tilt, 0.0f, 1.0f, 0.0f);
        glRotatef(pluto.rotation, 0.0f, 0.0f, 1.0f);
        glScalef(neptune.radius, neptune.radius, neptune.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();
    */

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
    mercury.orbit += mercury.orbit_speed * scene->animation_speed * time;
    venus.orbit += venus.orbit_speed * scene->animation_speed * time;
    earth.orbit += earth.orbit_speed * scene->animation_speed * time;
    mars.orbit += mars.orbit_speed * scene->animation_speed * time;
    jupiter.orbit += jupiter.orbit_speed * scene->animation_speed * time;
    saturn.orbit += saturn.orbit_speed * scene->animation_speed * time;
    uranus.orbit += uranus.orbit_speed * scene->animation_speed * time;
    neptune.orbit += neptune.orbit_speed * scene->animation_speed * time;
    pluto.orbit += pluto.orbit_speed * scene->animation_speed * time;
    moon.orbit += moon.orbit_speed * scene->animation_speed * time;
}

void increment_rotation(Scene* scene, double time){
    sun.rotation += sun.rotation_speed * scene->animation_speed * time;
    mercury.rotation += mercury.rotation_speed * scene->animation_speed * time;
    venus.rotation += venus.rotation_speed * scene->animation_speed * time;
    earth.rotation += earth.rotation_speed * scene->animation_speed * time;
    mars.rotation += mars.rotation_speed * scene->animation_speed * time;
    jupiter.rotation += jupiter.rotation_speed * scene->animation_speed * time;
    saturn.rotation += saturn.rotation_speed * scene->animation_speed * time;
    uranus.rotation += uranus.rotation_speed * scene->animation_speed * time;
    neptune.rotation += neptune.rotation_speed * scene->animation_speed * time;
    pluto.rotation += pluto.rotation_speed * scene->animation_speed * time;
    moon.rotation += moon.rotation_speed * scene->animation_speed * time;
}

void renderBitmapString(float x, float y, float z, void *font, char *string) {
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}
