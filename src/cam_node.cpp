#include<ros/ros.h>
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../include/USBDev/USBDev.h"
#include <iostream>
using namespace std;
typedef unsigned int UINT32;


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "image_pulisher");
    ros::NodeHandle nh;
    sensor_msgs::ImagePtr msg;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("cam/image_raw",1);
    cv::Mat image(480,752,CV_8UC1);
    UINT32 loglevel = 2;
    DEV_FRAME_INFO frameInfo;
    DEV_SetDeviceParameter(0xFFFF, SET_LOG_LEVEL, &loglevel);
    DEV_OpenDevice();
    ros::Rate loop_rate(4);
    while(nh.ok())
    {
        DEV_GetFrame(0, 0, 2, &frameInfo);
        image.data=frameInfo.pFrameBuffer;
        cv::imshow("image",image);
        cv::waitKey(30);
        msg = cv_bridge::CvImage(std_msgs::Header(),"mono8", image).toImageMsg();
        msg->header.frame_id="wolrd";
        msg->header.stamp = ros::Time::now() ;
        msg->height = frameInfo.nFrameHeight;
        msg->width = frameInfo.nFrameWidth;
        msg->encoding = "mono8";
        pub.publish(msg);
        ros::spinOnce();
	loop_rate.sleep();
    }
}
