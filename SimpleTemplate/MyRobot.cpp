#include "WPILib.h"
#include <math.h>
/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick

public:
	RobotDemo(void):
		myRobot(1, 2, 3, 4),	// these must be initialized in the same order
		stick(1)		// as they are declared above.
	{

	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
	
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		float magnitude;
		float direction;
		while (IsOperatorControl())
		{
			magnitude = sqrt(stick.GetX()*stick.GetX() + stick.GetY()*stick.GetY());
			direction = stick.GetDirectionDegrees()+180;
			if (magnitude > 1)
				magnitude = 1;
			myRobot.MecanumDrive_Polar(stick.GetThrottle(), direction, magnitude); // drive with arcade style (use right stick)
			//Parameters may be inverted.  Mecanum_Polar(rotation, degrees, magnitude) may be the right passing of parameters
			screen->PrintfLine(DriverStationLCD::kUser_Line1,"Magnitude: %f", magnitude);
			screen->PrintfLine(DriverStationLCD::kUser_Line2,"Degrees: %f", direction);	
			screen->PrintfLine(DriverStationLCD::kUser_Line3,"Rotation: %f", stick.GetThrottle());	// wait for a motor update time
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

