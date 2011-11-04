#ifndef __I_DEPLOYED_COMPONENT_MANAGER_CALLBACK_H_INCLUDED__
#define __I_DEPLOYED_COMPONENT_MANAGER_CALLBACK_H_INCLUDED__

#include <smart_cfg_server/parameter_id_and_value.h>
#include <smart_cfg_server/deployed_component_id.h>
#include <smart_cfg_server/shared_from.h>

namespace smart_cfg_server
{

class IDeployedComponentPushReplyListener
{
public:
  virtual void pushReplyReceivedNotify( DeployedComponentID component_id, const ParameterIDAndValue& param ) = 0;

};

}

#endif
