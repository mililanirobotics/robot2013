#include "WPILib.h"
#include "math.h"

/**
 * This code is able to control a two motor system and get encoder values.
 * Note that the drive system takes input from the left and right analog
 * sticks of the Logitech controllers. If you want to use the normal
 * joysticks, then change 
 */ 
class RobotDemo : public SimpleRobot
{
	RobotDrive arcade1; 	//Front left and right motors drive
	RobotDrive arcade2; 	//Back left and right motors drive
	Joystick leftstick; 	//For general drive, retrieval, and end game
	Joystick rightstick;	//For tracking and scoring
	Jaguar drivefrontleft;	//Jaguar connected to the top left motor
	Jaguar drivebackleft;	//Jaguar connected to the bot left motor
	Jaguar drivefrontright;	//Jaguar connected to the top right motor
	Jaguar drivebackright;	//Jaguar connected to the bot right motor
	Jaguar shooter1;		//Jaguar connected to a shooter motor
	Jaguar shooter2;		//Jaguar connected to a shooter motor 
	Jaguar retrieval;		//Jaguar connected to the conveyer belt motor
	Gyro vertical;			//Vertical gyro reading angle in y for endgame
	Gyro horizontal;		//Horizontal gyro reading angle in x for drive correction
	Encoder encodershooter;	//Encoder connected to the shooter for RPM
	Solenoid bridgedevice;	//controls pneumatic bridge device
	Victor turntable;		//controls turret window motor
	Victor bridgevictor;	//controls window motor for deploying bridge device
	Relay spike;			//controls ringlight
	Compressor compressor;
	
	float distance(float heightpixel)
	{
		float fov = 54;
		float widthtarget = 2 ;
		float yresolution = 360;
		float distance = widthtarget*yresolution/heightpixel/tan(fov*3.14159265/180);		
		return (distance);
	}
	
public:
	RobotDemo(void):
		arcade1(drivefrontleft,drivefrontright), //Setting top left and top right motors to arcade 1
		arcade2(drivebackleft,drivebackright), //Setting bot left and bot right motors to arcade 2
		leftstick(1),
		rightstick(2),
		drivefrontleft(1),
		drivebackleft(2),
		drivefrontright(3),
		drivebackright(4),
		shooter1(5),
		shooter2(6),
		retrieval(7),
		vertical(1,1), //Gyro(slot,channel)
		horizontal(1,2),
		encodershooter(1,2),
		bridgedevice(3,1),
		turntable(9),
		bridgevictor(8),
		spike(1,Relay::kForwardOnly),
		compressor(1,2)
	{
	}

