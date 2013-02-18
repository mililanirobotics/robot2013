#include "WPILib.h"

class RobotDemo : public SimpleRobot
{ // robot drive system
	Gyro gyro;
	Victor jFL, jRL, jFR, jRR;
	Joystick stick; // only joystick
	//DigitalInput s1;
public:
	RobotDemo(void):
		gyro(1),
		jFL(1), jRL(2), jFR(3), jRR(4),// these must be initialized in the same order
		stick(1)		// as they are declared above.
		//s1(1)
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
	float mod(float n1, float n2) {
		while (n1 >= n2) {
			n1 -= n2;
		}
		return n1;
	}
	void OperatorControl(void)
	{
		bool calibrate;
		//bool kill = false;
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		//gyro.Reset();
		//gyro.SetSensitivity(0.031915);
		bool robotIsNotMoving;
		float gyroAngle; //current angle of the gyro
		float prevAngle = 0; //angle of the gyro the last time it was stationary
		
		//speed going forward, right, & clockwise
		float forward;
		float right;
		float clockwise;
		
		//number of times robot has been stationary
		int stationaryCount = 0;
		
		//speed of each mecanum wheel
		float front_left;
		float front_right; 
		float rear_left; 
		float rear_right;
		
		float max;
		
		while (IsOperatorControl())
		{
			//Extreme 3D Pro Settings
			forward   = -stick.GetY();  // push joystick forward to go forward 
			right     = -stick.GetX();  // push joystick to the right to strafe right 
			clockwise =  stick.GetZ()*3/4;  // twist joystick clockwise turn clockwise
			
			// Logitech settings
//			float forward = -stick.GetY();
//			float right = -stick.GetX();
//			float clockwise = stick.GetThrottle();
			if (absolute(stick.GetZ()>.7))
			{
				if (stick.GetZ()>0)
					clockwise = 0.7;
				if (stick.GetZ()<0)
					clockwise = -0.7;
			}
			if (absolute(stick.GetZ()) < 0.15)
			{
				clockwise = 0;
			}
			
			if (absolute(stick.GetX()) < .7)
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
			if (absolute(stick.GetY()) < .3)
			{
				forward = 0;
			}
//			if (!stick.GetRawButton(1))
//			{
//				clockwise = 0;
//			}
//			if (s1.Get() == 1){
//				kill = true;
//			}
//			if (stick.GetRawButton(9)){
//				kill = false;
//				screen->PrintfLine(DriverStationLCD::kUser_Line1, "");
//				screen->UpdateLCD();
//			}
//			if(kill)
//			{
//				screen->PrintfLine(DriverStationLCD::kUser_Line1, "HIT!");
//				forward = 0;
//				clockwise = 0;
//				right = 0;
//			}
			front_left  = forward - clockwise + right; 
			front_right = forward + clockwise - right; 
			rear_left   = forward - clockwise - right; 
			rear_right  = forward + clockwise + right;

			max = absolute(front_left);  //This part finds the largest value in the drive and checks if it is larger than 1 or smaller than -1
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
			{ //Jaguar Sets values range only from -1 to 1
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
			
			gyroAngle = (mod(gyro.GetAngle() + 3600, 90));
			screen->PrintfLine(DriverStationLCD::kUser_Line1, "Angle: %f", gyroAngle);
			robotIsNotMoving = ((absolute(forward*10)<.1)&&(absolute(clockwise*10)<.1)&&(absolute(right*10)<.1));
			if (robotIsNotMoving)
			{
				prevAngle = gyro.GetAngle();
				gyro.Reset();
//				while (stick.GetRawButton(7))
//				{
//					calibrate = true;
//					screen->PrintfLine(DriverStationLCD::kUser_Line4, "Calibrating");
//				}
//				if (calibrate)
//				{
//					if(!(absolute(gyro.GetAngle())<1))
//					{
//						Wait(0.2);
//						prevAngle = gyro.GetAngle();
//						Wait(0.2);
//						gyro.Reset();
//						stationaryCount++;
//						screen->PrintfLine(DriverStationLCD::kUser_Line2, "Previous Angle: %f", mod(prevAngle + gyro.GetAngle() + 3600, 90));
//					}
//					else
//					{
//						gyro.Reset();
//						screen->PrintfLine(DriverStationLCD::kUser_Line2, "Previous Angle: %f", mod(prevAngle + 3600, 90));
//					}
//					calibrate = false;
//					
//				}
				screen->PrintfLine(DriverStationLCD::kUser_Line4, "Not Calibrating");
	
			}
			//checks whether robot is moving or not
//			robotIsNotMoving = ((absolute(forward*10)<.1)&&(absolute(clockwise*10)<.1)&&(absolute(right*10)<.1));
//			if (robotIsNotMoving)
//			{
//				screen->PrintfLine(DriverStationLCD::kUser_Line6, "ROBOT IS NOT MOVING");
//				if(stick.GetRawButton(7))
//				{
//					//stores the angle of the gyro, reset the gyro & adds to stationaryCount
//					if(!(absolute(gyro.GetAngle())<1))
//					{
//					Wait(0.2);
//					prevAngle = gyro.GetAngle();
//					Wait(0.2);
//					gyro.Reset();
//					stationaryCount++;
//					screen->PrintfLine(DriverStationLCD::kUser_Line2, "Previous Angle: %f", mod(prevAngle + gyro.GetAngle() + 3600, 90));
//					}
//					else
//					{
//						gyro.Reset();
//						screen->PrintfLine(DriverStationLCD::kUser_Line2, "Previous Angle: %f", mod(prevAngle + 3600, 90));
//					}
//				}
//			}
//			else
//				screen->PrintfLine(DriverStationLCD::kUser_Line6, "ROBOT IS MOVING");
			
			screen->PrintfLine(DriverStationLCD::kUser_Line3, "F: %.5f, C: %5f", forward, clockwise);
			//screen->PrintfLine(DriverStationLCD::kUser_Line4, "S: %.5f, A: %5f", right, stick.GetRawAxis(5));
			screen->PrintfLine(DriverStationLCD::kUser_Line5, "A: %.5f, C:%i", prevAngle, stationaryCount);
			
			screen->UpdateLCD();

		}
	}

	/**
	 * Runs during Test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

