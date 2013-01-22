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
	Jaguar driveLeft, driveRight, endGameLeftFront, endGameRightFront, endGameLeftBack, endGameRightBack, shooterFront, shooterBack;
	RobotDrive drive;
	Relay light;
	Servo pusher1, pusher2, feederLock;
	
public:
	RobotDemo(void):
		//Joysticks
		leftStick(1),
		rightStick(2),
		//Jaguars
		driveLeft(1),
		driveRight(2),
		endGameLeftFront(3), endGameRightFront(4), 
		endGameLeftBack(5), endGameRightBack(6),
		shooterFront(7),
		shooterBack(8),
		//Servos
		pusher1(2,1), pusher2(2,2),
		feederLock (2,3),
		//Light
		light(2,4),
		//Drive
		drive(1,2)
	{
		
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		//TODO:Autnomous code
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		
		while (IsOperatorControl())
		{
			drive.TankDrive(leftStick, rightStick);//tank drive for now, but we can change to fit drivers needs.
			//TODO:Shooter code - motor speeds and motor locks
			
			//TODO:End game code
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

