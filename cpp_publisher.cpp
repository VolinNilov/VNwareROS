// ROS Default Header File
#include "ros/ros.h"
// Message File Header
#include "std_msgs/String.h"

void msgCallback(const std_msgs::StringConstPtr& msg)
{
  ROS_INFO("I'm subscriber: recieve msg from hello = %s", msg->data.c_str());
}

void msgCallbackTopic2(const std_msgs::StringConstPtr& msg)
{
  ROS_INFO("I'm subscriber: recieve msg from topic 2 = %s", msg->data.c_str());
}

int main(int argc, char **argv)
{
  std::vector<std::string> vec;
  
  int par = 1;
  ros::init(argc, argv, "cpp_publisher_node");
  ROS_INFO("Hello from cpp publisher node");
  ros::NodeHandle nh;
  
  ros::Publisher pub1 = nh.advertise<std_msgs::String>("hello", 1000);
  ros::Publisher pub2 = nh.advertise<std_msgs::String>("topic2", 1000);
  
  ros::Rate loop_rate(1);
  
  
  ros::Time init_time = ros::Time::now();
  double time = 0.0;
  int count = 1;
  
  nh.getParamNames(vec);
  
  // ROS_INFO("Vector size = %d", vec.size());
  
  // std::string s="";
  // for(int i = 0; i < vec.size(); i++)
  // {
  //     ROS_INFO("%s", vec[i]);
  //     s+=vec[i];
  // }
  // ROS_INFO("%s", s);
  
  if(nh.getParam("slp", par))
  {
  	//ROS_INFO("Publisher param: %s", str_param.c_str());
  	ROS_INFO("Publisher param: %d", par);
  }
  else
  {
  	ROS_INFO("Publisher param fail");
  }
  
  while(ros::ok())
  {
      std_msgs::String msg1, msg2;
      std::stringstream ss;
      
      time = ros::Time::now().toSec() - init_time.toSec();
      
      ss << "Hello World " << time;
      msg1.data = ss.str();
      
      ss.str("");
      
      ss << count;
      msg2.data = ss.str();
      
      ROS_INFO("I'm publisher: %s", msg1.data.c_str());
      
      pub1.publish(msg1);
      pub2.publish(msg2);
      
      ros::spinOnce();
      
      ros::Duration(par).sleep();
      //loop_rate.sleep();
      count++;
      
  }
  
  return 0;
}
