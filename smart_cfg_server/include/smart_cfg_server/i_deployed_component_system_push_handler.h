#ifndef I_DEPLOYED_COMPONENT_SYSTEM_PUSH_HANDLER_H
#define I_DEPLOYED_COMPONENT_SYSTEM_PUSH_HANDLER_H

#include <smart_cfg_server/parameter_change_request.h>
#include <smart_cfg_server/shared_from.h>

namespace smart_cfg_server
{

class IDeployedComponentSystemPushHandler
{
public:
  virtual void pushChangeRequest( ParameterChangeRequest::ConstPtr request ) = 0;
};

}

#endif
