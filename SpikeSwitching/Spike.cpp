//EVERYTHING HERE IS WRONG! DO NOT USE THIS AS AN EXAMPLE.

#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	Joystick stick; // only joystick
	Servo servo;
	Jaguar retrieval;
public:
	RobotDemo(void):

		stick(1),
		servo(3),
		retrieval (7)
		
	{

	}

	void Autonomous(void)
	{

	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		while(IsOperatorControl())
		{
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		screen->PrintfLine(DriverStationLCD::kUser_Line1,"");
		while(stick.GetRawButton(1))
		{
			servo.SetAngle(180);
			screen->PrintfLine(DriverStationLCD::kUser_Line1,"%f",servo.GetAngle());
			screen->UpdateLCD();
		}
		while(stick.GetRawButton(3))
				{
					servo.SetAngle(0);
					screen->PrintfLine(DriverStationLCD::kUser_Line1,"%f",servo.GetAngle());
					screen->UpdateLCD();
				}
		retrieval.Set(0.0);
		screen->UpdateLCD();
		}	
	}
};

START_ROBOT_CLASS(RobotDemo);

