#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_tf_publisher");
    ros::NodeHandle n;

    ros::Rate r(100);

    tf::TransformBroadcaster broadcaster;
     tf::TransformListener listener(ros::Duration(10));

    while (n.ok())
    {
        broadcaster.sendTransform(
            tf::StampedTransform(
                tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.80, 0.25, 0.2)),
                ros::Time::now(), "base_link", "laser"));


           broadcaster.sendTransform(
            tf::StampedTransform(
                tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0 , 0 , 0)),
                ros::Time::now(), "odom", "base_link"));
            
           

        r.sleep();
    }
}