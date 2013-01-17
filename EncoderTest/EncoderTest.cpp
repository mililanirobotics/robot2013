#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{

	Encoder encoder;
	

public:
	RobotDemo(void):
		encoder(1, 1)
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
		double encodervalue;
		double encoderdegree;
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		encoder.Start();
		encoder.Reset(); 
		while (IsOperatorControl())
		{
			encodervalue = encoder.GetRaw();
			encoderdegree = encodervalue*0.36;
			screen->PrintfLine(DriverStationLCD::kUser_Line1,"Degree %d", encoderdegree);
			screen->PrintfLine(DriverStationLCD::kUser_Line2,"Value %d", encodervalue);
			screen->UpdateLCD();
			Wait(0.005);				// wait for a motor update time
		}
		encoder.Stop();	
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);
