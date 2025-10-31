#include "vex.h"
#include "Devices.h"
#include "UserControll.h"
#include "AutonSkills.h"
#include "AutonQualification.h"
#include "AutonMain.h"
#include "AutonFunction.h"
#include "AutonElimination.h"
#include "cmath"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

bool PIDcontroll;                    // This is numberical optimization!!!!!!!!!

double DrivekP = 0.005;      //Tune this one first
double DrivekI = 0;       //leave at zero for drivetrain
double DrivekD = 0.03;

double TurnkP = 0.003;      //Tune this one first
double TurnkI = 0.005;       //leave at zero for drivetrain
double TurnkD = 0.005;


float DriveError;
float DriveprevError = 0;
float Drivederivitive;
float DrivetotalError;

float TurnError;
float TurnPrevError = 0;
float TurnDerivitive;
float TurnTotalError;

double DrivedesiredValue;
double TurndesiredValue;

double DrivemotorPower;
double TurnMotorPower;

int PIDMax = 12;
float TurnPIDMin = 0.5;
float DrivePIDMin = 1.5;


bool DriveComplete = false;
bool TurnComplete = false;

double RightDriveCorrection;
double LeftDriveCorrection;

double RightTurnCorrection;
double LeftTurnCorrection;


int drivetrainPID(){

    waitUntil(PIDcontroll == true);

    while(PIDcontroll){

        DriveComplete = false;
        TurnComplete = false;

        float LeftMotorsPosition = ((leftbackmotor.position(degrees) + leftmiddlemotor.position(degrees) + leftfrontmotor.position(degrees)) / 3);
        float RightMotorsPosition = ((rightbackmotor.position(degrees) + rigtmiddlemotor.position(degrees) + rightfrontmotor.position(degrees)) / 3);

        /////////////////////////////////////////////////////////////
        //Drive Correction
        //////////////////////////////////////////////////////////////

        if(std::abs(DrivedesiredValue) >= 0 && TurndesiredValue == 0){ 
            if(std::abs(LeftMotorsPosition) > std::abs(RightMotorsPosition)){
                RightDriveCorrection = (std::abs(LeftMotorsPosition) - std::abs(RightMotorsPosition)) * DrivekP * DriveError * 0.005; //Controlls the severity with which it corrects
            }
            else{RightDriveCorrection = 0;}

            if(std::abs(RightMotorsPosition) > std::abs(LeftMotorsPosition)){
                LeftDriveCorrection = (std::abs(RightMotorsPosition) - std::abs(LeftMotorsPosition)) * DrivekP * DriveError * 0.005; //Controlls the severity with which it corrects
            }
            else{LeftDriveCorrection = 0;}
        }


        /////////////////////////////////////////////////////////////
        //Turn Correction
        //////////////////////////////////////////////////////////////

        if(DrivedesiredValue == 0 && std::abs(TurndesiredValue) >= 0){ 
            if(std::abs(LeftMotorsPosition) > std::abs(RightMotorsPosition)){
                RightTurnCorrection = (std::abs(LeftMotorsPosition) - std::abs(RightMotorsPosition)) * DrivekP * DriveError * 5; //Controlls the severity with which it corrects
            }
            else{RightDriveCorrection = 0;}

            if(std::abs(RightMotorsPosition) > std::abs(LeftMotorsPosition)){
                LeftTurnCorrection = (std::abs(RightMotorsPosition) - std::abs(LeftMotorsPosition)) * DrivekP * DriveError * 5; //Controlls the severity with which it corrects
            }
            else{LeftDriveCorrection = 0;}
        }

        /////////////////////////////////////////////////////////////////////////////
        //Driving PID
        //////////////////////////////////////////////////////////////

        double averagePosition = (LeftMotorsPosition + RightMotorsPosition) / 2;

        DriveError = DrivedesiredValue - averagePosition;  //this is correct

        //takes the derivitive
        Drivederivitive = DriveError - DriveprevError;

        //takes the integral
        DrivetotalError += DriveError;

        //sets speed of the drivetrain
        if(std::abs(DrivedesiredValue) > 0){DrivemotorPower = (DriveError * DrivekP + DrivetotalError * DrivekI + Drivederivitive * DrivekD);} else {DrivemotorPower = 0;}

        ////////////////////////////////////////////////////////////////////////////
        //Turning PID
        ///////////////////////////////////////////////////////////////

        double turnDifference = LeftMotorsPosition - RightMotorsPosition;
      
        TurnError = TurndesiredValue - turnDifference;  //this is correct

        //takes the derivitive
        TurnDerivitive = TurnError - TurnPrevError;

        //takes the integral
        TurnTotalError += TurnError;

        //sets speed of the drivetrain
        if(std::abs(TurndesiredValue) > 0){TurnMotorPower = TurnError * TurnkP + TurnTotalError * TurnkI + TurnDerivitive * TurnkD;} else{TurnMotorPower = 0;};

        ////////////////////////////////////////////////////////
        //Defining the min and max
        //////////////////////////////////////////////////////////
        if(TurndesiredValue == 0){
            if (std::abs(DrivemotorPower) <= DrivePIDMin && std::abs(DrivemotorPower) > 0){if(DrivedesiredValue > 0){DrivemotorPower = DrivePIDMin;} if(DrivedesiredValue < 0){DrivemotorPower = -1 * DrivePIDMin;}}   
            if (std::abs(DrivemotorPower) >= PIDMax){if(DrivedesiredValue > 0){DrivemotorPower = PIDMax;} if(DrivedesiredValue < 0){DrivemotorPower = -1 * PIDMax;}}

            if (std::abs(TurnMotorPower) <= DrivePIDMin && std::abs(TurnMotorPower) > 0){if(TurndesiredValue > 0){TurnMotorPower = DrivePIDMin;} if(TurndesiredValue < 0){TurnMotorPower = -1 * DrivePIDMin;}}   
            if (std::abs(TurnMotorPower) >= PIDMax){if(TurndesiredValue > 0){TurnMotorPower = PIDMax;} if(TurndesiredValue < 0){TurnMotorPower = -1 * PIDMax;}}
        }

        if(DrivedesiredValue == 0){
            if (std::abs(DrivemotorPower) <= TurnPIDMin && std::abs(DrivemotorPower) > 0){if(DrivedesiredValue > 0){DrivemotorPower = TurnPIDMin;} if(DrivedesiredValue < 0){DrivemotorPower = -1 * TurnPIDMin;}}   
            if (std::abs(DrivemotorPower) >= PIDMax){if(DrivedesiredValue > 0){DrivemotorPower = PIDMax;} if(DrivedesiredValue < 0){DrivemotorPower = -1 * PIDMax;}}

            if (std::abs(TurnMotorPower) <= TurnPIDMin && std::abs(TurnMotorPower) > 0){if(TurndesiredValue > 0){TurnMotorPower = TurnPIDMin;} if(TurndesiredValue < 0){TurnMotorPower = -1 * TurnPIDMin;}}   
            if (std::abs(TurnMotorPower) >= PIDMax){if(TurndesiredValue > 0){TurnMotorPower = PIDMax;} if(TurndesiredValue < 0){TurnMotorPower = -1 * PIDMax;}}
        }

        ///////////////////////////////////////////////////////////
        //Drivetrain Controll
        ////////////////////////////////////////////////////////////////

        RightDriveSmart.spin(forward, DrivemotorPower + RightDriveCorrection + RightTurnCorrection - TurnMotorPower, voltageUnits::volt); 
        LeftDriveSmart.spin(forward, DrivemotorPower + LeftDriveCorrection + LeftTurnCorrection + TurnMotorPower, voltageUnits::volt); 


        DriveprevError = DriveError;
        TurnPrevError = TurnError;

        vex::task::sleep(10);

        if (std::abs(averagePosition) >= std::abs(DrivedesiredValue)){DriveComplete = true;} else{DriveComplete = false;}
        if (std::abs(turnDifference) >= std::abs(TurndesiredValue)){TurnComplete = true;} else{TurnComplete = false;}

        if (std::abs(DrivedesiredValue) > 0 && DriveComplete == true && TurndesiredValue == 0){LeftDriveSmart.stop(); RightDriveSmart.stop();}
        if (DrivedesiredValue == 0 && TurnComplete == true && std::abs(TurndesiredValue) > 0){LeftDriveSmart.stop(); RightDriveSmart.stop();}

        vex::task::sleep(10);
    }

    return 1;
}