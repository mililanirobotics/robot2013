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
	Joystick leftstick, rightstick; // only joystick
	Jaguar driveleft, driveright;

public:
	RobotDemo(void):
		myRobot(1, 2),	// these must be initialized in the same order
		leftstick(1), rightstick(2),
		driveleft(1), driveright(2)// as they are declared above.
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
		float speed = 0;
		while (IsOperatorControl())
		{
			myRobot.TankDrive(leftstick, rightstick);
			driveleft.Set(1);
			driveright.Set(-1);
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

