#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	Joystick stick;
	Relay spike;
	
	//Servo door;
public:
	//NetworkTable *netTable;
	RobotDemo(void):
	stick(1),
	spike(1, Relay::kForwardOnly)//,door(1)
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
	//	bool closed = true;
		while (IsOperatorControl())
		{
			if (stick.GetRawButton(1))
			{
				spike.Set(Relay::kOn);
			}
		}
//			if (stick.GetRawButton(2)){
//				if (closed){
//					door.Set(0);
//					closed = false;
//				}
//				else{
//					door.Set(1);
//					closed = true;
//				}
//			}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

