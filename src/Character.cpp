#include <string>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Character.h"
#include "Model.h"

double LOWER_LEG_HEIGHT = -4;
double UPPER_LEG_HEIGHT = -2.3;
double SHOULDER_WIDTH = 1.3;
double HIP_WIDTH = 0.7;
double LOWER_ARM_HEIGHT = -1.15;
double UPPER_ARM_HEIGHT = -0.2;
int MAX_ANGLE = 360;

Character::Character() {
  // torso/head
  th = new Model("models/torso.obj", "textures/torso.ppm");
  // arm bits
  ulA = new Model("models/upperLarm.obj", "");
  urA = new Model("models/upperRarm.obj", "");
  llA = new Model("models/lowerLarm.obj", "");
  lrA = new Model("models/lowerRarm.obj", "");
  // leg bits
  ulL = new Model("models/upperLleg.obj", "");
  urL = new Model("models/upperRleg.obj", "");
  llL = new Model("models/lowerLleg.obj", "");
  lrL = new Model("models/lowerRleg.obj", "");

}

float Character::interpolate(float start, float end, float time) {
  return ((1-time) * start) + (time * end);
}

void Character::idle() {
  glPushMatrix();
    th->draw();
    this->leftLeg();
    this->rightLeg();
    this->leftArm();
    this->rightArm();
  glPopMatrix();

}

void Character::moving() {
  th->draw();
  glPushMatrix();
    this->leftLeg();
  glPopMatrix();
  glPushMatrix();
    this->rightLeg();
  glPopMatrix();
  glPushMatrix();
    this->rightArm();
    this->leftArm();
  glPopMatrix();

}

void Character::jumping() {
  th->draw();
  glPushMatrix();
    glTranslatef(0.0,UPPER_LEG_HEIGHT+0.4,-1.0);
    glRotatef(70,1.0,0.0,0.0);
    glTranslatef(0.0,-UPPER_LEG_HEIGHT+0.2,0.0);
    this->leftLeg();
    this->rightLeg();
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-(SHOULDER_WIDTH/2)-0.2,0.0,0.0);
    glRotatef(-70,0.0,0.0,1.0);
    glTranslatef((SHOULDER_WIDTH/2)-0.2,0.0,0.0);
    this->rightArm();
  glPopMatrix();
  glPushMatrix();
    glTranslatef((SHOULDER_WIDTH/2)+0.2,0.0,0.0);
    glRotatef(70,0.0,0.0,1.0);
    glTranslatef(-(SHOULDER_WIDTH/2)+0.2,0.0,0.0);
    this->leftArm();
  glPopMatrix();
}

void Character::leftLeg() {
  glPushMatrix();
  //glRotatef(20, 0.0, 0.0, 1.0);
    glPushMatrix();
      glTranslatef(HIP_WIDTH/2,UPPER_LEG_HEIGHT,0.0);
      ulL->draw();
    glPopMatrix();
    glPushMatrix();
      //glTranslatef(-0.78,-4, -0.38);
      glTranslatef(HIP_WIDTH/2,LOWER_LEG_HEIGHT,-0.2);
      llL->draw();
    glPopMatrix();
  glPopMatrix();
}

void Character::rightLeg() {
  glPushMatrix();
    glPushMatrix();
      glTranslatef(-HIP_WIDTH/2,UPPER_LEG_HEIGHT,0.0);
      urL->draw();
      glPopMatrix();
    glPushMatrix();
      //glTranslatef(0.78,-4, -0.38);
      glTranslatef(-HIP_WIDTH/2,LOWER_LEG_HEIGHT,-0.2);
      lrL->draw();
    glPopMatrix();
  glPopMatrix();
}

void Character::leftArm() {
  glPushMatrix();
    glPushMatrix();
      glTranslatef(SHOULDER_WIDTH/2,UPPER_ARM_HEIGHT,0.0);
      ulA->draw();
    glPopMatrix();
    glPushMatrix();
      glTranslatef((SHOULDER_WIDTH/2)+0.15,LOWER_ARM_HEIGHT,0.0);
      llA->draw();
    glPopMatrix();
  glPopMatrix();
}

void Character::rightArm() {
  glPushMatrix();
    glPushMatrix();
      glTranslatef(-SHOULDER_WIDTH/2,UPPER_ARM_HEIGHT,0.0);
      urA->draw();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-((SHOULDER_WIDTH/2)+0.15),LOWER_ARM_HEIGHT,0.0);
      lrA->draw();
    glPopMatrix();
  glPopMatrix();
}
