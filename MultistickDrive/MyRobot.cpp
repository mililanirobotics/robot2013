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
	
	
public:
	RobotDemo(void):
		//myRobot(1, 2),	// these must be initialized in the same order
		stick (1)
	{
		//myRobot.SetExpiration(0.1);
	}
	
	
	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	float* Xbox(void) {
		float *object = new float [3];
		object[0] = stick.GetY();
		object[1] = stick.GetTwist();
		return object;
	}
	
	float* Logitech(void){
		float *object = new float [2];
		object[0] = stick.GetY();
		object[1] = stick.GetX();
		return object;
	}
	
	float* Standard(void){
		float *object = new float [2];
		object[0] = stick.GetY();
		object[1] = stick.GetX();
		return object;
	}
	
	void Autonomous(void)
	{
		//myRobot.SetSafetyEnabled(false);
		//myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
		//Wait(2.0); 				//    for 2 seconds
		//myRobot.Drive(0.0, 0.0); 	// stop robot
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
	DriverStationLCD *screen = DriverStationLCD::GetInstance();
		while (IsOperatorControl())
		{
		float *object = new float[2];
		//object = Xbox();
		object = Logitech();
		//object = Standard();
		screen->PrintfLine(DriverStationLCD::kUser_Line1,"Direction %f",object[0] );
		screen->PrintfLine(DriverStationLCD::kUser_Line2,"Throttle %f",object[1] );	
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

