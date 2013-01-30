#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
using namespace std;
class RobotDemo : public SimpleRobot
{
	Joystick stick;
	Servo servo;
public:
	NetworkTable *netTable;
	RobotDemo(void):
	stick(1),
	servo(1)
	{
		NetworkTable::SetServerMode();
		NetworkTable::Initialize();
		netTable = NetworkTable::GetTable("SmartDashboard");
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
		servo.Set(stick.GetThrottle());
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		double xpos = 0;
		
		//double ypos = 0;
		servo.Set(0);
		while (IsOperatorControl())
		{
			//servo.Set((stick.GetTwist()+1)/2);
			try{
			xpos = netTable->GetNumber("Slider 1", 1);
			screen->PrintfLine(DriverStationLCD::kUser_Line2, "%d", xpos);
			//screen->PrintfLine(DriverStationLCD::kUser_Line1,(char*)xpos.c_str());  FOR STRINGS
			}
			catch (...)
			{
				screen->PrintfLine(DriverStationLCD::kUser_Line2,"ERROR OCCOURED!");
			}
			screen->UpdateLCD();
//			ypos = netTable->GetNumber("OBJECT_Y_COORD");
//			screen->PrintfLine(DriverStationLCD::kUser_Line2, (char*)xpos.c_str());
//			screen->UpdateLCD();
//			if (xpos > 167)
//			{
//				servo.Set(servo.Get() + .02);
//			}
//			if (xpos < 153)
//			{
//				servo.Set(servo.Get() - .02);
//			}
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

