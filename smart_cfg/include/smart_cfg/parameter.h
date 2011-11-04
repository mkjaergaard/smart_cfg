#ifndef __PARAMETER_H_INCLUDED__
#define __PARAMETER_H_INCLUDED__

#include <smart_cfg/abstract_parameter.h>
#include <smart_cfg_server/parameter_value_impl.h>
#include <boost/weak_ptr.hpp>

class ParameterizedComponent;

namespace smart_cfg
{

template<typename T>
class Parameter : public AbstractParameter
{

protected:
  ParameterID id_;
  ParameterValueImpl<T> value_;
  bool changed_;
  boost::weak_ptr<ParameterizedComponent> somep;

public:
  Parameter( ParameterizedComponent * owner, const std::string name ) :
    AbstractParameter( owner ),
    id_( name ),
    changed_( false )
  {
  }

  const T& value() const
  {
    return value_->value();
  }

  bool hasChanged()
  {
    return changed_;
  }

  void changeValue( const ParameterValue& new_value )
  {
    if( new_value.isKnown() )
    {
      boost::shared_ptr<const ParameterValueImpl<T> > t_impl = new_value.getImpl<T>();
      // Verify that the types are matching
      if( t_impl.get() != 0 )
      {
        value_ = *t_impl;
        changed_ = true;
      }
    }
  }

  void changeHandled()
  {
    changed_ = false;
  }

  bool isValid()
  {
    return value_.isKnown();
  }

  const ParameterID& getId()
  {
    return id_;
  }
/*
  const ParameterValueAbstract& getValue()
  {
    return value_;
  }
*/
};

}

#endif
