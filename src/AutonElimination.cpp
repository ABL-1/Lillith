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




bool singleElimination = true;

int EliminationPath = 0;

void EliminationAuton(int val){   //shows what was selected for autonomous
  EliminationPath = val;

  if (EliminationPath == 0){EliminationPath = 2;}

  if (EliminationPath == 1 && singleElimination == true){
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

  if (EliminationPath == 2 && singleElimination == true){
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

  if (EliminationPath == 3 && singleElimination == true){
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

  if (EliminationPath == 4 && singleElimination == true){
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
  
  if (EliminationPath == 5 && singleElimination == true){
    singleElimination = false;
    EliminationPath = 0;
    wait(1, msec);
    startScreen();
    return;
  }
}

void EliminationSelected() {                                     //selection code for autonomous
  int x = Brain.Screen.xPosition();
  int y = Brain.Screen.yPosition();

  if(x>=0 && x<=180 && y>=0 && y<=120){EliminationAuton(1);}
  if(x>=180 && x<=360 && y>=0 && y<=120){EliminationAuton(2);}
  if(x>=0 && x<=180 && y>=120 && y<=240){EliminationAuton(3);}
  if(x>=180 && x<=360 && y>=120 && y<=240){EliminationAuton(4);}
  if(x>=360 && x<=480 && y>=0 && y<=240){EliminationAuton(5);}
  
}


void EliminationAutonLogic() {                // Different aoutonomous paths, this is where the actual auton code goes.
    Brain.Screen.pressed(EliminationSelected);
  
  if (EliminationPath == 2){
      //this is the code for the right side autonomous red alliance
      //also known as stake side
      
      
  }

    if (EliminationPath == 1){
      //this is the code for the left side autonomous blue alliance
      //also known as stake side

    }

  if (EliminationPath == 3){
      //this is the code for the right side autonomous blue alliance
      //also known as blue ring side

    }

    if (EliminationPath == 4){
      //this is the code for the left side autonomous red alliance
      //also known as red ring side
      
    }

    if (EliminationPath == 0){
        return;
    }

}



