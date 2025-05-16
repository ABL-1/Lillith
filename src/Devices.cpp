#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;

motor leftfrontmotor = motor(PORT18, ratio36_1, true);
motor leftmiddlemotor = motor(PORT19, ratio36_1, true); 
motor leftbackmotor = motor(PORT20, ratio36_1, false);   
motor rightfrontmotor = motor(PORT8, ratio36_1, false);
motor rigtmiddlemotor = motor(PORT9, ratio36_1, false); 
motor rightbackmotor = motor(PORT7, ratio36_1, true);
rotation odometry = rotation(PORT2, false);
inertial inertialsensor = inertial(PORT3);

motor_group LeftDriveSmart = motor_group(leftfrontmotor, leftmiddlemotor, leftbackmotor);
motor_group RightDriveSmart = motor_group(rightfrontmotor, rigtmiddlemotor, rightbackmotor);

controller Controller1 = controller(primary);
