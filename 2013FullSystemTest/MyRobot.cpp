#include "WPILib.h"
#include <math.h>

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
	Gyro gRot, gArm1, gArm2;
public:
	RobotDemo(void) :
		stick(1),
				stick2(2),
				//Jaguars
				driveFrontLeft(1), driveRearLeft(2), driveFrontRight(3),
				driveRearRight(4), endGameLeftFront(5), endGameLeftBack(6),
				endGameRightFront(7), endGameRightBack(8), dumper(9),
				//Light
				light(1, 4, Relay::kForwardOnly),
				//Servos
				dumpLock(10),
				//Switches
				dFT(1), dBK(2),//dFB(2), dRT(3), dRB(4),
				//Gyros
				gRot(1), gArm1(2), gArm2(3) {
	}
	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void) {

	}
	//Obsolete - use math.fabs instead (Why didn't I find this earlier???)
	//	float absolute(float number) {
	//		if (number < 0) {
	//			number = -number;
	//		}
	//		return number;
	//	}

	//Modulus function
	//	float mod(float n1, float n2) {
	//		while (n1 > n2) {
	//			n1 = n1 - n2;
	//		}
	//		return n1;
	//	}
	float sign(float x) {
		if (x < 0)
			return -1;
		else if (x > 0)
			return 1;
		else
			return 0;
	}

	//Drive function
	void MecanumDrive(float forward, float right, float clockwise) {
		float front_left = forward - clockwise + right;
		float front_right = forward + clockwise - right;
		float rear_left = forward - clockwise - right;
		float rear_right = forward + clockwise + right;
		float max = fabs(front_left); //This part finds the largest value in the drive and checks if it is larger than 1 or smaller than -1
		if (fabs(front_right) > max) {
			max = fabs(front_right);
		}
		if (fabs(rear_left) > max) {
			max = fabs(rear_left);
		}
		if (fabs(rear_right) > max) {
			max = fabs(rear_right);
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
	/*void RobotDrive::MecanumDrive_Cartesian (float x,  
	 float d,
	 float rotation); */

	void OperatorControl(void) {
		bool calibrate;
		//bool kill = false;
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		bool robotIsNotMoving;
		float gyroAngle; //current angle of the gyro
		float prevAngle = 0; //angle of the gyro the last time it was stationary

		//speed going forward, right, & clockwise
		float forward;
		float right;
		float clockwise;

		//number of times robot has been stationary
		int stationaryCount = 0;

		//speed of each mecanum wheel
		float front_left;
		float front_right;
		float rear_left;
		float rear_right;
		bool isOne = false;
		float max;
		while (IsOperatorControl()) {
			forward = -stick.GetY();
			right = -stick.GetX();
			clockwise = stick.GetThrottle();
			if (fabs(stick.GetX()) < .3)
				right = 0;
			if (fabs(stick.GetY()) < .3)
				forward = 0;
			if (fabs(stick.GetThrottle()) < .3)
				clockwise = 0;
			else
				clockwise = 0.9 * sign(stick.GetThrottle());
			if (stick2.GetRawButton(1)) {
				endGameLeftFront.Set(0.2);
			} else if (stick2.GetRawButton(2)) {
				endGameLeftFront.Set(-0.2);
			} else {
				endGameLeftFront.Set(0);
			}
			if (stick2.GetRawButton(3)) {
				endGameLeftBack.Set(0.2);
			} else if (stick2.GetRawButton(4)) {
				endGameLeftBack.Set(-0.2);
			} else {
				endGameLeftBack.Set(0);
			}
			if (stick2.GetRawButton(5)) {
				isOne = !isOne;
				if (isOne)
					dumpLock.Set(1);
				else
					dumpLock.Set(0);
			}
			if (stick2.GetRawButton(6)) {
				dumper.Set(0.5);
			} else if (stick2.GetRawButton(7)) {
				dumper.Set(-0.5);
			} else {
				dumper.Set(0);
			}
			if (stick2.GetRawButton(8)) {
				endGameRightFront.Set(0.2);
			} else if (stick2.GetRawButton(9)) {
				endGameRightFront.Set(-0.2);
			} else {
				endGameRightFront.Set(0);
			}
			if (stick2.GetRawButton(10)) {
				endGameRightBack.Set(0.2);
			} else if (stick2.GetRawButton(11)) {
				endGameRightBack.Set(-0.2);
			} else {
				endGameRightBack.Set(0);
			}
			MecanumDrive(forward, right, clockwise);
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
