#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	RobotDrive myRobot; // robot drive system
	Joystick stick; // Extreme3DPro
/*	Joystick stick2; //optional second stick */
	

public:
	RobotDemo(void):

	/*	stick2(2), */
		myRobot(1, 2),	// these must be initialized in the same order
		stick(1)		// as they are declared above.
	{
		//myRobot.SetExpiration(0.1);
	}

	
	void Autonomous(void)
	{

	}


	void OperatorControl(void)
	{
		
	//	DriverStationLCD *screen -> DriverStationLCD::GetInstance();
		
		while (IsOperatorControl())
		{
			/* Using the Extreme3DPro Joystick */
			myRobot.MecanumDrive_Cartesian(stick.GetY(), stick.GetX(), stick.GetTwist(), 0.0);
			/* Using two Joysticks */
// 	 	 	myRobot.MecanumDrive_Cartesian(stick.GetY(), stick.GetX(), stick2.GetX(), 0.0);
			/* Using an Xbox controller */
//			myRobot.MecanumDrive_Cartesian(stick.GetY(), stick.GetX(), stick.GetZ(), 0.0);

//			screen->PrintfLine(DriverStationLCD::kUser_Line1("FL: .3f%",wheelFL));
			
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

  
