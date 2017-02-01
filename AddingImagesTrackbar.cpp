/**
 * @file LinearBlend.cpp
 * @brief Simple linear blender ( dst = alpha*src1 + beta*src2 )
 * @author OpenCV team
 */

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>

using namespace cv;

/** Global Variables */
const int alpha_slider_max = 100;
int alpha_slider;
double contrast = 1.0;
const int contrast_slider_max = 300;
int contrast_slider = 100;
double brightness = 0.0;
const int brightness_slider_max = 255;
int brightness_slider = 0;
double alpha;
double beta;

/** Matrices to store images */
Mat src1;
Mat src2;
Mat dst;

//![on_trackbar]
/**
 * @function on_trackbar
 * @brief Callback for trackbar
 */
static void on_trackbar( int, void* )
{
   alpha = (double) alpha_slider/alpha_slider_max ;

   beta = ( 1.0 - alpha );

   addWeighted( src1, alpha, src2, beta, 0.0, dst);

   imshow( "Linear Blend", dst );
}
//![on_trackbar]

static void on_trackbar_contrast(int, void*)
{
	printf("new contrast = %d\n", contrast_slider);
	contrast = (double) contrast_slider / 100;
	src1.convertTo(dst, -1, contrast, brightness);
	imshow("Linear Blend", dst);
}

static void on_trackbar_brightness(int, void*)
{
	printf("new birghtness = %d\n", brightness_slider);
	brightness = (double) brightness_slider;
	src1.convertTo(dst, -1, contrast, brightness);
	imshow("Linear Blend", dst);
}
/**
 * @function main
 * @brief Main function
 */
int main(int argc, char *argv[])
{
   //![load]
   /// Read images ( both have to be of the same size and type )
   src1 = imread(argv[1]);
   src2 = imread(argv[2]);
   //![load]

   if( src1.empty() ) { printf("Error loading src1 \n"); return -1; }
   if( src2.empty() ) { printf("Error loading src2 \n"); return -1; }

   /// Initialize values
   alpha_slider = 0;

   //![window]
   namedWindow("Linear Blend", WINDOW_AUTOSIZE); // Create Window
   //![window]

   //![create_trackbar]
   char TrackbarName[50];
   char ContrastTrackbarName[50];
   char BrightnessTrackbarName[50];
   sprintf( TrackbarName, "Alpha x %d", alpha_slider_max );
   sprintf( ContrastTrackbarName, "Contrast %d", contrast_slider_max );
   sprintf( BrightnessTrackbarName, "Brightness %d", brightness_slider_max );
   createTrackbar( TrackbarName, "Linear Blend", &alpha_slider, alpha_slider_max, on_trackbar );
   createTrackbar( ContrastTrackbarName, "Linear Blend", &contrast_slider, contrast_slider_max, on_trackbar_contrast );
   createTrackbar( BrightnessTrackbarName, "Linear Blend", &brightness_slider, brightness_slider_max, on_trackbar_brightness );
   //![create_trackbar]

   /// Show some stuff
   on_trackbar( alpha_slider, 0 );
   on_trackbar_contrast(contrast_slider, 0 );
   on_trackbar_brightness(brightness_slider, 0 );

   /// Wait until user press some key
   waitKey(0);

	imwrite("./blended_img.jpg", dst);
	Mat check = imread("./blended_img.jpg");
	imshow("Result", check);
	waitKey(0);

   return 0;
}
