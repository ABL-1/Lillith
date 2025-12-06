#include "vex.h"
#include "Devices.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3
      // right = Axis2
      int drivetrainLeftSideSpeed = Controller1.Axis3.position();
      int drivetrainRightSideSpeed = Controller1.Axis2.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, vex::percent);
        LeftDriveSmart.spin(vex::forward);                                                           
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, vex::percent);
        RightDriveSmart.spin(vex::forward);
      }

      if (Controller1.ButtonR1.pressing()){ // Scores the blocks on the low goals
        Intake1.setVelocity(100, percent);
        Intake2.setVelocity(100, percent);
        Intake1.spin(forward);
        Intake2.spin(reverse);
        Intake3.setVelocity(100, percent);
        Intake3.spin(forward);
      }


      if (Controller1.ButtonL2.pressing()){ // Scores the blocks on the medium goals
        Intake3.setVelocity(100, percent);
        Intake3.spin(reverse);
        Intake1.setVelocity(100, percent);
        Intake2.setVelocity(100, percent);
        Intake1.spin(reverse);
        Intake2.spin(reverse);
      }

      if (Controller1.ButtonL1.pressing()){ // Scores the blocks on the high goals
        Intake3.setVelocity(100, percent);
        Intake3.spin(forward);
        Intake1.setVelocity(100, percent);
        Intake2.setVelocity(100, percent);
        Intake1.spin(reverse);
        Intake2.spin(reverse);
      }

      if (Controller1.ButtonR2.pressing()){ // Store the blocks
        Intake1.setVelocity(100, percent);
        Intake2.setVelocity(100, percent);
        Intake1.spin(reverse);
        Intake2.spin(forward);
      }


      if (!Controller1.ButtonR2.pressing() && !Controller1.ButtonR1.pressing() && !Controller1.ButtonRight.pressing() && !Controller1.ButtonL2.pressing() && !Controller1.ButtonL1.pressing() && !Controller1.ButtonB.pressing()){
        Intake1.stop();
        Intake2.stop();
        Intake3.stop();
      }

      if(Controller1.ButtonDown.pressing()){ // Lowers the loader reloader
        scooper.set(true);
      }

      if(Controller1.ButtonRight.pressing()){ // Raises the Loader reloader
        scooper.set(false);
      }

      if(Controller1.ButtonA.pressing()){ // Extend the parking mech
        parker.set(true);
      }

      if(Controller1.ButtonX.pressing()){ // Retract the parking mech
        parker.set(false);
      }

      if(Controller1.ButtonB.pressing()){
        pummeler.set(true); 
      }

      if(!Controller1.ButtonB.pressing()){
        pummeler.set(false);
      }

    // wait before repeating the process
    vex::wait(20, vex::msec);
  }
  return 0;
}
}

void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain Inertial
  vex::wait(200, vex::msec);
  inertialsensor.calibrate();
  Brain.Screen.print("Calibrating Inertial for Drivetrain");
  // wait for the Inertial calibration process to finish
  while (inertialsensor.isCalibrating()) {
    vex::wait(25, vex::msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  vex::task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
  vex::wait(50, vex::msec);
  Brain.Screen.clearScreen();
}
