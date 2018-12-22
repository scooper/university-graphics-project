#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "Character.h"
#include "Model.h"

class Character {

  public:
    Character();
    void idle();
    void moving();
    void jumping();

  private:
    Model *th;
    Model *ulA;
    Model *urA;
    Model *llA;
    Model *lrA;
    Model *ulL;
    Model *urL;
    Model *llL;
    Model *lrL;

    void leftLeg();
    void rightLeg();
    void leftArm();
    void rightArm();
    float interpolate(float start, float end, float time);


};
#endif
