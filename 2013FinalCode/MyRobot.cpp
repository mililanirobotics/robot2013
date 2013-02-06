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
				shooterFront(7), shooterBack(8),
				//Drive
				drive(1, 2),
				//Light
				light(2, 4, Relay::kForwardOnly),
				//Servos
				pusher1(2, 1), pusher2(2, 2), feederLock(2, 3),
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
		//TODO:Autnomous code
		light.Set(Relay::kOn);
		bool isAligned;
		//Pyramid allignment
		while (!isAligned) 
		{
		//	float targety = 0; UNUSED
			float targetx = 0;
		//	float distance = 0; UNUSED
			//TODO: Get x and y values from NIVision or RoboRealm

			//This code assumes that center of target is located at 100.
			//TODO: Get actual middle values and replace 100

			if (targetx < 98) { //+-2 error margin
				//TODO: Math for the allignment algorithm
			} else if (targetx > 102) {
				//TODO: Math for the allignment algorithm
			} else {
				isAligned = true;
			}

			for (int x = 0; x<3; x++) 
			{  //This code repeats 3 times to shoot all three disks
				shooterBack.Set(1);
				shooterFront.Set(1);
				Wait(1.5); //Gives jags a chance to spin up  (TODO: find actual spin up time)
				pusher1.Set(1);
				pusher2.Set(1);
				Wait(1); //Shoots the disk
				shooterBack.Set(0);
				shooterFront.Set(0);
				pusher1.Set(0);
				pusher2.Set(0);
				Wait(1);
				feederLock.Set(1);
				Wait(1);
				feederLock.Set(0);
			}
		}

	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void) 
	{
	//	DriverStationLCD *screen = DriverStationLCD::GetInstance(); UNUSED
		while (IsOperatorControl()) {
			light.Set(Relay::kOn);
			drive.TankDrive(leftStick, rightStick);//tank drive for now, but we can change to fit drivers needs.
			if (rightStick.GetRawButton(1)) 
			{
				shooterBack.Set(1);
				shooterFront.Set(1);
				Wait(1.5); //Gives jags a chance to spin up
				pusher1.Set(1);
				pusher2.Set(1);
				Wait(1); //Shoots the disk
				pusher1.Set(0);
				pusher2.Set(0);
				shooterBack.Set(0);
				shooterFront.Set(0);
				Wait(1);
				feederLock.Set(1);
				Wait(1);
				feederLock.Set(0);
				//Do we want to put this in a for loop and fire all 4 disks, or shoot individual disks?
			}
			if (rightStick.GetRawButton(10)) //End game code
			{ 
				bool isAligned;
				//Pyramid allignment
				while (!isAligned) 
				{
				//	float targety = 0; UNUSED
					float targetx = 0;
				//	float distance = 0; UNUSED
					//TODO: Get x and y values from NIVision or RoboRealm
					//This code assumes that center of target is located at 100. (TODO: Get actual middle values and replace 100)

					if (targetx < 98) { //+-2 error margin
						//TODO: Math for the allignment algorithm
					} else if (targetx > 102) {
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
			if (ClawIsClosed())
			{
				while (potFront.GetVoltage() < (10/3)) { // 10/3 comes from 5(voltage)/270(degrees total)*180 degrees we need to move
//>>>>>>> origin/master //what the ellhay is this supposed to do???
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
			}
		}
	
		
	}
	
};

START_ROBOT_CLASS(RobotDemo);

