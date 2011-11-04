#ifndef __DEPLOYED_COMPONENT_H_INCLUDED__
#define __DEPLOYED_COMPONENT_H_INCLUDED__

#include <smart_cfg_server/shared_from.h>
#include <smart_cfg_server/parameter_id_and_value_ex.h>
#include <smart_cfg_server/deployed_component_id.h>
#include <smart_cfg_server/log.h>

#include <map>
#include <set>

namespace smart_cfg_server
{

// Forward Declaration
class DeployedComponentManager;

// Class Declaration
class DeployedComponent : public SharedFrom<DeployedComponent>
{

protected:
  DeployedComponentManager * parent_;
  DeployedComponentID id_;

  typedef std::map<ParameterID, ParameterIDAndValueEx::Ptr> ParameterMapType;
  ParameterMapType parameter_list_;

  typedef std::set<ParameterID> PendingChangesType;
  PendingChangesType pending_changes_set_;

public:
  DeployedComponent( DeployedComponentManager * parent, DeployedComponentID id );

  // Internal or from Mngr?
  void triggerPushChangesToComponents();

  ////////////////////////////////////////////////////
  // Nofity methods called from Middleware System Link
  ////////////////////////////////////////////////////
  void parameterValueReceivedNotify( const ParameterIDAndValue& param_in );


  ////////////////////////////////////////////////////
  // Nofity methods called from Middleware GUI Link
  ////////////////////////////////////////////////////
  void parameterValueOverrideRequest( const ParameterIDAndValue::ListOf& param_list );
  void triggerFullGuiUpdate();

  ////////////////////////////////////////////////////
  // Nofity methods called from Robot Model
  ////////////////////////////////////////////////////
  void parameterValueChangeRequest( const std::vector<ParameterIDAndValue>& param_list );


};

}

#endif
