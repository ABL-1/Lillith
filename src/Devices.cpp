#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;

motor leftfrontmotor = motor(PORT6, ratio6_1, false);
motor leftmiddlemotor = motor(PORT5, ratio6_1, true); 
motor leftbackmotor = motor(PORT4, ratio6_1, true);   

motor rightfrontmotor = motor(PORT3, ratio6_1, true);
motor rigtmiddlemotor = motor(PORT2, ratio6_1, false); 
motor rightbackmotor = motor(PORT1, ratio6_1, false);
inertial inertialsensor = inertial(PORT12);

motor_group LeftDriveSmart = motor_group(leftfrontmotor, leftmiddlemotor, leftbackmotor);
motor_group RightDriveSmart = motor_group(rightfrontmotor, rigtmiddlemotor, rightbackmotor);

motor Intake1 = motor(PORT20, ratio6_1, true);
motor Intake2 = motor(PORT19, ratio18_1, false);
motor Intake3 = motor(PORT18, ratio18_1, false);

controller Controller1 = controller(primary);

digital_out scooper = digital_out(digital_out(Brain.ThreeWirePort.G));
digital_out parker = digital_out(digital_out(Brain.ThreeWirePort.H));