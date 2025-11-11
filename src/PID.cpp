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

double DrivekP = 0.006;      //Tune this one first
double DrivekI = 0;       //leave at zero for drivetrain
double DrivekD = 0.003;

double TurnAdjustkP = 0.08;      //Tune this one first
double TurnAdjustkI = 0;       //leave at zero for drivetrain
double TurnAdjustkD = 0.0;
                                  //                                 Seperate turn and correction PID so I can tune them seperately
double TurnkP = 0.001;      //Tune this one first
double TurnkI = 0.005;       //leave at zero for drivetrain
double TurnkD = 0.00005;


float DriveError;
float DriveprevError = 0;
float Drivederivitive;
float DrivetotalError;

float TurnError;
float TurnPrevError = 0;
float TurnDerivitive;
float TurnTotalError;

float TurnAdjustError;
float TurnPrevAdjustError = 0;
float TurnAdjustDerivitive;
float TurnTotalAdjustError;

double DrivedesiredValue;
double TurndesiredValue;

double DrivemotorPower;
double TurnMotorPower;
double TurnAdjustMotorPower;

int PIDMax = 12;
float TurnPIDMin = 0;
float DrivePIDMin = 1.3;

double TurnCorrection = 0;

bool DriveComplete = false;
bool TurnComplete = false;


int drivetrainPID(){

    waitUntil(PIDcontroll == true);

    while(PIDcontroll){

        DriveComplete = false;
        TurnComplete = false;

        float LeftMotorsPosition = ((leftbackmotor.position(degrees) + leftmiddlemotor.position(degrees) + leftfrontmotor.position(degrees)) / 3);
        float RightMotorsPosition = ((rightbackmotor.position(degrees) + rigtmiddlemotor.position(degrees) + rightfrontmotor.position(degrees)) / 3);


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
        DrivemotorPower = (DriveError * DrivekP + DrivetotalError * DrivekI + Drivederivitive * DrivekD);

        ////////////////////////////////////////////////////////////////////////////
        //Drive Adjustment PID
        ///////////////////////////////////////////////////////////////

        double turnAdjustDifference = LeftMotorsPosition - RightMotorsPosition;
      
        TurnAdjustError = 0 - turnAdjustDifference;  //this is correct

        //takes the derivitive
        TurnAdjustDerivitive = TurnAdjustError - TurnPrevAdjustError;

        //takes the integral
        TurnTotalAdjustError += TurnAdjustError;

        //sets speed of the drivetrain
        TurnAdjustMotorPower = TurnError * TurnAdjustkP + TurnTotalError * TurnAdjustkI + TurnDerivitive * TurnAdjustkD;

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
        TurnMotorPower = TurnError * TurnkP + TurnTotalError * TurnkI + TurnDerivitive * TurnkD;

        ////////////////////////////////////////////////////////////////////////////
        //Turning Correction
        ///////////////////////////////////////////////////////////////

        if(std::abs(TurndesiredValue) > 0){
            
            TurnCorrection = (std::abs(LeftMotorsPosition) - std::abs(RightMotorsPosition)) * 1; //modifier to tune the severity of correction

        }

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

        double TurnVariable; 
        if(TurndesiredValue > 0){TurnVariable = TurnMotorPower;} else{TurnVariable = TurnAdjustMotorPower;}

        RightDriveSmart.spin(forward, DrivemotorPower - TurnVariable - TurnCorrection, voltageUnits::volt); 
        LeftDriveSmart.spin(forward, DrivemotorPower + TurnVariable + TurnCorrection, voltageUnits::volt); 


        DriveprevError = DriveError;
        TurnPrevError = TurnError;
        TurnPrevAdjustError = TurnAdjustError;

        

        if (std::abs(averagePosition) >= std::abs(DrivedesiredValue)){DriveComplete = true;} else{DriveComplete = false;}
        if (std::abs(turnDifference) >= std::abs(TurndesiredValue)){TurnComplete = true;} else{TurnComplete = false;}


        vex::task::sleep(5);

        if (std::abs(DrivedesiredValue) > 0 && DriveComplete == true && TurndesiredValue == 0){LeftDriveSmart.stop(); RightDriveSmart.stop();}
        if (DrivedesiredValue == 0 && TurnComplete == true && std::abs(TurndesiredValue) > 0){LeftDriveSmart.stop(); RightDriveSmart.stop();}

        vex::task::sleep(7);
    }

    return 1;
}