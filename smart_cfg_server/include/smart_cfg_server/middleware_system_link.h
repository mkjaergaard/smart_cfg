#ifndef __MIDDLEWARE_SYSTEM_LINK_H_INCLUDED__
#define __MIDDLEWARE_SYSTEM_LINK_H_INCLUDED__

#include <smart_cfg_server/i_deployed_component_push_reply_listener.h>
#include <smart_cfg_server/i_deployed_component_system_push_handler.h>
#include <queue>
#include <boost/thread/mutex.hpp>

namespace smart_cfg_server
{

class MiddleWareSystemLink : public IDeployedComponentSystemPushHandler, public SharedFrom<MiddleWareSystemLink>
{
protected:
  boost::weak_ptr<IDeployedComponentPushReplyListener> push_reply_listener_;

  typedef std::queue<ParameterChangeRequest::ConstPtr> RequestQueueType;
  RequestQueueType request_queue_;
  boost::mutex request_queue_mutex_;

public:
  MiddleWareSystemLink()
  {
  }

  void registerPushReplyListener( boost::weak_ptr<IDeployedComponentPushReplyListener> push_reply_listener )
  {
    push_reply_listener_ = push_reply_listener;
  }

  void triggerPushReplyReceivedNotify( DeployedComponentID component_id, const ParameterIDAndValue& param )
  {
    if( !push_reply_listener_.expired() )
    {
      boost::shared_ptr<IDeployedComponentPushReplyListener>(push_reply_listener_)->pushReplyReceivedNotify(component_id, param);
    }
  }

  void pushChangeRequest( ParameterChangeRequest::ConstPtr request )
  {
    boost::mutex::scoped_lock lock(request_queue_mutex_);
    request_queue_.push( request );
  }

protected:
  bool popChangeRequest( ParameterChangeRequest::ConstPtr request_out )
  {
    boost::mutex::scoped_lock lock(request_queue_mutex_);
    if( request_queue_.empty() )
    {
      return false;
    }
    else
    {
      request_out = request_queue_.front();
      request_queue_.pop();
      return true;
    }
  }

};

}

#endif
