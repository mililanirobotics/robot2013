#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */
class RobotDemo: public SimpleRobot {
	Joystick leftStick, rightStick;
	Jaguar jaga, jagb, jagc, jagd;
	RobotDrive drive;
	Victor turntable;
public:
	RobotDemo(void) :
		jaga(4), jagb(3), jagc(2), jagd(1), leftStick(1), rightStick(2),
				drive(1, 2, 3, 4), turntable(9) {

	}

	void Autonomous(void) {

	}

	/**
	 * Runs tank drive with four motors 
	 */
	void OperatorControl(void) {
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		
		while (IsOperatorControl()) {
			screen->PrintfLine(DriverStationLCD::kUser_Line1, "%f",
					leftStick.GetY());
			screen->UpdateLCD();

			if (leftStick.GetY() > .1) {
				jaga.Set(leftStick.GetY());
				jagb.Set(leftStick.GetY());
				//jagc.Set(-leftStick.GetY() + .1);
				//jagd.Set(-leftStick.GetY() + .1);
			} else if (leftStick.GetY() < .1) {
				//jagc.Set(-leftStick.GetY() - .1);
				//jagd.Set(-leftStick.GetY() - .1);
				jaga.Set(leftStick.GetY());
				jagb.Set(leftStick.GetY());
			}
			
			if (rightStick.GetY() > .1) {
				//jaga.Set(leftStick.GetY());
				//jagb.Set(leftStick.GetY());
				jagc.Set(-rightStick.GetY() + .1);
				jagd.Set(-rightStick.GetY() + .1);
			} else if (rightStick.GetY() < .1) {
				jagc.Set(-rightStick.GetY() - .1);
				jagd.Set(-rightStick.GetY() - .1);
				//jaga.Set(leftStick.GetY());
				//jagb.Set(leftStick.GetY());
			}
				if (leftStick.GetRawButton(4))
				{
					turntable.Set(.2);
				}
				if (leftStick.GetRawButton(5))
				{
					turntable.Set(-.2);
				}
				turntable.Set(0);
			//			while(leftStick.GetRawButton(1))
			//			{
			//				jaga.Set(0.4);
			//				jagb.Set(0.4);
			//				jagc.Set(-0.3-leftStick.GetThrottle());
			//				jagd.Set(-0.3-leftStick.GetThrottle());
			//			}
			//			while(leftStick.GetRawButton(2))
			//			{
			//				jaga.Set(-0.4);
			//				jagb.Set(-0.4);
			//				jagc.Set(0.4+leftStick.GetThrottle());
			//				jagd.Set(0.4+leftStick.GetThrottle());
			//			}
			//			jaga.Set(0.0);
			//			jagb.Set(0.0);
			//			jagc.Set(0.0);
			//			jagd.Set(0.0);

		}
		//drive.TankDrive(leftStick, rightStick);
	}
};

START_ROBOT_CLASS(RobotDemo)
;

