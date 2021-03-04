#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>


nav_msgs::Odometry odom;
void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg){
     static tf::TransformBroadcaster odom_broadcaster;

	ROS_INFO("Seq: [%d]", msg->header.seq);
	ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
	ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
	ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);
    
    odom.child_frame_id = "base_link";
    odom.header = msg->header ;
    odom.pose = msg->pose;
    odom.pose.pose.position.z = 0;
    odom.twist = msg->twist;

    //  geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(0);

    //     // // //first, we'll publish the transform over tf
    //      geometry_msgs::TransformStamped odom_trans;
    //      odom_trans.header.stamp=ros::Time::now();
    //      odom_trans.header.frame_id = "map";
    //      odom_trans.child_frame_id = "base_link";

    //      odom_trans.transform.translation.x = msg->pose.pose.position.x;
    //      odom_trans.transform.translation.y = msg->pose.pose.position.y;
    //      odom_trans.transform.translation.z = msg->pose.pose.position.z;
    //      odom_trans.transform.rotation.w = msg->pose.pose.orientation.w;
    //      odom_trans.transform.rotation.x = msg->pose.pose.orientation.x;
    //      odom_trans.transform.rotation.y = msg->pose.pose.orientation.y;
    //      odom_trans.transform.rotation.z = msg->pose.pose.orientation.z;

    //     // // //send the transform
    //       odom_broadcaster.sendTransform(odom_trans);


}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "odometry_publisher");

    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/mavros/odometry/in",1000, chatterCallback);
    ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 1000);   
   


     ros::Time current_time, last_time;
    // current_time = ros::Time::now();
    // last_time = ros::Time::now();

    ros::Rate r(100);
    while (n.ok())
    {

        ros::spinOnce(); // check for incoming messages
         current_time = ros::Time::now();

        // //compute odometry in a typical way given the velocities of the robot
        // double dt = (current_time - last_time).toSec();
        // double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
        // double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
        // double delta_th = vth * dt;

        // x += delta_x;
        // y += delta_y;
        // th += delta_th;

        // //since all odometry is 6DOF we'll need a quaternion created from yaw
       
        //next, we'll publish the odometry message over ROS
        // nav_msgs::Odometry odom;
        // odom.header.stamp = current_time;
        // odom.header.frame_id = "odom";

        // //set the position
        // odom.pose.pose.position.x = x;
        // odom.pose.pose.position.y = y;
        // odom.pose.pose.position.z = 0.0;
        // odom.pose.pose.orientation = odom_quat;

        // //set the velocity
        // odom.child_frame_id = "base_link";
        // odom.twist.twist.linear.x = vx;
        // odom.twist.twist.linear.y = vy;
        // odom.twist.twist.angular.z = vth;

        //publish the message
        odom_pub.publish(odom);

        // last_time = current_time;
        r.sleep();
    }
}