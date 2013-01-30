#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	//RobotDrive myRobot;
	Joystick stick; // only joystick
	Jaguar jagl, jagr; // robot drive system

public:
	RobotDemo(void):
		//myRobot(1, 2),	// these must be initialized in the same order
		stick(1),		// as they are declared above.
		jagl (1), jagr (2)	
	{
		//myRobot.SetExpiration(0.1);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		/*
		myRobot.SetSafetyEnabled(false);
		myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
		Wait(2.0); 				//    for 2 seconds
		myRobot.Drive(0.0, 0.0); 	// stop robot
		*/
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
	float throttle = 0;
	float direction = 0;
	DriverStationLCD *screen = DriverStationLCD::GetInstance();
		while (IsOperatorControl())
		{
			
			throttle = stick.GetThrottle();
			
			while(stick.GetThrottle() > 0.01 || stick.GetThrottle() < -0.01)
			{
				jagl.Set(stick.GetThrottle());
				jagr.Set(-stick.GetThrottle());
				screen->PrintfLine(DriverStationLCD::kUser_Line3, "Left Jag Set: %f", jagl.Get());
				screen->PrintfLine(DriverStationLCD::kUser_Line4, "Right Jag Set: %f", jagr.Get());
				screen->UpdateLCD();
			}
			
			
			
			direction = stick.GetX(); //direction left or right based on x
			//if (direction < 0)
			//direction  = -direction;
			while (stick.GetX() < -.1)
			{
			jagl.Set(stick.GetX());
			jagr.Set(stick.GetX());
			screen->PrintfLine(DriverStationLCD::kUser_Line3, "Left Jag Set: %f", jagl.Get());
			screen->PrintfLine(DriverStationLCD::kUser_Line4, "Right Jag Set: %f", jagr.Get());
			screen->UpdateLCD();
			}
			while (stick.GetX() > .1)
			{
			jagl.Set(stick.GetX());
			jagr.Set(stick.GetX());
			screen->PrintfLine(DriverStationLCD::kUser_Line3, "Left Jag Set: %f", jagl.Get());
			screen->PrintfLine(DriverStationLCD::kUser_Line4, "Right Jag Set: %f", jagr.Get());
			screen->UpdateLCD();
			}
			screen->PrintfLine(DriverStationLCD::kUser_Line1, "Throttle: %f",	throttle);
			screen->PrintfLine(DriverStationLCD::kUser_Line2, "Direction: %f",	direction);
			screen->PrintfLine(DriverStationLCD::kUser_Line3, "Left Jag Set: %f", jagl.Get());
			screen->PrintfLine(DriverStationLCD::kUser_Line4, "Right Jag Set: %f", jagr.Get());
			jagl.Set(0.0);
			jagr.Set(0.0);
			screen->UpdateLCD();

	
					
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

