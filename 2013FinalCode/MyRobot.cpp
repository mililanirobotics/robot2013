#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */
class RobotDemo : public SimpleRobot {
	Joystick leftStick, rightStick;
	Jaguar driveLeft, driveRight, endGameLeftFront, endGameRightFront,
			endGameLeftBack, endGameRightBack, shooterFront, shooterBack;
	RobotDrive drive;
	Relay light;
	Servo pusher1, pusher2, feederLock;
	AnalogChannel potFront, potBack;
	DigitalInput switchFront, switchBack;

public:
	RobotDemo(void) :
				//Joysticks
				leftStick(1),
				rightStick(2),
				//Jaguars
				driveLeft(1), driveRight(2), endGameLeftFront(3),
				endGameRightFront(4), endGameLeftBack(5), endGameRightBack(6),
				//Drive
				drive(1, 2),
				//Light
				light(2, 4, Relay::kForwardOnly),
				//Potentiometers
				potFront(1, 1), potBack(1, 2),
				//Switches
				switchFront(1,3) , switchBack(1,4)
	{

	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	bool ClawIsClosed()
	{
		return true; //REPLACE THIS BEFORE TESTING
	}
	void Autonomous(void) 
	{

	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void) 
	{
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		while (IsOperatorControl()) {
			light.Set(Relay::kOn);
			drive.TankDrive(leftStick, rightStick);//tank drive for now, but we can change to fit drivers needs.
			if (rightStick.GetRawButton(10)) //End game code
			{ 
				bool isAligned;
				//Pyramid allignment
				while (!isAligned) 
				{
					float targetx = 0;
					float distance = 0;  //TODO: Distance algorithm
					//TODO: Get x value from NIVision or RoboRealm
					
					//This code assumes that center of target is located at 100. (TODO: Get actual middle values and replace 100)

					if (targetx < 150) { //+-10 error margin
						//TODO: Math for the allignment algorithm
					} else if (targetx > 170) {
						//TODO: Math for the allignment algorithm
					} else {
						isAligned = true;
					}
				}
				while (potFront.GetVoltage() < (10/3) || switchFront.Get() < 1) { // 10/3 comes from 5(voltage)/270(degrees total)*180 degrees we need to move

				//TODO: Tell the driver that the robot is aligned
				}
			}
			
			//TODO: Find out some way to figure out when the claw is closed - possibly a switch?
			if (ClawIsClosed())  //PSUEDOCODE - are we going to use a switch or not?
			{
				while (potFront.GetVoltage() < (10/3)) { // 10/3 comes from 5(voltage)/270(degrees total)*180 degrees we need to move
						
					endGameLeftFront.Set(1);
					endGameRightFront.Set(1);
				}
				endGameLeftFront.Set(0);
				endGameRightFront.Set(1);
				while (potBack.GetVoltage() < (10/3) || switchBack.Get() < 1) {
					endGameLeftBack.Set(1);
					endGameRightBack.Set(1);
				}
				endGameLeftBack.Set(0);
				endGameRightBack.Set(0);
				//TODO: Repeat this code for the number of times we are going to move the arms
			//}
			}
		}
	
		
	}
	
};

START_ROBOT_CLASS(RobotDemo);
