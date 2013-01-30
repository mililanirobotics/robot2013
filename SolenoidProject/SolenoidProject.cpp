#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */
class RobotDemo: public SimpleRobot {

	Servo servo;
	Joystick joy1;
	Relay spike;
public:
	NetworkTable *netTable;
	RobotDemo(void) :
		servo(1), joy1(1), spike(1, Relay::kForwardOnly) {

	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void) {
		NetworkTable::SetIPAddress("10.28.53.2");
		NetworkTable::SetServerMode();
		NetworkTable::SetTeam(2853);
		NetworkTable::Initialize();
		netTable = NetworkTable::GetTable("SmartDashboard");
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void) {
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		while (IsOperatorControl()) {
			float xpos = 8;
			xpos = netTable->GetNumber("Slider 1");
			spike.Set(Relay::kOn);
			float test = (joy1.GetTwist() + 1) / 2;
			screen->PrintfLine(DriverStationLCD::kUser_Line1, "Z input: %f", test);
	//		screen->PrintfLine(DriverStationLCD::kUser_Line1, "Z input: %d", xpos);
		//	servo.Set(xpos/100);
		//	if (xpos < 150) {
		//		servo.Set(servo.Get() - .02);
		//	}
		//	if (xpos > 170) {
		//		servo.Set(servo.Get() + .02);
		//	}
			screen->UpdateLCD();
			servo.Set((joy1.GetTwist() + 1) / 2);
		}
	}

	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo)
;
