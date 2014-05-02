#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	RobotDrive arcade1;
	RobotDrive arcade2;
	Joystick leftstick;
	//Joystick rightstick;
	Jaguar retrieval; // robot drive system
	Jaguar shooter1;
	Jaguar shooter2;
	Relay spike;
	Victor turntable;
	Encoder encoder;
	Jaguar drivefrontleft;	//Jaguar connected to the top left motor
	Jaguar drivebackleft;	//Jaguar connected to the bot left motor
	Jaguar drivefrontright;	//Jaguar connected to the top right motor
	Jaguar drivebackright;	//Jaguar connected to the bot right motor

public:
	RobotDemo(void):
		arcade1(drivefrontleft,drivefrontright), //Setting top left and top right motors to arcade 1
		arcade2(drivebackleft,drivebackright), //Setting bot left and bot right motors to arcade 2
		leftstick(1),
		//rightstick(2),// as they are declared above.
		retrieval(7),
		shooter1(5),
		shooter2(6),
		spike(1),
		turntable(10),
		encoder(1,2),
		drivefrontleft(1),
		drivebackleft(2),
		drivefrontright(3),
		drivebackright(4)
	{
		
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
		bool wait = true;
		while (IsOperatorControl())
		
		{
			wait = true;
			arcade1.ArcadeDrive(leftstick); //Arcade drive system assigned to the left joystick
			//arcade2.TankDrive(leftstick, leftstick);
			DriverStationLCD *screen = DriverStationLCD::GetInstance();
			/*encoder.SetDistancePerPulse(0.0058177642);
			encoder.Reset();
			
			encoder.Start();
			while(stick.GetRawButton(4))
			{
				retrieval.Set(0.5);
			}
			while(stick.GetRawButton(5))
			{
				retrieval.Set(-0.5);
			} //DONT USE RETRIEVAL DAMNIT!!!*/
			retrieval.Set(0.0);
			spike.Set(Relay::kOff);
			//screen->PrintfLine(DriverStationLCD::kUser_Line1,"%f",.1*stick.GetZ());
			screen->UpdateLCD();
			/*while(leftstick.GetRawButton(7) && leftstick.GetRawButton(8))
			{
				    screen->PrintfLine(DriverStationLCD::kUser_Line2,"Pressing Button 1");
					spike.Set(Relay::kForward);
					AxisCamera &camera = AxisCamera::GetInstance("10.28.53.11");
					camera.WriteResolution(AxisCamera::kResolution_320x240);
					camera.WriteCompression(80);//Compresses the image(?)
					camera.WriteBrightness(50);//Sets the brightness to 80 on a scale from 0-100
					int matches = 0;
					float average = 0;
					DriverStationLCD *screen = DriverStationLCD::GetInstance();
					screen->PrintfLine(DriverStationLCD::kUser_Line1,"%i, %f", matches, average);
					screen->PrintfLine(DriverStationLCD::kUser_Line2, "Pressing button 1");
					screen->UpdateLCD();
					HSLImage* imgpointer;
					imgpointer = camera.GetImage();
					//imaqWriteFile(imgpointer, "/tmp/imagetest1.jpg", NULL);
					BinaryImage* binImg = NULL;
					binImg = imgpointer->ThresholdHSL(0, 255, 0, 255, 237, 255); //somebody please type a comment here that actually says what the parameters do
					delete imgpointer;
					Image* Convex = imaqCreateImage(IMAQ_IMAGE_U8, 0);
					Image* Size = imaqCreateImage(IMAQ_IMAGE_U8, 0);
					imaqSizeFilter(Size, binImg->GetImaqImage(), TRUE, 1, IMAQ_KEEP_LARGE, NULL);
					delete binImg;
					imaqConvexHull(Convex, Size, TRUE);
					imaqDispose(Size);
					screen->UpdateLCD();
					float lookuptable[256];
					lookuptable[0] = 0;
					lookuptable[1] = 65535;
					Image* cast = imaqCreateImage(IMAQ_IMAGE_U16, 0);
					imaqCast(cast, Convex, IMAQ_IMAGE_U16, lookuptable, 0);
					imaqDispose(Convex);
					Image* bitcast = imaqCreateImage(IMAQ_IMAGE_U8, 0);
					imaqCast(bitcast, cast, IMAQ_IMAGE_U8, NULL, 0);
					imaqDispose(cast);
					static RectangleDescriptor recDescriptor = 
					{
						10, 	// minWidth
						200, 	// maxWidth
						10, 	// minHeight
						200		// maxHeight
					};
				
					static CurveOptions curveOptions = //extraction mode specifies what the VI identifies curves in the image. curve options are all the  
					{	
						IMAQ_NORMAL_IMAGE,	// extractionMode
						75, 				// threshold
						IMAQ_NORMAL, 		// filterSize
						25, 				// minLength
						15, 				// rowStepSize 
						15, 				// columnStepSize
						10, 				// maxEndPointGap
						FALSE,				// onlyClosed
						FALSE				// subpixelAccuracy
					};
					static ShapeDetectionOptions shapeOptions = 
					{		
						IMAQ_GEOMETRIC_MATCH_ROTATION_INVARIANT,	// mode
						NULL,			// angle ranges
						0,				// num angle ranges
						{75, 125},		// scale range
						100				// minMatchScore
					};
					RectangleMatch* recmatch = imaqDetectRectangles(bitcast, &recDescriptor, &curveOptions, &shapeOptions, NULL, &matches);
					//imaqDispose(roi);
					average = recmatch->corner[0].x/4 + recmatch->corner[1].x/4 + recmatch->corner[2].x/4 + recmatch->corner[3].x/4;
					//screen->PrintfLine(DriverStationLCD::kUser_Line5, "%f", average);	//debugging code, perhaps?
					screen->PrintfLine(DriverStationLCD::kUser_Line6,"Avg. %f",average);
					screen->UpdateLCD();
						if (matches == 0)
						{
							imaqWriteFile(bitcast, "/tmp/bitcast.jpg", NULL);
						}
						
						if (average > 170 && average < 180)	//does this make it stop moving if no matches are found?
						{
							turntable.Set(0.0);
							screen->PrintfLine(DriverStationLCD::kUser_Line6,"Perfection!");
						}
						else if (average > 180 && average < 185)
						{
							turntable.Set(-0.2);
						}
						else if (average > 185)
						{
							turntable.Set(-0.3);
						}
						else if (average > 165 && average < 170)
						{
							turntable.Set(0.2);
						}
						else if (average < 165 && average > 0)
						{
							turntable.Set(0.3);
						}
						else
						{
							turntable.Set(0);
						}
						imaqDispose(bitcast);
						imaqDispose(recmatch);
					}
					*/
					while(leftstick.GetRawButton(1))
					{
						turntable.Set(0.8);
					}
					while(leftstick.GetRawButton(3))
					{
						screen->PrintfLine(DriverStationLCD::kUser_Line2,"Pressing Button 3");
						turntable.Set(-0.7);
					}
					while(leftstick.GetRawButton(2))
					{
						retrieval.Set(0.8);
					}
					while(leftstick.GetRawButton(4))
					{
						retrieval.Set(-0.7);
					}
			
			//gyro testing
						while(leftstick.GetRawButton(7))
						{
							shooter1.Set(-0.7);
							shooter2.Set(-0.7);
							screen->PrintfLine(DriverStationLCD::kUser_Line2,"Pressing Button 5");
							Wait(4.0);
							retrieval.Set(0.7);
							Wait(2.0);
							retrieval.Set(0.0);
						}
			
						/*while(leftstick.GetRawButton(4))
						{
							screen->PrintfLine(DriverStationLCD::kUser_Line2,"Pressing Button 5");
							shooter1.Set(0.3);
							shooter2.Set(0.3);
							Wait(4.0);
							retrieval.Set(0.7);
							Wait(2.0
									);
							retrieval.Set(0.0);
						}
						//while(leftstick.GetRawButton(7))
						{
							shooter1.Set(0.3);
							shooter2.Set(0.3);
						}
						//while(leftstick.GetRawButton(8))
						{
							shooter1.Set(-0.3);
							shooter2.Set(-0.3);
						}
			//gyro testing
						/*while(leftstick.GetRawButton(6))
						{
							shooter1.Set(-0.8 + .1*stick.GetZ());
							shooter2.Set(-0.8 + .1*stick.GetZ());
						}*/

						turntable.Set(0.0);
						retrieval.Set(0.0);
						shooter1.Set(0.0);
						shooter2.Set(0.0);
			}
	}
};

START_ROBOT_CLASS(RobotDemo);

