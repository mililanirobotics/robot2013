#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	Joystick leftstick;
	Servo servo;

public:
	RobotDemo(void):
		leftstick(1),servo(3)  
	{
		
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
	
		Wait(2.0); 				//    for 2 seconds
		
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		while (IsOperatorControl()) {
			if(leftstick.GetRawButton(1)){
				servo.Set(1.0);
			}
			if(leftstick.GetRawButton(2)){
				servo.Set(0.0);
			}
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

