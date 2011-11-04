#ifndef __I_DEPLOYED_COMPONENT_CHANGE_LISTENER_H_INCLUDED__
#define __I_DEPLOYED_COMPONENT_CHANGE_LISTENER_H_INCLUDED__

#include <smart_cfg_server/shared_from.h>
#include <smart_cfg_server/deployed_component_id.h>
#include <smart_cfg_server/parameter_id_and_value_ex.h>

namespace smart_cfg_server
{

class IDeployedComponentStateChangeListener
{
public:
  virtual void parameterStateChangeNotify( const DeployedComponentID& component_id, ParameterIDAndValueEx::WeakConstPtrList& parameter_info ) = 0;

  virtual ~IDeployedComponentStateChangeListener()
  {
  }
};

}

#endif
