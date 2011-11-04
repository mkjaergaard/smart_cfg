#ifndef __PARAMETER_VALUE_ABSTRACT_H_INCLUDED__
#define __PARAMETER_VALUE_ABSTRACT_H_INCLUDED__

#include <smart_cfg_server/shared_from.h>
#include <smart_cfg_server/parameter_status.h>

class ParameterValueAbstract : public SharedFrom<ParameterValueAbstract>
{
public:
  virtual const std::string& getType() const = 0;
  virtual const std::string getEncodedValue() const = 0;
  virtual void setFromEncodedValue( const std::string& encoded_value ) = 0;
  virtual const ParameterStatus::Type& getStatus() const = 0;
  virtual bool isKnown() const = 0;
};

#endif
