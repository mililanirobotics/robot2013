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
	Joystick stick; // only joystick
	
	/* motors pl0x */
	Jaguar fL, fR, rL, rR;
	
	float wheelFL;
	float wheelFR;
	float wheelBL;
	float wheelBR;	

public:
	RobotDemo(void):
		
		/* motors pl0x */
		
		myRobot(1, 2, 3, 4),
		fL(1), fR(2), rL(3), rR(4),// these must be initialized in the same order
		stick(1)		// as they are declared above.
	{
		//myRobot.SetExpiration(0.1);
	}

	
	void verticalDrive (float speed)
	{
		wheelFL += speed;
		wheelFR += speed;
		wheelBL += speed;
		wheelBR += speed;
	}
	void horizontalDrive (float speed)
	{
		wheelFL -= speed;
		wheelFR += speed;
		wheelBL += speed;
		wheelBR -= speed;
	}
	void rotationDrive (float speed)
	{
		wheelFL += speed;
		wheelFR -= speed;
		wheelBL += speed;
		wheelBR -= speed;
	}
	
	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{

	}


	void OperatorControl(void)
	{
		wheelFL = 0;
		wheelFR = 0;
		wheelBL = 0;
		wheelBR = 0;	
		
		myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl())
		{
			wheelFL = 0;
			wheelFR = 0;
			wheelBL = 0;
			wheelBR = 0;	
			verticalDrive(stick.GetY());
			horizontalDrive(stick.GetX());
			rotationDrive(stick.GetTwist()); 
		
			fL.set(wheelFL); //replace with real motor
			fR.set(wheelFR); //replace with real motor
			rL.set(wheelBL); //replace with real motor
			rR.set(wheelBR); //replace with real motor */
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

  
