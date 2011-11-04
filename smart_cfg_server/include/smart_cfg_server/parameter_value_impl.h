#ifndef __PARAMETER_VALUE_IMPL_H_INCLUDED__
#define __PARAMETER_VALUE_IMPL_H_INCLUDED__

#include <smart_cfg_server/parameter_value_abstract.h>
#include <smart_cfg_server/parameter_status.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <smart_cfg_server/parameter_types.h>

class UnsetValue {};

template<typename T = UnsetValue>
class ParameterValueImpl : public ParameterValueAbstract
{
public:
  typedef boost::shared_ptr<ParameterValueAbstract> AbstractPtr;

protected:
  T value_;
  ParameterStatus status_;

public:
  ParameterValueImpl() :
    value_(),
    status_( ParameterStatus::UNKNOWN )
  {
  }

  ParameterValueImpl(const T& value, const ParameterStatus::Type status = ParameterStatus::UNKNOWN) :
    value_(value),
    status_( status )
  {
  }

  ParameterValueImpl(const ParameterStatus::Type status) :
    value_(),
    status_( status )
  {
  }

  static boost::shared_ptr<ParameterValueAbstract> createFromType( const std::string& type )
  {
    if( type == ParameterTypes::TYPE_int )
    {
      return boost::shared_ptr<ParameterValueAbstract>( new ParameterValueImpl<int>() );
    }
    else if( type == ParameterTypes::TYPE_float )
    {
      return boost::shared_ptr<ParameterValueAbstract>( new ParameterValueImpl<double>() );
    }
    else // if( type == ParameterTypes::TYPE_unknown )
    {
      return boost::shared_ptr<ParameterValueAbstract>( new ParameterValueImpl<UnsetValue>() );
    }
  }

  T& value()
  {
    return value_;
  }

  const T& value() const
  {
    return value_;
  }

  const ParameterStatus::Type& getStatus() const
  {
    return status_.status();
  }

  bool isKnown() const
  {
    return (status_.status() != ParameterStatus::UNKNOWN) && (status_.status() != ParameterStatus::MISSING);
  }

  virtual const std::string& getType() const;
  virtual const std::string getEncodedValue() const;
  virtual void setFromEncodedValue( const std::string& encoded_value );
};

#endif
