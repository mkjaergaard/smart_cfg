#ifndef __PARAMETER_CHANGE_REQUEST_H_INCLUDED__
#define __PARAMETER_CHANGE_REQUEST_H_INCLUDED__

#include <smart_cfg_server/parameter_id_and_value.h>
#include <smart_cfg_server/deployed_component_id.h>
#include <smart_cfg_server/shared_from.h>

#include <vector>

class ParameterChangeRequest : public SharedFrom<ParameterChangeRequest>
{
public:
  typedef std::vector<ParameterIDAndValue> NewValuesListType;

protected:
  DeployedComponentID component_id_;
  NewValuesListType new_values_;

public:
  ParameterChangeRequest( DeployedComponentID component_id ) : component_id_(component_id)
  {
  }

  const DeployedComponentID& id() const
  {
    return component_id_;
  }

  void addValue( const ParameterIDAndValue& new_value )
  {
    new_values_.push_back( new_value );
  }

  const NewValuesListType& newValuesList() const
  {
    return new_values_;
  }

};

#endif
