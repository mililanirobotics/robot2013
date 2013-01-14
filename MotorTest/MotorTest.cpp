#include "WPILib.h"

/**
 *  Test code for jaguar motors.
 *  Uses joystick 1's throttle to control speed, and button 1 to toggle motor.
 */
class RobotDemo: public SimpleRobot { // driver station object for getting selections
	Joystick leftstick;
	//ervo servo;
	Jaguar shooter1;
	Jaguar shooter2;

public:
	RobotDemo(void) :
		leftstick(1),
		//servo(3),
		shooter1(1),
		shooter2 (2)
	{

	}
	void OperatorControl() {
		{

			//			front.SetSafetyEnabled(false);
			//			back.SetSafetyEnabled(false);
			//			horizontal.Reset();
			//			vertical.Reset();
			//			int z = 0;
			//			int a = 0;
			//			double x, y;
			//			int buttoncount = 0;
			DriverStationLCD *screen = DriverStationLCD::GetInstance();

			while (IsOperatorControl()) {
				screen->PrintfLine(DriverStationLCD::kUser_Line1,
						"Z input: %f", leftstick.GetThrottle());
//				if (leftstick.GetRawButton(1)) {
//					shooter1.Set(.10);
//					//shooter2.Set(-0.5);
//				}  if (leftstick.GetRawButton(2)) {
//					shooter1.Set(0 - 0.10);
//					//shooter2.Set(0);
//				}
//				if (leftstick.GetRawButton(4)) {
//					shooter1.Set(.50);
//					//shooter2.Set(-0.5);
//				}if (leftstick.GetRawButton(5)) {
//					shooter1.Set(0 - 0.50);
//					//shooter2.Set(0);
//				}if (leftstick.GetRawButton(7)) {
//					shooter1.Set(.80);
//					//shooter2.Set(-0.5);
//				}if (leftstick.GetRawButton(10)) {
//					shooter1.Set(0 - 0.80);
//					//shooter2.Set(0);
//				} 
				if(leftstick.GetRawButton(1))
				{
					shooter1.Set(leftstick.GetThrottle());
					shooter2.Set(leftstick.GetThrottle());
				}
				else
				{
					shooter1.Set(0);
					shooter2.Set(0);
				}
				screen->UpdateLCD();
			}
			// supply your own teleop code here
		}
	}
};

START_ROBOT_CLASS(RobotDemo)
;

