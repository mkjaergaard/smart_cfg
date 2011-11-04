#ifndef __MIDDLEWARE_GUI_LINK_H_INCLUDED__
#define __MIDDLEWARE_GUI_LINK_H_INCLUDED__

#include <smart_cfg_server/deployed_component_manager.h>
#include <smart_cfg_server/shared_from.h>
#include <boost/shared_ptr.hpp>
#include <smart_cfg_server/i_deployed_component_state_change_listener.h>

namespace smart_cfg_server
{

class MiddlewareGuiLink : public SharedFrom<MiddlewareGuiLink>, public IDeployedComponentStateChangeListener
{
protected:
  //DeployedComponentManager::WeakPtr deployed_component_mngr_;
  boost::weak_ptr<DeployedComponentManager> deployed_component_mngr_;

  MiddlewareGuiLink()
  {
  }

public:
  // Initialization
  void registerDeployedComponentManager( boost::weak_ptr<DeployedComponentManager> deployed_component_mngr)
  {
    deployed_component_mngr_ = deployed_component_mngr;
  }

};

}

#endif
