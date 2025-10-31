#include "vex.h"
#include "Devices.h"
#include "UserControll.h"
#include "AutonSkills.h"
#include "AutonQualification.h"
#include "AutonMain.h"
#include "AutonFunction.h"
#include "AutonElimination.h"
#include "PID.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code; 

int SkillsPath = 0;
bool singleSkills = true;

void SkAuton(int val){   //shows what was selected for autonomous
  SkillsPath = val;


  if (SkillsPath == 1 && singleSkills == true){
    Brain.Screen.clearScreen();
    wait(5, msec);
    Brain.Screen.drawCircle(180, 120, 120, green);
    Brain.Screen.drawRectangle(360, 0, 120, 240, orange);
    Brain.Screen.printAt(5, 120, "Skills");
    Brain.Screen.printAt(365, 120, "Exit");
    Controller1.Screen.print("Skills                ");
  } 

  if (SkillsPath == 2 && singleSkills == true){
    singleSkills = false;
    SkillsPath = 0;
    wait(1, msec);
    startScreen();
    return;
  }

}

void SkillsSelected() {                                     //selection code for autonomous
  int x = Brain.Screen.xPosition();
  int y = Brain.Screen.yPosition();

  if(x>=0 && x<=360 && y>=0 && y<=240){SkAuton(1);}
  if(x>=360 && x <= 480 && y>=0 && y<=240){SkAuton(2);}
  
}

void SkillsAuton(){

    if (SkillsPath == 1){  
      PIDcontroll = true;
      // Insert the code for the auton skills here
      // Brain.Screen.print("Skills Running");
      // wait(1, sec);
      Drive(100);
      Brain.Screen.newLine();
      Brain.Screen.print("Drive 1 Ran");
      wait(5, msec);
      Turn(90);
      Brain.Screen.print("done");
      // Drive(-100);
      // Brain.Screen.newLine();
      // Brain.Screen.print("Drive 2 Ran");
      // wait(10, msec);
      // Turn(45);
      // Brain.Screen.newLine();
      // Brain.Screen.print("Turn 1 Ran");
      // Turn(-45);
      // Brain.Screen.newLine();
      // Brain.Screen.print("Turn 2 Ran");
      // Turn(90);
      // Brain.Screen.newLine();
      // Brain.Screen.print("Turn 1 Ran");
      // Turn(-90);
      // Brain.Screen.newLine();
      // Brain.Screen.print("Turn 2 Ran");
      // Turn(180);
      // Brain.Screen.newLine();
      // Brain.Screen.print("Turn 1 Ran");
      // Turn(-180);
      // Brain.Screen.newLine();
      // Brain.Screen.print("Turn 2 Ran");
      // Curve(100, 90);
      // Brain.Screen.newLine();
      // Brain.Screen.print("Curve 1 Ran");

      PIDcontroll = false;      
    }

    if (SkillsPath == 0){
        return;
    }
}