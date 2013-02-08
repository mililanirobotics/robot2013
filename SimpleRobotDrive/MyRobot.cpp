#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	//RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick
	Jaguar j1;
	Jaguar j2;
	Jaguar j3;
	Jaguar j4;
	

public:
	RobotDemo(void):
		//myRobot(1, 2),	// these must be initialized in the same order
		stick(1),		// as they are declared above.
		j1(1),j2(2),j3(3),j4(4)
	{
		//myRobot.SetExpiration(0.1);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		/*myRobot.SetSafetyEnabled(false);
		myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
		Wait(2.0); 				//    for 2 seconds
		myRobot.Drive(0.0, 0.0); 	// stop robot*/
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		float mag;
		//myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl())
		{
			mag = stick.GetX() + stick.GetY();
			if (mag < 0)
				mag = -mag;
			if(stick.GetX() + stick.GetY() > 1 || stick.GetX() + stick.GetY() < -1)
			{
				j1.Set(-stick.GetX()/mag+stick.GetY()/mag);
				j2.Set(-stick.GetX()/mag-stick.GetY()/mag);
				j3.Set(stick.GetX()/mag+stick.GetY()/mag);
				j4.Set(stick.GetX()/mag-stick.GetY()/mag);

			}
			else
			{
				j1.Set(-stick.GetX()+stick.GetY());
				j2.Set(-stick.GetX()-stick.GetY());
				j3.Set(stick.GetX()+stick.GetY());
				j4.Set(stick.GetX()-stick.GetY());
			}
			if (stick.GetThrottle() < -0.5 || stick.GetThrottle() > 0.5)
			{
				j1.Set(stick.GetThrottle());
				j2.Set(stick.GetThrottle());
				j3.Set(stick.GetThrottle());
				j4.Set(stick.GetThrottle());
			}
			j1.Set(0.0);
			j2.Set(0.0);
			j3.Set(0.0);
			j4.Set(0.0);
			screen->PrintfLine(DriverStationLCD::kUser_Line1,"X: %.3f, Y: %.3f", stick.GetX(), stick.GetY());	
			screen->PrintfLine(DriverStationLCD::kUser_Line2,"Mag: %f", mag);	// wait for a motor update time
			screen->PrintfLine(DriverStationLCD::kUser_Line3,"Throttle: %f", stick.GetThrottle());
			screen->PrintfLine(DriverStationLCD::kUser_Line5,"J1 %.3f, J2 %.3f", j1.Get(), j2.Get());
			screen->PrintfLine(DriverStationLCD::kUser_Line5,"J3 %.3f, J4 %.3f", j3.Get(), j4.Get());
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

