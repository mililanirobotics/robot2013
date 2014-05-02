#include "WPILib.h"
#include <math.h>
//#include "ArrayData.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */
class RobotDemo: public SimpleRobot {
	Victor jFL, jRL, jFR, jRR;
	Joystick stick; // only joystick
	Relay spike;
	Gyro gyro;
	DigitalInput mswitch;
public:
	//NetworkTable *netTable;
	RobotDemo(void) :
		jFL(5), jRL(6), jFR(3), jRR(4), stick(1),
				spike(2, Relay::kForwardOnly), gyro(1), mswitch(1) {
	}

	void Autonomous(void) {

	}

	float absolute(float number) {
		if (number < 0) {
			number = -number;
		}
		return number;
	}
	float mod(float n1, float n2) {
		while (n1 > n2) {
			n1 = n1 - n2;
		}
		return n1;
	}
	void OperatorControl(void) {
		double x1 = 1;
		double x2 = 2;
		double y1 = 3;
		double y2 = 4;
		bool isLocked = false;
		double cx = 0;
		double angle = 0;
		float forward;
		float right;
		float clockwise;
		//float diff;
		float front_left;
		float front_right;
		float rear_left;
		float rear_right;
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		spike.Set(Relay::kOff);
		gyro.Reset();
		while (IsOperatorControl()) {

			//spike.Set(Relay::kOn);
			if (mswitch.Get() == 0)
				screen->PrintfLine(DriverStationLCD::kUser_Line2, "Off");
			else
				screen->PrintfLine(DriverStationLCD::kUser_Line2, "On");
//			x1 = SmartDashboard::GetNumber("X1");
//			x2 = SmartDashboard::GetNumber("X2");
//			cx = x1 / 2 + x2 / 2;
//			if (cx == 0)
//				right = 0;
//			else if((cx>150) && (cx<170))
//				right = 0;
//			else if((cx<150))
//				right = -0.8;
//			else if((cx>170))
//				right = 0.8;
//			else{}
//			angle = atan((y1 - y2) / (x1 - x2));
//			angle = angle * 180 / 3.14159265359;
//			if (angle < 0) {
//				angle = 180 + angle;
//			}

			//angle = SmartDashboard::GetNumber("Angle");
			screen->PrintfLine(DriverStationLCD::kUser_Line1, "Angle Toggle: " + isLocked);
			screen->PrintfLine(DriverStationLCD::kUser_Line5, "Imperfection!");
			screen->PrintfLine(DriverStationLCD::kUser_Line6, "X: %.3f", cx);
			forward = -stick.GetY(); // push joystick forward to go forward 
			right = -stick.GetX(); // push joystick to the right to strafe right 
			clockwise = stick.GetThrottle(); // twist joystick clockwise turn clockwise


			if (absolute(stick.GetX()) < .3) {
				right = 0;
			} else if (absolute(stick.GetX()) < .9) {
				if (stick.GetX() > 0)
					right = -0.9;
				else
					right = 0.9;
			} else
				right = -stick.GetX();

			if (absolute(stick.GetY()) < .118) {
				forward = 0;
			}
			if (absolute(stick.GetThrottle()) < 0.15) {
				clockwise = 0;
			}
			//			if (!stick.GetRawButton(1)) {
			//				clockwise = 0;
			//			}

//						if (stick.GetRawButton(9)) {
//							if (angle == 0) {
//							} else if ((angle > 86) && angle < 94) //if pixels are perfect, move forward
//							{
//								screen->PrintfLine(DriverStationLCD::kUser_Line5,
//										"PERFECTION!");
//								//forward = 0.2;
//							} else if (angle < 70)//if pixels are too far left, rotate left
//							{
//								right = 0.9;
//							} else if (angle > 110)//if pixels are too far right, rotate right
//							{
//								right = -0.9;
//							} else if (angle > 94 && angle < 110) //if pixels are small kine left, rotate small kine left
//							{
//								right = -0.7;
//							} else if (angle > 70 && angle < 86) //if pixels are small kine right, rotate small kine right
//							{
//								right = 0.7;
//							} else {
//							}
//						}

			float theta = (mod(gyro.GetAngle() + 360, 90));
			if (stick.GetRawButton(12)) {
				isLocked = !isLocked;
				Wait(0.020);
			}
				if (isLocked) {
					if ((theta) - 45 > 1) {
						clockwise = -(.00889 * absolute(theta - 45) + .3);
						screen->PrintfLine(DriverStationLCD::kUser_Line4,
								"A: %.3f", theta);
					} else if ((theta) - 45 < -1) {
						clockwise = (.00889 * absolute(theta - 45) + .3);
						screen->PrintfLine(DriverStationLCD::kUser_Line4,
								"A: %.3f", theta);
					} else {
						screen->PrintfLine(DriverStationLCD::kUser_Line4,
								"PERFECT %f", theta);
						clockwise = 0;
					}
				}
			
				//screen->PrintfLine(DriverStationLCD::kUser_Line4, "A: %.3f, S: %.3f", theta, clockwise);

				front_left = forward - clockwise + right;
				front_right = forward + clockwise - right;
				rear_left = forward - clockwise - right;
				rear_right = forward + clockwise + right;

				float max = absolute(front_left); //This part finds the largest value in the drive and checks if it is larger than 1 or smaller than -1
				if (absolute(front_right) > max) {
					max = absolute(front_right);
				}
				if (absolute(rear_left) > max) {
					max = absolute(rear_left);
				}
				if (absolute(rear_right) > max) {
					max = absolute(rear_right);
				}
				if (max > 1)//If it is, normalize all values by dividing by the highest value, maintaining the ratio.
				{ //Jaguar Sets values range only form -1 to 1
					front_left = front_left / max;
					front_right = front_right / max;
					rear_left = rear_left / max;
					rear_right = rear_right / max;
				}
				//avex = 180 - x1/2 - x2/2;


				/*if(stick.GetRawButton(9))
				 {
				 if (avex = 0)
				 {}
				 else if ((avex < 190) && avex > 170) //if pixels are perfect, move forward
				 {
				 //forward = 0.2;
				 }
				 else if (avex < 130)//if pixels are too far left, rotate left
				 {
				 right = 0.7;
				 }
				 else if (avex > 230)//if pixels are too far right, rotate right
				 {
				 right = -0.7;
				 }
				 else if (avex > 190 && avex < 230) //if pixels are small kine left, rotate small kine left
				 {
				 right = -0.9;
				 }
				 else if (avex > 130 && avex < 170) //if pixels are small kine right, rotate small kine right
				 {
				 right = 0.9;
				 }
				 else{}
				 }*/

				jFL.Set(front_left);
				jFR.Set(-front_right);
				jRL.Set(rear_left);
				jRR.Set(-rear_right);
				screen->UpdateLCD();
				

			}
		}

		/**
		 * Runs during test mode
		 */
		void Test() {

		}
	}
	;

	START_ROBOT_CLASS(RobotDemo)
	;

