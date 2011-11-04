#ifndef __PARAMETER_ID_AND_VALUE_H_INCLUDED__
#define __PARAMETER_ID_AND_VALUE_H_INCLUDED__

#include <smart_cfg_server/parameter_id.h>
#include <smart_cfg_server/parameter_value.h>

class ParameterIDAndValue
{
public:
  typedef std::vector<ParameterIDAndValue> ListOf;

protected:
  ParameterID id_;
  ParameterValue value_;

public:
  ParameterIDAndValue( const ParameterIDAndValue& src ) :
    id_( src.id_ ),
    value_( src.value_)
  {
  }

  ParameterIDAndValue( const ParameterID& id ) :
    id_( id )
  {
  }

  ParameterIDAndValue( const ParameterID& id, const ParameterValue& value ) :
    id_( id ),
    value_(value)
  {
  }

  const std::string& getName() const
  {
    return id_.getName();
  }

  const ParameterID& id() const
  {
    return id_;
  }

  const ParameterValue& value() const
  {
    return value_;
  }

  ParameterValue& value()
  {
    return value_;
  }

};

#endif
