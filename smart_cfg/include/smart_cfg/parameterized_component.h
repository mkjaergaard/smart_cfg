#ifndef __PARAMETERIZED_COMPONENT_H_INCLUDED__
#define __PARAMETERIZED_COMPONENT_H_INCLUDED__

#include <map>

#include <smart_cfg/controlled_component.h>
#include <smart_cfg/parameter.h>

namespace smart_cfg
{

class ParameterizedComponent : public virtual ControlledComponent
{

protected:
  typedef std::map<std::string, AbstractParameter*> ParameterListType;
  ParameterListType parameter_list_;

  // Initialization/Construction methods used by the derived class.
  ~ParameterizedComponent() {}

  void registerParameter( AbstractParameter * param )
  {
    // todo: check for already registered
    parameter_list_[param->name()] = param;
  }

  // Virtual Methods the derived class can override.

  /**
   * Called on the class when one of the components parameters has changed value.
   */
  virtual void notifyParametersHasChanged()
  {
  }

  bool setParameterValue( const std::string& param_name, const std::string& value_type, const std::string& encoded_value )
  {
    ParameterListType::iterator elem = parameter_list_.find(param_name);

    if( elem != parameter_list_.end() )
    {
      (elem->second)->setEncodedValue(value_type, encoded_value);
      return true;
    }
    else
    {
      assert(false);
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
