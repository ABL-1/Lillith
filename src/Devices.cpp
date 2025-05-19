#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;

motor leftfrontmotor = motor(PORT20, ratio36_1, false);
motor leftmiddlemotor = motor(PORT19, ratio36_1, true); 
motor leftbackmotor = motor(PORT18, ratio36_1, true);   

motor rightfrontmotor = motor(PORT11, ratio36_1, true);
motor rigtmiddlemotor = motor(PORT12, ratio36_1, false); 
motor rightbackmotor = motor(PORT13, ratio36_1, false);
rotation odometry = rotation(PORT2, false);
inertial inertialsensor = inertial(PORT3);

motor_group LeftDriveSmart = motor_group(leftfrontmotor, leftmiddlemotor, leftbackmotor);
motor_group RightDriveSmart = motor_group(rightfrontmotor, rigtmiddlemotor, rightbackmotor);

controller Controller1 = controller(primary);
