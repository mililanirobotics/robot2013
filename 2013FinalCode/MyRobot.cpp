#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */
class RobotDemo: public SimpleRobot {
	Joystick stick, stick2;
	Victor driveFrontLeft, driveRearLeft, driveFrontRight, driveRearRight;
	Jaguar endGameLeftFront, endGameLeftBack, endGameRightFront,
			endGameRightBack;
	Victor dumper;
	Relay light;
	Servo dumpLock;
	DigitalInput dFT, dBK;//dFB, dRT, dRB; dFT = Microswitch safety for front arms, dBK = microswtich safety for back
	Gyro gRot, gFlip;
	NetworkTable *netTable;

public:
	RobotDemo(void) :
				//Joystick
				stick(1), stick2(2),
				//Jaguars
				driveFrontLeft(1), driveRearLeft(2), driveFrontRight(3),
				driveRearRight(4), endGameLeftFront(5),	endGameLeftBack(6),endGameRightFront(7), endGameRightBack(8), dumper(9),
				//Light
				light(1, 4, Relay::kForwardOnly),
				//Servos
				dumpLock(10),
				//Switches
				dFT(1), dBK(2),//dFB(2), dRT(3), dRB(4),
				//Gyros
				gRot(1), gFlip(2) {

	}

	void Autonomous(void) {

	}

	//Absolute value function
	float absolute(float number) {
		if (number < 0) {
			number = -number;
		}
		return number;
	}

	//Modulus function
	float mod(float n1, float n2) {
		while (n1 > n2) {
			n1 = n1 - n2;
		}
		return n1;
	}

	//Drive function
	void MecanumDrive(float forward, float right, float clockwise) {
		float front_left = forward - clockwise + right;
		float front_right = forward + clockwise - right;
		float rear_left = forward - clockwise - right;
		float rear_right = forward + clockwise + right;

		float max = absolute(front_left); //This part finds the largest value in the drive and checks if it is larger than 1 or smaller than -1
		if (absolute(front_right) > max) {
			max = absolute(front_right);
		}
		if (absolute(rear_left) > max) {
			max = absolute(rear_left);
		}
		if (absolute(rear_right) > max) {
			max = absolute(rear_right);
		}
		if (max > 1)//If it is, normalize all values by dividing by the highest value, maintaining the ratio.
		{ //Jaguar Sets values range only from -1 to 1
			front_left = front_left / max;
			front_right = front_right / max;
			rear_left = rear_left / max;
			rear_right = rear_right / max;
		}

		driveFrontLeft.Set(front_left);
		driveFrontRight.Set(-front_right);
		driveRearLeft.Set(rear_left);
		driveRearRight.Set(-rear_right);

	}
	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void) {

		DriverStationLCD *screen = DriverStationLCD::GetInstance();

		//Toggle for auto-45
		bool isLocked45 = false;
		bool isLockedStrafe = false;
		//Killswitch toggles
		//bool kFL = false, kFR = false, kRL = false, kRR = false;
		//CODE DIFFERENCES BETWEEN JOYSTICKS
		//IF SINGLE JOYSTICK (EXTREME 3D PRO), change clockwise = stick.GetZ();
		//IF XBOX CONTROLELR, change clockwise = stick.GetThrottle(), and comment out stick.GetRawButton(1) code
		while (IsOperatorControl()) {
			float x1 = 0;
			float x2 = 0;
			float centerx = 0;
			float forward = -stick.GetY(); // push joystick forward to go forward 
			float right = -stick.GetX(); // push joystick to the right tostrafe right 
			float clockwise = stick.GetThrottle()*2/3; // twist joystick clockwise turn clockwise & Change depending on joysticks (see part above)
			//Deadzones 
			if (absolute(stick.GetX()) < .3) {
				right = 0;
			} else if (absolute(stick.GetX()) < .9) {
				if (stick.GetX() > 0)
					right = -0.9;
				else
					right = 0.9;
			} else
				right = -stick.GetX();

			if (absolute(stick.GetY()) < .118) {
				forward = 0;
			}
			if (absolute(stick.GetThrottle()) < 0.15) {
				clockwise = 0;
			}
			if (!stick.GetRawButton(1))//Comment out if using XBOX Controller
			{
				clockwise = 0;
			}
			light.Set(Relay::kOn);
			if (stick.GetRawButton(11)) { //11 Starts the climb
				float delta = gRot.GetAngle();
				//TODO - SUPER IMPORTANT - NEED TO GET ACTUAL ANGLES THAT ROBOT WILL BE AT DURING CLIMB
				//For now, all angles will be set to 2853 - NEED TO CHANGE

				while (!(dFT.Get() == 1) && delta < 2853) {
					endGameLeftFront.Set(1);
					endGameRightFront.Set(1);
				}
				endGameLeftFront.Set(0);
				endGameRightFront.Set(0);
				while (!(dBK.Get() == 1) && delta < 2853) {
					endGameLeftFront.Set(1);
					endGameRightFront.Set(1);
				}
				endGameLeftFront.Set(0);
				endGameRightFront.Set(0);
				//while (delta )
			}
			//Network Table Code
			x1 = SmartDashboard::GetNumber("X1");
			x2 = SmartDashboard::GetNumber("X2");
			centerx = x1/2 + x2/2;
			if (stick.GetRawButton(7))
			{
				isLockedStrafe = !isLockedStrafe;
				screen->PrintfLine(DriverStationLCD::kUser_Line5,"LOCK STRAFE: %f", centerx);
			}
			screen->PrintfLine(DriverStationLCD::kUser_Line5,"Center: %f", centerx);
			if (isLockedStrafe)
			{
				if (centerx == 0)
					right = 0;
				else if ((centerx > 150) && (centerx < 170))
					right = 0;
				else if (centerx < 150)
					right = -0.9;
				else if(centerx > 170)
					right = 0.9;
				else{}
			}
			float theta = (mod(gRot.GetAngle() + 3600, 90));
			if (stick.GetRawButton(12)) {
				isLocked45 = !isLocked45;
				screen->PrintfLine(DriverStationLCD::kUser_Line2,
						"AUTO 45 MODE = " + isLocked45);
				Wait(0.20);
			}
			if (isLocked45) {
				if ((theta) - 45 > 1) {
					clockwise = -(.00889 * absolute(theta - 45) + .3);
					screen->PrintfLine(DriverStationLCD::kUser_Line4,
							"A: %.3f", theta);
				} else if ((theta) - 45 < -1) {
					clockwise = (.00889 * absolute(theta - 45) + .3);
					screen->PrintfLine(DriverStationLCD::kUser_Line4,
							"A: %.3f", theta);
				} else {
					screen->PrintfLine(DriverStationLCD::kUser_Line4,
							"PERFECT %f", theta);
					clockwise = 0;
				}
			}
			if (stick.GetRawButton(8))
			{
				dumpLock.Set(1);
				dumper.Set(0.7);
			}
			else
			{	
				dumper.Set(0);	
			}
			//After all calculations have been done, output results.
			//Drive Code
			MecanumDrive(forward, right, clockwise);
		}
	}
};
START_ROBOT_CLASS(RobotDemo)
;
