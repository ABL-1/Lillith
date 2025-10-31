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

void AutonLogic(){
    QualificationAutonLogic();
    EliminationAutonLogic();
    SkillsAuton();
}

int setpath = 0; 

bool singleRun = true;

void setcode(int val){
  setpath = val;

  Brain.Screen.clearScreen();
}

void selection() {                                     //selection code for autonomous
  int x = Brain.Screen.xPosition();
  int y = Brain.Screen.yPosition();

  if(x>=0 && x<=160 && y>=0 && y<=240){setcode(1);}
  if(x>=160 && x<=320 && y>=0 && y<=240){setcode(2);}
  if(x>=320 && x<=480 && y>=0 && y<=240){setcode(3);}
  
  if(setpath == 1 && singleRun == true){
    singleRun = false;
    Brain.Screen.clearScreen();
    wait(5, msec);
    Brain.Screen.drawRectangle(0, 0, 180, 120, red);
    Brain.Screen.printAt(5, 60, "Left Side");
    Brain.Screen.drawRectangle(0, 120, 180, 120, red);
    Brain.Screen.printAt(5, 180, "Right Side");
    Brain.Screen.drawRectangle(180, 0, 180, 120, blue);
    Brain.Screen.printAt(185, 60, "Right Side");
    Brain.Screen.drawRectangle(180, 120, 180, 120, blue);
    Brain.Screen.printAt(185, 180, "Left Side");
    Brain.Screen.drawRectangle(360, 0, 120, 240, orange);
    Brain.Screen.printAt(365, 120, "Exit");
    Brain.Screen.pressed(QualificationSelected);
    Brain.Screen.printAt(5, 120, "Qualification");
    Controller1.Screen.print("Qualification           ");
  }

  if(setpath == 2 && singleRun == true){
    singleRun = false;
    Brain.Screen.clearScreen();
    wait(5, msec);
    Brain.Screen.drawRectangle(0, 0, 180, 120, red);
    Brain.Screen.printAt(5, 60, "Left Side");
    Brain.Screen.drawRectangle(0, 120, 180, 120, red);
    Brain.Screen.printAt(5, 180, "Right Side");
    Brain.Screen.drawRectangle(180, 0, 180, 120, blue);
    Brain.Screen.printAt(185, 60, "Right Side");
    Brain.Screen.drawRectangle(180, 120, 180, 120, blue);
    Brain.Screen.printAt(185, 180, "Left Side");
    Brain.Screen.drawRectangle(360, 0, 120, 240, orange);
    Brain.Screen.printAt(365, 120, "Exit");
    Brain.Screen.pressed(EliminationSelected);
    Brain.Screen.printAt(5, 120, "Elimination");
    Controller1.Screen.print("Elimination             ");
  }

  if(setpath == 3 && singleRun == true){
    singleRun = false;
    Brain.Screen.clearScreen();
    wait(5, msec);
    Brain.Screen.drawCircle(180, 120, 120, red);
    Brain.Screen.drawRectangle(360, 0, 120, 240, orange);
    Brain.Screen.pressed(SkillsSelected);
    Brain.Screen.printAt(5, 120, "Skills");
    Brain.Screen.printAt(365, 120, "Exit");
    Controller1.Screen.print("Skills                ");
  }
}

void startScreen(){
  wait(3, msec);
  singleRun = true;
  setpath = 0;
  Brain.Screen.clearScreen();
  wait(3, msec);
  Brain.Screen.drawRectangle(0, 0, 160, 240, green);
  Brain.Screen.printAt(5, 120, "Qualification");
  Brain.Screen.drawRectangle(160, 0, 160, 240, green);
  Brain.Screen.printAt(165, 120, "Elimination");
  Brain.Screen.drawRectangle(320, 0, 160, 240, green);
  Brain.Screen.printAt(325, 120, "Skills");
  Brain.Screen.pressed(selection);
  return;                                              // Remove this if it accidentially kills the UI
}