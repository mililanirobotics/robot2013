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
	Jaguar jFL, jRL, jFR, jRR;
	Joystick stick; // only joystick
public:
	RobotDemo(void):
		myRobot(1, 2),
		jFL(1), jRL(2), jfR(3), jRR(4),// these must be initialized in the same order
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
		while (IsOperatorControl())
		{
			float forward   = -stick.GetYAxis();  // push joystick forward to go forward 
			float right     =  stick.GetXAxis();  // push joystick to the right to strafe right 
			float clockwise =  stick.GetThrottle();  // twist joystick clockwise turn clockwise
			float front_left  = forward + clockwise + right 
			float front_right = forward - clockwise - right; 
			float rear_left   = forward + clockwise - right; 
			float rear_right  = forward - clockwise + right;
			
			max = abs(front_left);  //This part finds the largest value in the drive and checks if it is larger than 1 or smaller than -1
			if (abs(front_right)> max){
				max = abs(front_right); 
			}
			if (abs(rear_left)> max){
				max=abs(rear_left); 
			}
			if (abs(rear_right)> max){
				max=abs(rear_right);
			}						
			if (max>1){				//If it is, normalize all values by dividing by the highest value.
				front_left/=max;
				front_right/=max;
				rear_left/=max;
				rear_right/=max;
			}
			jFL.Set(front_left);
			jFR.Set(front_right);
			jRL.Set(rear_left);
			jRR.Set(rear_right);
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

