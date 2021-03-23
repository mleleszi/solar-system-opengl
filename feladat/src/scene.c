#include <GL/glut.h>
#include <stdio.h>
#include "scene.h"
#include "callbacks.h"


void init_scene(Scene* scene){

}

void draw_scene(Scene* scene){

}

Planet sun = {3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Planet earth = {1.0f, 10.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Planet moon = {0.3f, 1.5f, 60.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Planet mars = {0.8f, 15.0f, 15.0f, 0.0f, 0.0f, 0.0f, 0.0f};

void draw_planets(){

    // Sun
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f);
        glutSolidSphere(sun.radius, 15, 15);
    glPopMatrix();

    // Earth & Moon
    glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);
        glRotatef(earth.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(earth.distance, 0.0f, 0.0f);
        //glRotatef(rotation, 0.0f, 0.0f, 1.0f); forgas?
        glutSolidSphere(earth.radius, 15, 15);

        // Moon
        glColor3f(0.0f, 0.0f, 1.0f);
        glRotatef(moon.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(moon.distance, 0.0f, 0.0f);
        glutSolidSphere(moon.radius, 15, 15);
    glPopMatrix();

    // Mars
    glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.5f);
        glRotatef(mars.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(mars.distance, 0.0f, 0.0f);
        glutSolidSphere(mars.radius, 15, 15);
    glPopMatrix();

    // Mars
    glPushMatrix();
        glColor3f(0.0f, 1.0f, 1.0f);
        glRotatef(mars.orbit, 0.0f, 0.0f, 1.0f);
        glTranslatef(30.0, 0.0f, 0.0f);
        glutSolidSphere(2.0f, 15, 15);
    glPopMatrix();


}

void draw_orbit_trail(Planet* planet){

}

void increment_orbit(double time){
    earth.orbit += earth.orbit_speed * time;
    moon.orbit += moon.orbit_speed * time;
    mars.orbit += mars.orbit_speed * time;
}
