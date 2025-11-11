#include "vex.h"
#include "PID.h"
#include "Devices.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;


void Drive(double driveDistance){  //driveDistance is in centimeters

    LeftDriveSmart.resetPosition();
    wait(1, msec);
    RightDriveSmart.resetPosition();
    wait(1, msec);

    TurndesiredValue = 0;

    double distancePerRevolution = 19.4; // this is in cm, and it is the distance that the 3.25 in omni wheels go in one rotation on our drivetrain setup

    DrivedesiredValue = (driveDistance / distancePerRevolution) * 360; //This is in degrees

    waitUntil(DriveComplete == true);  
    wait(1, msec);
}

 void Turn(double turnDegrees){

    double TurnValue = turnDegrees;

    LeftDriveSmart.resetPosition();
    wait(1, msec);
    RightDriveSmart.resetPosition();
    wait(1, msec);

    double CirclePercent = (TurnValue); //the 360 degrees cancel out

    DrivedesiredValue = 0;

    double driveDistance = (CirclePercent * 94); //drive circumfrence

    double rotations = (driveDistance / 19.4); // this is in cm, and it is the distance that the 3.25 in omni wheels go in one rotation

    TurndesiredValue = rotations;
    

    waitUntil(TurnComplete == true);  
    wait(1, msec);
}

void Curve(double DriveDistance, double TurnValue){

    LeftDriveSmart.resetPosition();
    wait(1, msec);
    RightDriveSmart.resetPosition();
    wait(1, msec);

    double distancePerRevolution = 21.944024311; // this is in cm, and it is the distance that the 2.75 in omni wheels go in one rotation

    double CirclePercent = (TurnValue);

    double driveDistance = (CirclePercent * 82.5); //drive circumfrence

    double rotations = (driveDistance / distancePerRevolution) * 2; // this is in cm, and it is the distance that the 2.75 in omni wheels go in one rotation

    TurndesiredValue = rotations;

    DrivedesiredValue = (DriveDistance / distancePerRevolution) * 360; //This is in degrees

    waitUntil(TurnComplete == true && DriveComplete == true);

}