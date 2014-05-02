#include "WPILib.h"
//#include "NetworkTables/NetworkTable.h"


/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */
class RobotDemo: public SimpleRobot {

	//Servo servo;
	//Joystick joy1;
	Victor jFL, jRL, jFR, jRR;
	Joystick stick; // only joystick
	Relay spike;
public:
	//NetworkTable *netTable;
	RobotDemo(void) :
		//joy1(1),
		jFL(5), jRL(6), jFR(3), jRR(4),
		stick(1),
		spike(2, Relay::kForwardOnly) {

	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void) {
		
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void) {
		spike.Set(Relay::kOn);
		int x = 0;
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		while (IsOperatorControl()) {
		spike.Set(Relay::kOn);
		
			//string xpos = "null";
		//	string xpos1 = "null";
			//You would not BELIEVE how much of a pain in the *** this was.
			//string key = "Disk";
		//	string key1 = "Disk L";
			//xpos = SmartDashboard::GetString(key);
		//	xpos1 = SmartDashboard::GetString(key1);
		//	float xposd1 = ::atof(xpos1.c_str());
			//float xposd = ::atof(xpos.c_str()); 
//			float dif = (xposd - xposd1);
//			if (dif < 0)
//				dif = -dif;
			
//			float dist = (-.002816358*dif*dif*dif + .29375*dif*dif -10.4194444*dif + 173.8);
//			float dist1 = (.0137841988*dif*dif + -1.709170854*dif + 89.83165829);
//			float dist2 = (-.7966010695*dif + 76.59322034);
//			screen->PrintfLine
			x++;
			screen->PrintfLine(DriverStationLCD::kUser_Line2, "Hella %i", x);
//			screen->PrintfLine(DriverStationLCD::kUser_Line3, "Difference: %f", (xposd-xposd1));
			//screen->PrintfLine(DriverStationLCD::kUser_Line4, "Cubic: %f", dist);
			//screen->PrintfLine(DriverStationLCD::kUser_Line5, "Quadratic: %f", dist1);
			//screen->PrintfLine(DriverStationLCD::kUser_Line6, "Linear: %f", dist2);
			
			screen->UpdateLCD();
		}
	}
	
//	void Triangulate (double something, double someOtherThing)
//	{
//	 //trig 
//	}

	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo)
;

