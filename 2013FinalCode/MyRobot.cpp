#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */
class RobotDemo : public SimpleRobot {
	Joystick leftStick, rightStick;
	Victor driveFrontLeft, driveFrontRight, driveRearLeft, driveRearRight, Dumper;
	Jaguar endGameLeftFront, endGameRightFront, endGameLeftBack, endGameRightBack;
	Relay light;
	Servo dumpLock;
	AnalogChannel potFront, potBack;

public:
	RobotDemo(void) :
				//Joysticks
				leftStick(1),
				rightStick(2),
				//Jaguars
				driveFrontLeft(1), driveFrontRight(2), driveRearLeft(3), driveRearRight(4), endGameLeftFront(5),
				endGameRightFront(6), endGameLeftBack(7), endGameRightBack(8), Dumper(9),
				//Drive
				drive(1, 2, 3, 4),
				//Light
				light(1, 4, Relay::kForwardOnly),
				//Servos
				dumpLock(10),
				//Potentiometers
				potFront(1, 1), potBack(1, 2)
	{

	}

	void Autonomous(void) 
	{

	}
	
	float absolute(float number){
			if (number<0){
				number = -number;
			}
			return number;
	}	
	
	void MecanumDrive (float forward, float right, float clockwise){
		//float forward   = -stick.GetY();  // push joystick forward to go forward 
		//			float right     = -stick.GetX();  // push joystick to the right to strafe right 
		//			float clockwise =  stick.GetThrottle();  // twist joystick clockwise turn clockwise
					if (absolute(right) < .3)
						right = 0;
					else if(absolute(right) < .9)
					{
						if (right > 0)
							right = -0.9;
						else
							right = 0.9;
					}
					if (absolute(forward()) < .118)
					{
						forward = 0;
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
					driveFrontLeft.Set(front_left);
					driveFrontRight.Set(-front_right);
					driveRearLeft.Set(rear_left);
					driveRearRight.Set(-rear_right);
					//adjusted for polarity changes
		//			screen->PrintfLine(DriverStationLCD::kUser_Line1,"FL %.3f, RL %.3f", front_left, rear_left);
		//			screen->PrintfLine(DriverStationLCD::kUser_Line2,"FR %.3f, RR %.3f", front_right, rear_right);
		//			screen->PrintfLine(DriverStationLCD::kUser_Line3,"X %.3f, Y %.3f", stick.GetX(), stick.GetY());
		//			screen->PrintfLine(DriverStationLCD::kUser_Line4,"Throttle: %.3f", stick.GetThrottle());
		//			screen->PrintfLine(DriverStationLCD::kUser_Line5,"J1 %.3f, J2 %.3f", jFL.Get(), jRL.Get());
		//			screen->PrintfLine(DriverStationLCD::kUser_Line6,"J3 %.3f, J4 %.3f", jFR.Get(), jRR.Get());
		//			screen->UpdateLCD();
	}
	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void) 
	{
	//	DriverStationLCD *screen = DriverStationLCD::GetInstance(); UNUSED
		while (IsOperatorControl()) {
			light.Set(Relay::kOn);
			MechanumDrive();
			if (rightStick.GetRawButton(10)) //End game code
			{ 
				bool isAligned;
				//Pyramid allignment
				while (!isAligned) 
				{
					//Make sure the variable is called Pyramid!
					float targetx = SmartDashboard::GetNumber("Pyramid");
					Sleep(5);				
					//This code assumes that center of target is located at 160 (pixels).					
					if (targetx < 150) { //+-10 error margin
						//TODO: Move left
					} else if (targetx > 170) {
						//TODO: Move right 
					} else {
						isAligned = true;
					}
				}
				delete isAligned;

				//TODO: Tell the driver that the robot is aligned

			}
			if (rightStick.GetRawButton(11))
			{
				while (potFront.GetVoltage() < (10/3)) { // 10/3 comes from 5(voltage)/270(degrees total)*180 degrees we need to move
				//TODO: Change this to the actual turn amounts

					endGameLeftFront.Set(1);
					endGameRightFront.Set(1);
				}
				endGameLeftFront.Set(0);
				endGameRightFront.Set(0);

				while (potBack.GetVoltage() < (10/3)) {
					endGameLeftBack.Set(1);
					endGameRightBack.Set(1);
				}
				endGameLeftBack.Set(0);
				endGameRightBack.Set(0);


				//TODO: Repeat this code for the number of times we are going to move the arms

			}
		}


	}

};

START_ROBOT_CLASS(RobotDemo);
