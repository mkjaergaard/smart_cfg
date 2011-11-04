#ifndef __PARAMETER_ID_AND_VALUE_EX_H_INCLUDED__
#define __PARAMETER_ID_AND_VALUE_EX_H_INCLUDED__

#include <smart_cfg_server/parameter_id_and_value.h>
#include <smart_cfg_server/shared_from.h>

class ParameterIDAndValueEx : public ParameterIDAndValue, public SharedFrom<ParameterIDAndValueEx>
{
protected:
  bool change_request_;
  ParameterValue requested_value_;

public:
  ParameterIDAndValueEx( const ParameterID& id ) :
    ParameterIDAndValue( id ),
    change_request_(false)
  {
  }

  const ParameterValue& newValue() const
  {
    return requested_value_;
  }

  ParameterValue& newValue()
  {
    return requested_value_;
  }

  const bool& hasPendingChange() const
  {
    return change_request_;
  }

  void clearPendingChange()
  {
    change_request_ = false;
    requested_value_ = ParameterValue();
  }

  void change( const ParameterValue& new_value )
  {
    change_request_ = true;
    requested_value_ = new_value;
  }

};

#endif
