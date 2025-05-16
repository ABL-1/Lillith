#include "vex.h"
#include "Devices.h"
#include "UserControll.h"
#include "AutonSkills.h"
#include "AutonQualification.h"
#include "AutonMain.h"
#include "AutonFunction.h"
#include "AutonElimination.h"

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
        
      //Insert the code for the auton skills here
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(2,2);
      Brain.Screen.print("Skills");
    }

    if (SkillsPath == 0){
        return;
    }
}