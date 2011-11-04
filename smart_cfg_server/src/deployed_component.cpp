#include <smart_cfg_server/deployed_component.h>

#include <smart_cfg_server/deployed_component_manager.h>
#include <smart_cfg_server/parameter_change_request.h>

namespace smart_cfg_server
{

DeployedComponent::DeployedComponent( DeployedComponentManager * parent, DeployedComponentID id ) :
  parent_( parent ),
  id_( id )
{
}

////////////////////////////////////////////////////
// Nofity methods called from Middleware System Link
////////////////////////////////////////////////////
void DeployedComponent::parameterValueReceivedNotify( const ParameterIDAndValue& param_in )
{
  Log::Info("parameterValueReceivedNotify", param_in.getName());
  // Check if it is known
  ParameterMapType::iterator current_it = parameter_list_.find( param_in.id() );
  if( current_it != parameter_list_.end() )
  {
    ParameterIDAndValueEx::Ptr& current = current_it->second;
    if( current->hasPendingChange() )
    {
      // todo: check if the value is correct
      current->newValue() = param_in.value();
      current->clearPendingChange();
    }
    else
    {
      current->newValue() = param_in.value();
    }
  }
  else
  {
    ParameterIDAndValueEx::Ptr current( new ParameterIDAndValueEx(param_in.id()) );
    current->value() = param_in.value();
    parameter_list_[param_in.id()] = current;
  }

  std::cout << "Set some value" << std::endl;
}

////////////////////////////////////////////////////
// Methods called from Middleware GUI Link
////////////////////////////////////////////////////
void DeployedComponent::parameterValueOverrideRequest( const ParameterIDAndValue::ListOf& change_list )
{
  // Save all changed entries in a list
  ParameterIDAndValueEx::WeakConstPtrList changed_list;

  // Iterate through the list of requested changes
  for( ParameterIDAndValue::ListOf::const_iterator in_it = change_list.begin(); in_it != change_list.end(); in_it++ )
  {
    // Easy access to iteration element
    const ParameterIDAndValue& param_in = (*in_it);

    // Find matching entry in parameter list
    ParameterMapType::iterator elem_it = parameter_list_.find(param_in.id());
    if( elem_it != parameter_list_.end() )
    {
      // Easy access to found element
      ParameterIDAndValueEx::Ptr& param_elem = elem_it->second;

      // Register the requested change
      param_elem->change( param_in.value() );
      pending_changes_set_.insert( param_elem->id() );
      changed_list.push_back( ParameterIDAndValueEx::WeakConstPtr(param_elem) );
      // todo: how to schedule sending update? // create timeout queue class
    }
    else
    {
      // Add the parameter as "missing"
      ParameterIDAndValueEx::Ptr param_elem( new ParameterIDAndValueEx( param_in.id()) );
      param_elem->value() = ParameterValue( ParameterStatus::MISSING );
      param_elem->change( param_in.value() );
      parameter_list_[ param_elem->id() ] = param_elem;
      pending_changes_set_.insert( param_elem->id() );
      changed_list.push_back( ParameterIDAndValueEx::WeakConstPtr(param_elem) );
    }

    // Tell the GUI that we have some changes to show
    parent_->parameterStateChangeNotify( id_, changed_list );

    triggerPushChangesToComponents();
  }
}

////////////////////////////////////////////////////
// Methods called from Robot Model
////////////////////////////////////////////////////
void DeployedComponent::parameterValueChangeRequest( const std::vector<ParameterIDAndValue>& param_list )
{
  // todo: Check for exsisting request
  //requested_value_list_[param.getName()] = param.value();
}

//// Internal?
void DeployedComponent::triggerFullGuiUpdate()
{
  Log::Info("triggerFullGuiUpdate");
  ParameterIDAndValueEx::WeakConstPtrList list;
  for ( ParameterMapType::iterator it = parameter_list_.begin(); it != parameter_list_.end(); it++ )
  {
    ParameterIDAndValueEx::WeakConstPtr p(it->second);
    list.push_back(p);
  }
  parent_->parameterStateChangeNotify( id_, list );
}

void DeployedComponent::triggerPushChangesToComponents()
{
  if( !pending_changes_set_.empty() )
  {
    Log::Info("pushChangesToComponents");

    ParameterChangeRequest::Ptr request( new ParameterChangeRequest(id_) );
    for( PendingChangesType::iterator it = pending_changes_set_.begin(); it != pending_changes_set_.end(); it++ )
    {
      const ParameterID& parameter_id = (*it);
      ParameterIDAndValue new_value( parameter_id, parameter_list_[parameter_id]->newValue() );
      request->addValue(new_value);
    }
    parent_->pushChangesToComponents( request );
  }
}

}

