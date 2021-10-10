// License: Apache 2.0. See LICENSE file in root directory.
// Alessansdro de Oliveira Faria (A.K.A.CABELO) 
// g++ main.cpp `pkg-config --cflags opencv4` `pkg-config --libs opencv4`  -lrealsense2 

#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <opencv2/opencv.hpp>   // Include OpenCV API
#include "utils.hpp"

const int erosion_size = 3;
Mat erode_less = gen_element(erosion_size);
Mat erode_more = gen_element(erosion_size * 2);

void create_mask_from_depth(Mat& depth, int thresh, ThresholdTypes type)
{
   threshold(depth, depth, thresh, 255, type);
   dilate(depth, depth, erode_less);
   erode(depth, depth, erode_more);
}

int main(int argc, char * argv[]) try
{

    VideoWriter writer;
    int codec = VideoWriter::fourcc('H', '2', '6', '4');  
    double fps = 15.0;
    string filename = "lookingglass.mp4";
    Size sizeFrame(640,960);
    bool isColor = true;
    writer.open(filename, codec, fps, sizeFrame, isColor);

    rs2::threshold_filter thr_filter;	
    rs2::colorizer colorize;
    rs2::align align_to(RS2_STREAM_COLOR);

    rs2::pipeline pipe;
    pipe.start();

    using namespace cv;
    using namespace rs2;
    const auto window_name = "Lookingglass Portrait";
    namedWindow(window_name, 1);

    int min_depth = 1;
    int max_depth = 160;
    createTrackbar("Max", window_name, &max_depth, 800);
    createTrackbar("Min", window_name, &min_depth, 800);

    thr_filter.set_option(RS2_OPTION_MIN_DISTANCE, (float)(min_depth/100));
    thr_filter.set_option(RS2_OPTION_MAX_DISTANCE, (float)(max_depth/100));
    colorize.set_option(RS2_OPTION_COLOR_SCHEME, 1);


    while (waitKey(1) < 0 && getWindowProperty(window_name, WND_PROP_AUTOSIZE) >= 0)
    {
        thr_filter.set_option(RS2_OPTION_MIN_DISTANCE, (float)(min_depth/100));
        thr_filter.set_option(RS2_OPTION_MAX_DISTANCE, (float)(max_depth/100));

        rs2::frameset data = pipe.wait_for_frames(); // Wait for next set of frames from the camera
        frameset aligned_set = align_to.process(data);

	frame depth = aligned_set.get_depth_frame();
	frame color = aligned_set.get_color_frame();

        frame d1 = depth.apply_filter(thr_filter);
        frame c1 = color.apply_filter(colorize);

	frame bw_depth = d1.apply_filter(colorize); 
	Mat _depth = frame_to_mat(bw_depth);
        Mat _color = frame_to_mat(c1);
        
        Mat video;
	Mat far = frame_to_mat(bw_depth);
        cvtColor(far, far, COLOR_BGR2GRAY);
        far.setTo(255, far == 0); 
        create_mask_from_depth(far, 254, THRESH_BINARY_INV);
        cvtColor(far, far, COLOR_GRAY2BGR);
 
        Mat bgModel, fgModel;
        bitwise_and(_color, far, fgModel); 

        cv::vconcat(fgModel,_depth,video);
        imshow(window_name, video);
	writer.write(video);
    }

    writer.release();
    return EXIT_SUCCESS;
}
catch (const rs2::error & e)
{
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
    return EXIT_FAILURE;
}
catch (const std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}
