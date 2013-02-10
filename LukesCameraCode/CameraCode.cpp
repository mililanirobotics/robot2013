#include "WPILib.h"
#include "nivision.h"

//HERE WE GO
class RobotDemo : public SimpleRobot
{
	Relay light;

public:
	RobotDemo(void):
		light(1, Relay::kForwardOnly)
	{
		
	}


	void Autonomous(void)
	{
		
		
	}

	void OperatorControl(void)
	{
		AxisCamera &camera = AxisCamera::GetInstance("10.28.53.11");
		camera.WriteBrightness(50);
		camera.WriteResolution(AxisCamera::kResolution_320x240);
		camera.WriteCompression(80);
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		light.Set(Relay::kOn);
		while (IsOperatorControl()){
		HSLImage *image = camera.GetImage();
		
		
		///////////////////////////////////////////////////////
		//                  Threshold                        //
		///////////////////////////////////////////////////////
		BinaryImage* binImg = image->ThresholdHSL(1, 255, 1, 255, 230, 255); //Need to get threshold parameters from helper
		binImg->Write("/tmp/thresh.jpg"); //These temp images are for debugging purposes only, and should not be used in the final code.
		imaqWriteFile(binImg->GetImaqImage(), "/tmp/thresh2.jpg", NULL);  
		
		
		///////////////////////////////////////////////////////
		//                  Convex Hull                      //
		///////////////////////////////////////////////////////
		Image* Convex = imaqCreateImage(IMAQ_IMAGE_U8, 0);
		imaqConvexHull(Convex, binImg->GetImaqImage(), TRUE);
		delete binImg;
		
		///////////////////////////////////////////////////////
		//                     Casts                         //
		///////////////////////////////////////////////////////
		float lookuptable[256];  //Not quite sure what lookup table does
		lookuptable[0] = 0;
		lookuptable[1] = 65535;
		Image* cast = imaqCreateImage(IMAQ_IMAGE_U16, 0);
		imaqCast(cast, Convex, IMAQ_IMAGE_U16, lookuptable, 0);  //Casts binary to 16 bit
		imaqDispose(Convex);
		Image* bitcast = imaqCreateImage(IMAQ_IMAGE_U8, 0);  //Casts 16 bit to 8 bit
		imaqCast(bitcast, cast, IMAQ_IMAGE_U8, NULL, 0);
		imaqDispose(cast);	
		
		////////////////////////////////////////////////////////
		//                  Shape Detection                   //
		////////////////////////////////////////////////////////
		
		//Copy the values from NI Vision
		static RectangleDescriptor rectangleDescriptor = 
		{
			30, 	// minWidth (All values are estimated)
			200, 	// maxWidth
			20, 	// minHeight
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
			300				// minMatchScore
		};
		
		
		int matches = 0;  //Holds number of matches found
		
		//The big important line of code that does important stuff
		RectangleMatch* recmatch = imaqDetectRectangles(bitcast, &rectangleDescriptor, &curveOptions, &shapeOptions, NULL, &matches);
		
		
		//Prints out locations of corners if it finds a match, or a message saying no match has been found.
		if (matches>0){
			screen->PrintfLine(DriverStationLCD::kUser_Line1,"Matches: %i",matches);//Notifies the user
			screen->PrintfLine(DriverStationLCD::kUser_Line2,"Corner 1: X:%f,Y:%f",recmatch->corner[0].x,recmatch->corner[0].y);
			screen->PrintfLine(DriverStationLCD::kUser_Line2,"Corner 1: X:%f,Y:%f",recmatch->corner[1].x,recmatch->corner[1].y);
			screen->PrintfLine(DriverStationLCD::kUser_Line2,"Corner 1: X:%f,Y:%f",recmatch->corner[2].x,recmatch->corner[2].y);
			screen->PrintfLine(DriverStationLCD::kUser_Line2,"Corner 1: X:%f,Y:%f",recmatch->corner[3].x,recmatch->corner[3].y);
		}
		else
		{
			screen->PrintfLine(DriverStationLCD::kUser_Line1, "No matches found!");
		}
		screen->UpdateLCD();
		}
		
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

		
		
	}
};

START_ROBOT_CLASS(RobotDemo);

