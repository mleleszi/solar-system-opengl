#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "scene.h"
#include "callbacks.h"



void init_scene(Scene* scene){
    load_model(&(scene->geoid), "data/models/geoid.obj");

    scene->sun_texture_id = load_texture("data/textures/sun.jpg");
    scene->mercury_texture_id = load_texture("data/textures/moon.png");

    scene->mercury_texture_id = load_texture("data/textures/moon.png");
    scene->venus_texture_id = load_texture("data/textures/moon.png");
    scene->earth_texture_id = load_texture("data/textures/earth.png");
    scene->mars_texture_id = load_texture("data/textures/moon.png");
    scene->jupiter_texture_id = load_texture("data/textures/moon.png");
    scene->saturn_texture_id = load_texture("data/textures/moon.png");
    scene->uranus_texture_id = load_texture("data/textures/moon.png");
    scene->neptune_texture_id = load_texture("data/textures/moon.png");
    scene->moon_texture_id = load_texture("data/textures/moon.png");

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

Planet sun = {6.0f/10, 0.0f/10, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Planet mercury = {0.4f/10, 8.0f/10, 40.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Planet venus = {0.95f/10, 16.0f/10, 30.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Planet earth = {1.0f/10, 24.0f/10, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Planet mars = {0.5f/10, 30.0f/10, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Planet jupiter = {3.0f/10, 38.0f/10, 8.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Planet saturn = {2.5f/10, 50.0f/10, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Planet uranus = {1.9f/10, 60.0f/10, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Planet neptune = {1.8f/10, 70.0f/10, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Planet moon = {0.3f/10, 2.0f/10, 40.0f, 0.0f, 0.0f, 0.0f, 0.0f};

void draw_planets(Scene* scene){
    set_material(&(scene->material));
    set_lighting(scene);
    glPushMatrix();

    // Skybox
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->skybox_texture_id);
        glScalef(30, 30, 30);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Sun
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->sun_texture_id);
        glScalef(sun.radius, sun.radius, sun.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Mercury
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->mercury_texture_id);
        if(scene->drawOrbit) draw_orbit_trail(mercury.distance);
        glRotatef(mercury.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(mercury.distance, 0.0f, 0.0f);
        glScalef(mercury.radius, mercury.radius, mercury.radius);
        draw_model(&(scene->geoid));

    glPopMatrix();

    // Venus
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->venus_texture_id);
        if(scene->drawOrbit) draw_orbit_trail(venus.distance);
        glRotatef(venus.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(venus.distance, 0.0f, 0.0f);
        glScalef(venus.radius, venus.radius, venus.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Earth & Moon
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->earth_texture_id);
        if(scene->drawOrbit) draw_orbit_trail(earth.distance);
        glRotatef(earth.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(earth.distance, 0.0f, 0.0f);
        //glRotatef(earth.orbit, 0.0f, 0.0f, 1.0f); forgas
        glutSolidSphere(earth.radius, 15, 15);

        // Moon
        glBindTexture(GL_TEXTURE_2D, scene->moon_texture_id);
        if(scene->drawOrbit) draw_orbit_trail(moon.distance);
        glRotatef(moon.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(moon.distance, 0.0f, 0.0f);
        glScalef(moon.radius, moon.radius, moon.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Mars
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->mars_texture_id);
        if(scene->drawOrbit) draw_orbit_trail(mars.distance);
        glRotatef(mars.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(mars.distance, 0.0f, 0.0f);
        glScalef(mars.radius, mars.radius, mars.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Jupiter
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->jupiter_texture_id);
        if(scene->drawOrbit) draw_orbit_trail(jupiter.distance);
        glRotatef(jupiter.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(jupiter.distance, 0.0f, 0.0f);
        glScalef(jupiter.radius, jupiter.radius, jupiter.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Saturn
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->saturn_texture_id);
        if(scene->drawOrbit) draw_orbit_trail(saturn.distance);
        glRotatef(saturn.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(saturn.distance, 0.0f, 0.0f);
        glScalef(saturn.radius, saturn.radius, saturn.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Uranus
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->uranus_texture_id);
        if(scene->drawOrbit) draw_orbit_trail(uranus.distance);
        glRotatef(uranus.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(uranus.distance, 0.0f, 0.0f);
        glScalef(uranus.radius, uranus.radius, uranus.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    // Neptune
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->neptune_texture_id);
        if(scene->drawOrbit) draw_orbit_trail(neptune.distance);
        glRotatef(neptune.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(neptune.distance, 0.0f, 0.0f);
        glScalef(neptune.radius, neptune.radius, neptune.radius);
        draw_model(&(scene->geoid));
    glPopMatrix();

    glPopMatrix();
}




void draw_orbit_trail(float radius){
    glBegin(GL_LINE_STRIP);
        float angle;
        for(angle = 0.0f; angle < 2 * M_PI; angle += 0.05f){
            glVertex3f(sin(angle) * radius,cos(angle) * radius, 0.0f);
        }
        glVertex3f(0.0f, radius, 0.0f);
    glEnd();
}



void increment_orbit(double time){
    mercury.orbit += mercury.orbit_speed * time;
    venus.orbit += venus.orbit_speed * time;
    earth.orbit += earth.orbit_speed * time;
    mars.orbit += mars.orbit_speed * time;
    jupiter.orbit += jupiter.orbit_speed * time;
    saturn.orbit += saturn.orbit_speed * time;
    uranus.orbit += uranus.orbit_speed * time;
    neptune.orbit += neptune.orbit_speed * time;
    moon.orbit += moon.orbit_speed * time;
}
