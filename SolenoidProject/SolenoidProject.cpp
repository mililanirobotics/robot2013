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
	Joystick stick; // only joystick
	//Solenoid solenoid;
	Victor victor;
	
	int buttoncount;
public:
	RobotDemo(void):
		//myRobot(1, 2),	// these must be initialized in the same order
		stick(1),		// as they are declared above.
		//solenoid(3, 1),
		victor (2)
	{
		//myRobot.SetExpiration(0.1);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		//myRobot.SetSafetyEnabled(false);
		//myRobot.Drive(0.5, 0.0); 	// drive forwards half speed
		//Wait(2.0); 				//    for 2 seconds
		//myRobot.Drive(0.0, 0.0); 	// stop robot
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		//myRobot.SetSafetyEnabled(true);
		while(IsOperatorControl()) {
			screen->UpdateLCD();
			/*
			if(stick.GetRawButton(1))
			{
				victor.Set(.1);
				screen->PrintfLine(DriverStationLCD::kUser_Line1,"Button1");
			}
			else if(stick.GetRawButton(2))
			{
				victor.Set(.2);
				screen->PrintfLine(DriverStationLCD::kUser_Line2,"Button2");
			}
			else if(stick.GetRawButton(3))
			{
				victor.Set(.3);
			}
			else if(stick.GetRawButton(4))
			{
				victor.Set(.4);
			}
			else if(stick.GetRawButton(5))
			{
				victor.Set(.5);
			}
			else if(stick.GetRawButton(6))
			{
				victor.Set(.6);
			}
			else if(stick.GetRawButton(7))
			{
				victor.Set(.7);
			}
			else if(stick.GetRawButton(8))
			{
				victor.Set(.8);
			}
			else if(stick.GetRawButton(9))
			{
				victor.Set(.9);
			}         
			else if(stick.GetRawButton(10))
			{
				victor.Set(1.0);
			}
			victor.Set(stick.GetY());
			*/
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

