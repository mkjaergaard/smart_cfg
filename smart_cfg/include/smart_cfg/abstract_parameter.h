#ifndef __ABSTRACT_PARAMETER_H_INCLUDED__
#define __ABSTRACT_PARAMETER_H_INCLUDED__

#include <string>
#include <smart_cfg_server/parameter_id_and_value.h>
#include <smart_cfg_server/parameter_status.h>

namespace smart_cfg
{

class ParameterizedComponent;

class AbstractParameter
{
protected:


public:
  AbstractParameter( ParameterizedComponent * owner );

  virtual bool isValid() = 0;
  virtual const ParameterID& getId() = 0;
  virtual void changeValue( const ParameterValue& new_value ) = 0;
 // virtual const ParameterValue& getValue() = 0;
//  virtual void getType( std::string& typeOut ) = 0;
 // virtual void getEncodedValue( std::string& encodedValueOut ) = 0;

};

}

#endif
