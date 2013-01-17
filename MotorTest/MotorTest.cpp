#include "WPILib.h"

/**
 *  Test code for jaguar motors.
 *  Uses joystick 1's throttle to control speed, and button 1 to toggle motor.
 */
class RobotDemo: public SimpleRobot { // driver station object for getting selections
	Joystick leftstick;
	Jaguar shooter1;
	Jaguar shooter2;
	Victor turntable;
//	AxisCamera cam;

public:
	RobotDemo(void) :
		leftstick(1),
		//servo(3),
		shooter1(4),
		shooter2 (6),
		turntable(10)
	//	cam()
	{

	}
	void OperatorControl() {
		{
		//	cam = AxisCamera::GetInstance("10.28.53.11");
			
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
				screen->PrintfLine(DriverStationLCD::kUser_Line1,"Z input: %f", leftstick.GetThrottle());
				screen->UpdateLCD();
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
				if (leftstick.GetRawButton(4) == true){
					turntable.Set(.4);
				}
				else if (!leftstick.GetRawButton(5)== true){
					turntable.Set(0);
				}
				else{}
				if (leftstick.GetRawButton(5) == true){
					turntable.Set(-.4);
				}
				else if (!leftstick.GetRawButton(4)== true){
					turntable.Set(0);
				}
				else{}
				
				
			
			}
			// supply your own teleop code here
		}
	}
};

START_ROBOT_CLASS(RobotDemo)
;

