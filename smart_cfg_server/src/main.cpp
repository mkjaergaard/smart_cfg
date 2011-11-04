/*
 * main.cpp
 *
 *  Created on: Aug 8, 2011
 *      Author: morten
 */

#include <fstream>
#include <sstream>
#include <yaml-cpp/yaml.h>
#include <smart_cfg_server/component_model.h>
#include <smart_cfg_server/deployed_component_manager.h>
#include <smart_cfg_server/middleware_system_link_ros.h>
#include <smart_cfg_server/middleware_gui_link_ros.h>

int main(int argc, char** argv)
{
  // Setup Mngr: Deployed Components
  smart_cfg_server::DeployedComponentManager::Ptr mngr( new smart_cfg_server::DeployedComponentManager() );
  mngr->registerDeployedComponent( DeployedComponentID("cfg_dummy") );

  // Register a parameter for testing
  ParameterIDAndValue new_value( ParameterID("someint") );
  new_value.value().setFromValue<int>(2, ParameterStatus::OVERRIDDEN );
  mngr->pushReplyReceivedNotify( DeployedComponentID("test"), new_value );

  // Setup ROS interfaces
  ros::init(argc, argv, "cfg_server");
  ros::NodeHandle nh("cfg_server");
  MiddlewareSystemLinkRos::Ptr system_ros( new MiddlewareSystemLinkRos(nh) );
  system_ros->registerPushReplyListener( mngr );
  MiddlewareGuiLinkRos::Ptr gui_ros( new MiddlewareGuiLinkRos(nh) );

  mngr->registerChangeListener( gui_ros );
  mngr->registerPushHandler( system_ros );

  // Set an override
  ParameterIDAndValue::ListOf override_list;
  ParameterIDAndValue override_param( ParameterID("blop") );
  override_param.value().setFromValue<int>(4);
  override_list.push_back(override_param);
  mngr->parameterValueOverrideRequest( DeployedComponentID("test"), override_list);

  // Queue a change of a parameter: cfg_dummy/somefloat
/*    ParameterChangeRequest::Ptr req( new ParameterChangeRequest("cfg_dummy") );
    ParameterIDAndValue to_change("somefloat");
    to_change.value().setFromValue<double>(7.5);
    req->addValue(to_change);
    system_ros.queueParameterChangeRequest(req);
*/
    ros::spin();

/*
 * rostopic pub /deployed_component_info_request smart_cfg_msgs/ComponentModelInfoRequest "{'subscribe': 1, 'component_id': {'name':'test'} }"
 * rostopic pub /parameter_override smart_cfg_msgs/OverrideRequest "{'component_id': {'name':'test'}, 'parameters':[{'id':{'name':'something'}}]}"
 *
 */

return 0;

    std::ifstream fin("/home/morten/repositories/prevas/implementation/ros/ros-pkg/dtu/smart_cfg_server/models/cfg_dummy.cm");
    YAML::Parser parser(fin);

    //std::istringstream ins; // Declare an input string stream.
    //ins.str("123");        // Specify string to read.
    //YAML::Parser parser2(ins);

    YAML::Node doc;
/*    while(parser2.GetNextDocument(doc)) {
       int test;
       doc >> test;
       std::cout << "DOC: " << test << std::endl;
    }
*/

    while(parser.GetNextDocument(doc)) {
       smart_cfg_server::ComponentModel m;
       doc >> m;
    }

    return 0;
}
