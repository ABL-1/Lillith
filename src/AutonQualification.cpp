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



bool singleQualification = true;

int aoutonpath = 0;

bool wallStake = true;

void setauton(int val){   //shows what was selected for autonomous
  aoutonpath = val;

  if (aoutonpath == 0){aoutonpath = 2;}

  if (aoutonpath == 1 && singleQualification == true){
    Brain.Screen.clearScreen();
    wait(5, msec);
    Brain.Screen.drawRectangle(0, 0, 180, 120, red);
    Brain.Screen.printAt(5, 60, "Left Side");
    Brain.Screen.drawRectangle(0, 120, 180, 120);
    Brain.Screen.printAt(5, 180, "Right Side");
    Brain.Screen.drawRectangle(180, 0, 180, 120);
    Brain.Screen.printAt(185, 60, "Right Side");
    Brain.Screen.drawRectangle(180, 120, 180, 120);
    Brain.Screen.printAt(185, 180, "Left Side");
    Brain.Screen.drawRectangle(360, 0, 120, 240, orange);
    Brain.Screen.printAt(365, 120, "Exit");   
  } 

  if (aoutonpath == 2 && singleQualification == true){
    Brain.Screen.clearScreen();
    wait(5, msec);
     Brain.Screen.drawRectangle(0, 0, 180, 120);
    Brain.Screen.printAt(5, 60, "Left Side");
    Brain.Screen.drawRectangle(0, 120, 180, 120);
    Brain.Screen.printAt(5, 180, "Right Side");
    Brain.Screen.drawRectangle(180, 0, 180, 120, blue);
    Brain.Screen.printAt(185, 60, "Right Side");
    Brain.Screen.drawRectangle(180, 120, 180, 120);
    Brain.Screen.printAt(185, 180, "Left Side");
    Brain.Screen.drawRectangle(360, 0, 120, 240, orange);
    Brain.Screen.printAt(365, 120, "Exit");
  }  

  if (aoutonpath == 3 && singleQualification == true){
    Brain.Screen.clearScreen();
    wait(5, msec);
     Brain.Screen.drawRectangle(0, 0, 180, 120);
    Brain.Screen.printAt(5, 60, "Left Side");
    Brain.Screen.drawRectangle(0, 120, 180, 120, red);
    Brain.Screen.printAt(5, 180, "Right Side");
    Brain.Screen.drawRectangle(180, 0, 180, 120);
    Brain.Screen.printAt(185, 60, "Right Side");
    Brain.Screen.drawRectangle(180, 120, 180, 120);
    Brain.Screen.printAt(185, 180, "Left Side");
    Brain.Screen.drawRectangle(360, 0, 120, 240, orange);
    Brain.Screen.printAt(365, 120, "Exit");
  } 

  if (aoutonpath == 4 && singleQualification == true){
    Brain.Screen.clearScreen();
    wait(5, msec);
     Brain.Screen.drawRectangle(0, 0, 180, 120);
    Brain.Screen.printAt(5, 60, "Left Side");
    Brain.Screen.drawRectangle(0, 120, 180, 120);
    Brain.Screen.printAt(5, 180, "Right Side");
    Brain.Screen.drawRectangle(180, 0, 180, 120);
    Brain.Screen.printAt(185, 60, "Right Side");
    Brain.Screen.drawRectangle(180, 120, 180, 120, blue);
    Brain.Screen.printAt(185, 180, "Left Side");
    Brain.Screen.drawRectangle(360, 0, 120, 240, orange);
    Brain.Screen.printAt(365, 120, "Exit");
  } 

  if (aoutonpath == 5 && singleQualification == true){
    singleQualification = false;
    aoutonpath = 0;
    wait(1, msec);
    startScreen();
    return;
  }
}

void QualificationSelected() {                                     //selection code for autonomous
  int x = Brain.Screen.xPosition();
  int y = Brain.Screen.yPosition();

  if(x>=0 && x<=180 && y>=0 && y<=120){setauton(1);}
  if(x>=180 && x<=360 && y>=0 && y<=120){setauton(2);}
  if(x>=0 && x<=180 && y>=120 && y<=240){setauton(3);}
  if(x>=180 && x<=360 && y>=120 && y<=240){setauton(4);}
  if(x>=360 && x<=480 && y>=0 && y<=240){setauton(5);}
  
}


void QualificationAutonLogic() {                // Different aoutonomous paths, this is where the actual auton code goes.
    Brain.Screen.pressed(QualificationSelected);
  
  if (aoutonpath == 2){
      //this is the code for the right side autonomous red alliance


  }

    if (aoutonpath == 1){
      //this is the code for the left side autonomous blue alliance


    }

  if (aoutonpath == 3){
      //this is the code for the right side autonomous blue alliance


    }

    if (aoutonpath == 4){
      //this is the code for the left side autonomous red alliance

    }

    if (aoutonpath == 0){
      return;
    }

}