	void Autonomous(void)
	{
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		screen->PrintfLine(DriverStationLCD::kUser_Line1,"Autonomous");
		screen->UpdateLCD();
		while (IsAutonomous())
		{
			/* Locate & set up camera to be used*/
			AxisCamera &camera = AxisCamera::GetInstance("10.28.53.11");
			camera.WriteResolution(AxisCamera::kResolution_320x240);
			camera.WriteCompression(80);//Compresses the image(?)
			camera.WriteBrightness(50);//Sets the brightness to 80 on a scale from 0-100
			
			int matches = 0;
			float average = 0;
			
			/* Turn on ringlight */
			spike.Set(Relay::kOn);
			
			/* Connect to DriverStation */
			DriverStationLCD *screen = DriverStationLCD::GetInstance();
			screen->PrintfLine(DriverStationLCD::kUser_Line1,"CAA Active");
			screen->UpdateLCD();
			
			/* Create pointer for current image */
			HSLImage* originalHSLPointer;
			originalHSLPointer = camera.GetImage();
			
			/* COLOR PLANE EXTRACTION */
			/* Move the image from HSL image pointer to 8-bit image pointer and extract color planes by luminance */
			Image* pointer8bit = imaqCreateImage(IMAQ_IMAGE_U8, 0);
			//int imaqExtractColorPlanes(const Image* image, ColorMode mode, Image* plane1, Image* plane2, Image* plane3); 
			imaqExtractColorPlanes(originalHSLPointer, IMAQ_HSL, NULL, NULL, pointer8bit);
			delete originalHSLPointer;
			
			/* THRESHOLD */
			/* Move the image from 8-bit image pointer and filter using a brightness threshold */
			//int imaqThreshold(Image* dest, const Image* source, float rangeMin, float rangeMax, int useNewValue, float newValue); 
			imaqThreshold(pointer8bit, pointer8bit, 223, 255, int useNewValue, float newValue); 
			
			/* ADV MORPHOLOGY (SIZE FILTER) */
			/* Filter image by size (remove small particles) */
			
			/* ADV MORPHOLOGY (CONVEX HULL) */
			/* Fill in holes in image */
			
			/* CONVERSION (8-BIT TO 16-BIT) */
			/* Convert image from 8-bit to 16-bit */
			
			/* CONVERSION (16-BIT TO 8-BIT) */
			/* Convert image from 16-bit to 8-bit */
			
			/* SHAPE DETECTION (DETECT RECTANGLES) */
			/* Detect rectangle shapes in image */
			
			
#if 0		
			ROI *roi;
			Rect rectangle;
			rectangle.top = 120;
			rectangle.left = 0;
			rectangle.width = 320;
			rectangle.height = 120;
			imaqAddRectContour(roi,rectangle);
#endif
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
				500				// minMatchScore
			};
			RectangleMatch* recmatch = imaqDetectRectangles(bitcast, &recDescriptor, &curveOptions, &shapeOptions, NULL, &matches);
			//imaqDispose(roi);
			average = recmatch->corner[0].x/4 + recmatch->corner[1].x/4 + recmatch->corner[2].x/4 + recmatch->corner[3].x/4;
			//screen->PrintfLine(DriverStationLCD::kUser_Line5, "%f", average);	//debugging code, perhaps?
#if 1
			if (matches == 0)
			{
				imaqWriteFile(bitcast, "/tmp/bitcast.jpg", NULL);
			}
			
			if (average == 0)	//does this make it stop moving if no matches are found?
			{
				turntable.Set(0.0);
			}
			else if (average > 170 && average < 180)	//stop turret and print matches when centered
			{
				turntable.Set(0.0);
				screen->PrintfLine(DriverStationLCD::kUser_Line2,"Match: %i %f", matches,distance(recmatch->height));
				screen->UpdateLCD();
			}
			//go various speeds and directions based on image location. Far from center = high speed.
			else if (average > 180 && average < 185)
			{
				turntable.Set(0.1);
			}
			else if (average > 185)
			{
				turntable.Set(0.25);
			}
			else if (average > 165 && average < 170)
			{
				turntable.Set(-0.1);
			}
			else if (average < 165)
			{
				turntable.Set(-0.25);
			}
			imaqDispose(bitcast);
			imaqDispose(recmatch);
			int count = 0;
			
			if(average > 170 && average < 180)
			{
				//CHIAKAZING THE SHOOTER SPEEDS ARE SOMEWHAT ARBITRARY. TEST AND FIX.
				shooter1.Set(.7);
				shooter2.Set(.7);
				Wait(5.0);

				for(count = 0; count != 2; count++) {
					retrieval.Set(1.0);
					Wait(1.0);
					retrieval.Set(0.0);
					Wait(2);
				}

				shooter1.Set(0.0);
				shooter2.Set(0.0);
				retrieval.Set(0.0);
			}
#endif
		}
	}
	
	void OperatorControl(void)
	{
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		screen->PrintfLine(DriverStationLCD::kUser_Line1,"Operator Control");
		screen->UpdateLCD();
		
		/*DriverStationLCD *screen = DriverStationLCD::GetInstance();
		screen->UpdateLCD();
		while (IsOperatorControl())
		{
			vic.Set(0.0);
			screen->PrintfLine(DriverStationLCD::kUser_Line5,"no button");
			screen->UpdateLCD();
			
			while (stick1.GetRawButton(1)) {
				screen->PrintfLine(DriverStationLCD::kUser_Line5,"Button1");
				vic.Set(0.5);
			}
			while (stick1.GetRawButton(2)) {
				screen->PrintfLine(DriverStationLCD::kUser_Line5,"Button2");
				vic.Set(-0.5);
			}
			
		}*/
	}
};
START_ROBOT_CLASS(RobotDemo);
