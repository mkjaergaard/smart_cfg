#include <smart_cfg_server/deployed_component_manager.h>

namespace smart_cfg_server
{

bool DeployedComponentManager::componentExists( const DeployedComponentID component_id )
{
  return (component_list_.count( component_id ) != 0);
}

void DeployedComponentManager::registerDeployedComponent( const DeployedComponentID component_id )
{
  if( component_list_.count( component_id ) == 0 )
  {
    DeployedComponent::Ptr tmp( new DeployedComponent(this, component_id) );
    component_list_[component_id] = tmp;
    Log::Info("Registered Component", component_id.getText().c_str());
  }
  else
  {
    // todo: special handling needed, or just ignore?
    // td::cout << "Component: " << component_id.getText() << " already registered" << std::endl;
    Log::Warning("Component already registered", component_id.getText().c_str());
  }
}

void DeployedComponentManager::registerChangeListener( boost::weak_ptr<IDeployedComponentStateChangeListener> change_listener )
{
  change_listener_ = change_listener;
}

void DeployedComponentManager::registerPushHandler( boost::weak_ptr<IDeployedComponentSystemPushHandler> push_handler )
{
  push_handler_ = push_handler;
}

// Override
void DeployedComponentManager::parameterValueOverrideRequest( DeployedComponentID component_id, const ParameterIDAndValue::ListOf& param_list)
{
  if( componentExists(component_id) )
  {
    component_list_[component_id]->parameterValueOverrideRequest( param_list );
  }
  else
  {
    // todo: special handling needed, or just ignore?
    std::cout << "Component: " << component_id.getText() << " not registered (Param override request)" << std::endl;
  }
}


// Called from System Link
void DeployedComponentManager::pushReplyReceivedNotify( const DeployedComponentID component_id, const ParameterIDAndValue& param )
{
  if( componentExists(component_id) )
  {
    component_list_[component_id]->parameterValueReceivedNotify( param );
  }
  else
  {
    // todo: special handling needed, or just ignore?
    std::cout << "Component: " << component_id.getText() << " not registered (Param value received)" << std::endl;
  }
}

// Called from?
void DeployedComponentManager::parameterValueChangeRequest( const DeployedComponentID component_id, const std::vector<ParameterIDAndValue>& param_list )
{
  if( componentExists(component_id) )
  {
    component_list_[component_id]->parameterValueChangeRequest( param_list );
  }
}

// Called from GUI Link
void DeployedComponentManager::triggerFullGuiUpdate( DeployedComponentID component_id )
{
  if( componentExists(component_id) )
  {
    component_list_[component_id]->triggerFullGuiUpdate();
  }
}

void DeployedComponentManager::parameterStateChangeNotify( const DeployedComponentID& component_id, ParameterIDAndValueEx::WeakConstPtrList& parameter_info )
{
  if( !change_listener_.expired() )
  {
    change_listener_.lock()->parameterStateChangeNotify(component_id, parameter_info);
  }
}

void DeployedComponentManager::pushChangesToComponents( ParameterChangeRequest::Ptr request )
{

}

void DeployedComponentManager::triggerPushChangesToComponents()
{
  for( ComponentListType::iterator it = component_list_.begin(); it != component_list_.end(); it++)
  {
    it->second->triggerPushChangesToComponents();
  }
}

}
