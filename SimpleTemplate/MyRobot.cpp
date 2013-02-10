#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	Joystick leftStick, rightStick;
	Victor driveFrontLeft, driveFrontRight, driveRearLeft, driveRearRight, Dumper;
	Jaguar endGameLeftFront, endGameRightFront, endGameLeftBack, endGameRightBack;
	//RobotDrive drive;
	Relay light;
	Servo dumpLock;
	//AnalogChannel potFront, potBack;

public:
	RobotDemo(void):
		leftStick (1), rightStick(2),
		driveFrontLeft(1), driveRearLeft(2), driveFrontRight(3), driveRearRight(4),
		endGameLeftFront(5),endGameRightFront(6),endGameLeftBack(7),endGameRightBack(8),
		light(1), dumpLock(9)
	{
		myRobot.SetExpiration(0.1);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		//myRobot.SetSafetyEnabled(false);
		myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
		Wait(2.0); 				//    for 2 seconds
		myRobot.Drive(0.0, 0.0); 	// stop robot
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	/*void RobotDrive::MecanumDrive_Cartesian (float x,  
										float d,
										float rotation); */
	
	
	void OperatorControl(void)
	
	{
		//myRobot.SetSafetyEnabled(true);
		//myRobot.MecanumDrive_Cartesian( x, y, rotation);
		while (IsOperatorControl())
		{
			//myRobot.ArcadeDrive(stick); // drive with arcade style (use right stick)
			myRobot.MecanumDrive_Cartesian(stick.GetX(), stick.GetY(), stick.GetThrottle());
			
		
			Wait(0.005);				// wait for a motor update time
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);
