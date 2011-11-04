#ifndef __PARAMETERIZED_COMPONENT_H_INCLUDED__
#define __PARAMETERIZED_COMPONENT_H_INCLUDED__

#include <smart_cfg_server/parameter_id_and_value.h>
#include <smart_cfg/controlled_component.h>
#include <smart_cfg/parameter.h>

#include <map>

namespace smart_cfg
{

class ParameterizedComponent : public virtual ControlledComponent
{

protected:
  typedef std::map<ParameterID, AbstractParameter*> ParameterListType;
  ParameterListType parameter_list_;

  // Initialization/Construction methods used by the derived class.

  void registerParameter( AbstractParameter * param )
  {
    // todo: check for already registered
    parameter_list_[param->getId()] = param;
  }

  // Virtual Methods the derived class can override.

  /**
   * Called on the class when one of the components parameters has changed value.
   */
  virtual void notifyParametersHasChanged()
  {
  }

  bool setParameterValue( const std::string& paramName, const std::string& valueType, const std::string& encodedValue )
  {
    ParameterID param_id( paramName );

    ParameterListType::iterator elem = parameter_list_.find(param_id);

    if( elem != parameter_list_.end() )
    {
      ParameterValue param_value;
      param_value.setFromEncodedValue( encodedValue, valueType );
      (elem->second)->changeValue(param_value);
      return true;
    }
    else
    {
      return false;
    }
  }

  bool parametersReady()
  {
    for( ParameterListType::iterator it = parameter_list_.begin(); it != parameter_list_.end(); it++ )
    {
      if( !(*it).second->isValid() )
      {
        return false;
      }
    }
    return true;
  }

  bool verifyInitializing()
  {
    return parametersReady();
  }

  friend class AbstractParameter;

};

}

#endif
