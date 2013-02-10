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
public:
	RobotDemo(void):
		jFL(5), jRL(6), jFR(3), jRR(4),// these must be initialized in the same order
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
	float absolute(float number){
		if (number<0){
			number = -number;
		}
		return number;
	}
	void OperatorControl(void)
	{
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		bool capture = false;
		while (IsOperatorControl())
		{
			float forward   = -stick.GetY();  // push joystick forward to go forward 
			float right     = -stick.GetX();  // push joystick to the right to strafe right 
			float clockwise =  stick.GetThrottle();  // twist joystick clockwise turn clockwise
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
			if (stick.GetRawButton(2)){  //Button 2 triggers left only mode
					forward = 0;
			}
			if (!stick.GetRawButton(1))
			{
				clockwise = 0;
			}
			if (stick.GetRawButton(3)){
				right = -0.8;
				forward = 0;
			}
			if (stick.GetRawButton(4)){
				right = 0.8;
				forward = 0;
			}
			if (stick.GetRawButton(8) && capture){
				printf("FL = %.3f RL = %.3f FR = %.3f FR = %.3f \n", jFL.Get(), jRL.Get(), jFR.Get(), jRR.Get());
				printf("Forward = %.3f  Right = %.3f ", forward, right);
				printf("Clockwise = %.3f \n", clockwise);
				capture = false;
			}
			if (stick.GetRawButton(12)){
				capture = true;
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
			//adjusted for polarity changes
			screen->PrintfLine(DriverStationLCD::kUser_Line1,"FL %.3f, RL %.3f", front_left, rear_left);
			screen->PrintfLine(DriverStationLCD::kUser_Line2,"FR %.3f, RR %.3f", front_right, rear_right);
			screen->PrintfLine(DriverStationLCD::kUser_Line3,"X %.3f, Y %.3f", stick.GetX(), stick.GetY());
			screen->PrintfLine(DriverStationLCD::kUser_Line4,"Throttle: %.3f", stick.GetThrottle());
			screen->PrintfLine(DriverStationLCD::kUser_Line5,"J1 %.3f, J2 %.3f", jFL.Get(), jRL.Get());
			screen->PrintfLine(DriverStationLCD::kUser_Line6,"J3 %.3f, J4 %.3f", jFR.Get(), jRR.Get());
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

