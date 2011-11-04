#ifndef __COMPONENT_MODEL_PARAMETER_H_INCLUDED__
#define __COMPONENT_MODEL_PARAMETER_H_INCLUDED__

#include "abstract_component_model_parameter.h"
#include <yaml-cpp/yaml.h>

namespace smart_cfg_server
{

template<typename T>
class ComponentModelParameter : public AbstractComponentModelParameter
{
protected:
  std::string name_;
  T value_;

  virtual void setConstantValueFromYAML( const YAML::Node& yaml )
  {
    // todo: catch exceptions
    yaml >> value_;

    std::cout << "Value is: " << value_ << std::endl;
  }

public:
  ComponentModelParameter(const std::string& name) : name_(name)
  {
  }
};

}

#endif
