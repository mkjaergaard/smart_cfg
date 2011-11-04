#ifndef __CONTROLLED_COMPONENT_ROS_H_INCLUDED__
#define __CONTROLLED_COMPONENT_ROS_H_INCLUDED__

#include <smart_cfg/controlled_component.h>
#include <ros/ros.h>
#include <std_msgs/String.h>

namespace smart_cfg
{

class ControlledComponentRos : virtual public ControlledComponent
{
protected:
  ros::Publisher pub_state_;
  ros::Timer timer_publish_;

  void publishTimerHandler(const ros::TimerEvent & e)
  {
    char buf[128];
    sprintf(buf, "State %i", getState() );

    std_msgs::String msg;
    msg.data = std::string(buf);
    pub_state_.publish( msg );
  }

  ControlledComponentRos( ros::NodeHandle& nh ) :
    pub_state_( nh.advertise<std_msgs::String>("state", 2) ),
    timer_publish_( nh.createTimer( ros::Duration(0.5), &ControlledComponentRos::publishTimerHandler, this ))
  {
  }


};

}

#endif
