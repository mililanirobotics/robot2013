#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	DigitalInput s1, s2, s3, s4

public:
	RobotDemo(void):

		jFL(5), jRL(6), jFR(3), jRR(4),
		stick(1),
		spike(2, Relay::kForwardOnly) 
	{
	}
	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		//myRobot.SetSafetyEnabled(false);
		//myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed				//    for 2 seconds
		//myRobot.Drive(0.0, 0.0); 	// stop robot
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	/*void RobotDrive::MecanumDrive_Cartesian (float x,  
										float d,
										float rotation); */
	
	
	void OperatorControl(void)
	
	{
		//myRobot.SetSafetyEnabled(true);
		//myRobot.MecanumDrive_Cartesian( x, y, rotation);
		while (IsOperatorControl())
		{
			//myRobot.ArcadeDrive(stick); // drive with arcade style (use right stick)
			if(stick.GetRawButton(1))
				vic.Set(stick.GetY());
			else
				vic.Set(0);// wait for a motor update time
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);
