#ifndef __ABSTRACT_PARAMETER_H_INCLUDED__
#define __ABSTRACT_PARAMETER_H_INCLUDED__

#include <string>
#include <smart_cfg/parameter_types.h>
#include <smart_cfg/parameter_status.h>

namespace smart_cfg
{

class ParameterizedComponent;

class AbstractParameter
{
protected:
  ParameterStatus status_;
  std::string name_;
  bool changed_;

public:
  AbstractParameter( ParameterizedComponent * owner, const std::string& name );
  virtual ~AbstractParameter() {}

  // Acces methods
  ParameterStatus::Type& status();
  const ParameterStatus::Type& status() const;
  bool isValid() const;
  const std::string& name() const;
  bool hasChanged() const;
  void changeHandled();

  // Impl by Parameter
  virtual bool setEncodedValue( const std::string& valueType, const std::string& encodedValue ) = 0;
  virtual bool getEncodedValue( std::string& encodedValueOut ) const = 0;
  virtual const std::string& type() const = 0;

};

}

#endif
