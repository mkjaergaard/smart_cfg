#ifndef __PARAMETER_VALUE_H_INCLUDED__
#define __PARAMETER_VALUE_H_INCLUDED__

#include <smart_cfg_server/parameter_value_impl.h>

#include <boost/shared_ptr.hpp>

class ParameterValue
{
public:

protected:
  ParameterValueAbstract::Ptr impl_;

public:
  ParameterValue( ParameterStatus::Type status = ParameterStatus::UNKNOWN ) :
    impl_( new ParameterValueImpl<>( status ))
  {
  }

  template<typename T>
  void setFromValue( const T& value, ParameterStatus::Type status = ParameterStatus::UNKNOWN )
  {
    impl_.reset( new ParameterValueImpl<T>(value, status) );
  }

  template<typename T>
  boost::shared_ptr<const ParameterValueImpl<T> > getImpl() const
  {
    return boost::shared_dynamic_cast<ParameterValueImpl<T>, ParameterValueAbstract>(impl_);
  }

  void setFromEncodedValue( const std::string& encoded_value, const std::string& type )
  {
    impl_ = ParameterValueImpl<>::createFromType(type);
    impl_->setFromEncodedValue( encoded_value );
  }

  const std::string getType() const
  {
    // todo: check for 0-pointer
    return impl_->getType();
  }

  const std::string getEncodedValue() const
  {
    // todo: check for 0-pointer
    return impl_->getEncodedValue();
  }

  const ParameterStatus::Type& getStatus() const
  {
    return impl_->getStatus();
  }

  bool isKnown() const
  {
    return impl_->isKnown();
  }

};

#endif
