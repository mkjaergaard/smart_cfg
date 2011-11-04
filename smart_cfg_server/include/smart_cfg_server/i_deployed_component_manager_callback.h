#ifndef __I_DEPLOYED_COMPONENT_MANAGER_CALLBACK_H_INCLUDED__
#define __I_DEPLOYED_COMPONENT_MANAGER_CALLBACK_H_INCLUDED__

#include <smart_cfg_server/parameter_id_and_value.h>

namespace smart_cfg_server
{

class IDeployedComponentManagerCallback
{
public:
  virtual void parameterValueReceivedNotify( const std::string& component_name, const ParameterIDAndValue& param ) = 0;

};

}

#endif
