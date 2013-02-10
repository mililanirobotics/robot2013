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
	RobotDrive drive;
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

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void) 
	{
	//	DriverStationLCD *screen = DriverStationLCD::GetInstance(); UNUSED
		while (IsOperatorControl()) {
			light.Set(Relay::kOn);
			drive.TankDrive(leftStick, rightStick);//Need to change to Mechanum.
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
