#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{ // robot drive system
	Victor jFL, jRL, jFR, jRR;
	Joystick stick; // only joystick
	DigitalInput s1;
public:
	RobotDemo(void):
		jFL(5), jRL(6), jFR(3), jRR(4),// these must be initialized in the same order
		stick(1)		// as they are declared above.
		,s1(1)
		//,s1(2), s2(3)
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
	float absolute(float number){
		if (number<0){
			number = -number;
		}
		return number;
	}
	void OperatorControl(void)
	{
		bool kill = false;
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		while (IsOperatorControl())
		{
			//Extreme 3D Pro Settings
			float forward   = -stick.GetY();  // push joystick forward to go forward 
			float right     = -stick.GetX();  // push joystick to the right to strafe right 
			float clockwise =  stick.GetThrottle();  // twist joystick clockwise turn clockwise
			
			// Logitech settings
//			float forward = -stick.GetY();
//			float right = -stick.GetX();
//			float clockwise = stick.GetThrottle();
			if (absolute(stick.GetThrottle()) < 0.15)
			{
				clockwise = 0;
			}
			
			if (absolute(stick.GetX()) < .3)
				right = 0;
			else if(absolute(stick.GetX()) < .9)
			{
				if (stick.GetX() > 0)
					right = -0.9;
				else
					right = 0.9;
			}
			else
				right = -stick.GetX();
			if (absolute(stick.GetY()) < .118)
			{
				forward = 0;
			}
			if (absolute(stick.GetThrottle()) < 0.15)
			{
				clockwise = 0;
			}
			if (!stick.GetRawButton(1))
			{
				clockwise = 0;
			}
			float front_left  = forward - clockwise + right; 
			float front_right = forward + clockwise - right; 
			float rear_left   = forward - clockwise - right; 
			float rear_right  = forward + clockwise + right;

			float max = absolute(front_left);  //This part finds the largest value in the drive and checks if it is larger than 1 or smaller than -1
			if (absolute(front_right)> max){
				max = absolute(front_right); 
			}
			if (absolute(rear_left)> max){
				max=absolute(rear_left); 
			}
			if (absolute(rear_right)> max){
				max=absolute(rear_right);
			}						
			if (max>1)//If it is, normalize all values by dividing by the highest value, maintaining the ratio.
			{ //Jaguar Sets values range only form -1 to 1
				front_left=front_left/max;
				front_right=front_right/max;
				rear_left=rear_left/max;
				rear_right=rear_right/max;
			}
			jFL.Set(front_left);
			jFR.Set(-front_right);
			jRL.Set(rear_left);
			jRR.Set(-rear_right);
			if (s1.Get() == 1){
				kill = true;
			}
			if (stick.GetRawButton(9)){
				kill = false;
			}
			while(kill)
			{
				jFL.Set(0);
				jFR.Set(0);
				jRL.Set(0);
				jRR.Set(0);
			}
			//adjusted for polarity changes
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

