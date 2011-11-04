#ifndef __COMMUNICATOR_H_INCLUDED__
#define __COMMUNICATOR_H_INCLUDED__

#include <smart_cfg_server/parameter_change_request.h>
#include <smart_cfg_server/i_deployed_component_manager_callback.h>

#include <boost/thread/mutex.hpp>
#include <queue>

namespace smart_cfg_server
{

class Communicator
{
protected:
  boost::mutex change_queue_mutex_;
  std::queue<ParameterChangeRequest::ConstPtr> change_queue_;
  IDeployedComponentManagerCallback * deployed_component_manager_;

public:
  Communicator() :
    deployed_component_manager_( 0 )
  {
  }

  void setDeployedComponentManagerCallback( IDeployedComponentManagerCallback * callback )
  {
    deployed_component_manager_ = callback;
  }

  void queueParameterChangeRequest( ParameterChangeRequest::ConstPtr request )
  {
    boost::mutex::scoped_lock(change_queue_mutex_);
    change_queue_.push(request);
  }

  bool popParameterChangeRequest( ParameterChangeRequest::ConstPtr& request_out )
  {
    boost::mutex::scoped_lock(change_queue_mutex_);
    if( !change_queue_.empty() )
    {
      request_out = change_queue_.front();
      change_queue_.pop();
      return true;
    }
    else
    {
      return false;
    }
  }

  void triggerParameterValueReceivedNotify( const std::string& component_name, const ParameterIDAndValue& param )
  {
    if( deployed_component_manager_ != 0 )
    {
      deployed_component_manager_->parameterValueReceivedNotify(component_name, param);
    }
  }

};

}

#endif
