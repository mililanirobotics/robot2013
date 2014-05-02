#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	//RobotDrive myRobot; // robot drive system
	//Joystick stick; // only joystick
	Gyro gyro;

public:
	RobotDemo(void):
		//myRobot(1, 2),	// these must be initialized in the same order
		//stick(1)		// as they are declared above.
		gyro (1,1) 
	{
		
	}
	
	void OperatorControl(void)
	{
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		gyro.Reset();
		while (IsOperatorControl())
		{
			float angle = 0.0;
			angle = gyro.GetAngle();
			screen->PrintfLine(DriverStationLCD::kUser_Line1,"Angle %f",angle );
			screen->PrintfLine(DriverStationLCD::kUser_Line3,"Nosu ar orothrim");
			screen->UpdateLCD();// wait for a motor update time
		}
	}
};

START_ROBOT_CLASS(RobotDemo);
