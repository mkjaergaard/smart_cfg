#ifndef __COMPONENT_MODEL_H_INCLUDED__
#define __COMPONENT_MODEL_H_INCLUDED__

#include "component_model_parameter.h"

#include <vector>
#include <assert.h>

namespace smart_cfg_server
{

class ComponentModel
{

protected:
  std::string name_;

  typedef std::vector<AbstractComponentModelParameter*> ParameterListType;
  ParameterListType parameter_list_;

public:
  ComponentModel() {}

  void parseYAML(const YAML::Node& node)
  {
    node["name"] >> name_;
    std::cout << "Parsing Model: " << name_ << std::endl;
    parseParameters(node["parameters"]);
  }

  void parseParameters(const YAML::Node& parameter_list_node)
  {
    for(unsigned i=0; i<parameter_list_node.size(); i++)
    {
      parseParameter(parameter_list_node[i]);
    }
  }

  void parseParameter(const YAML::Node& parameter_node)
  {
    AbstractComponentModelParameter * param = 0;
    std::string name;
    std::string type;
    std::string value;
    parameter_node["name"] >> name;
    parameter_node["type"] >> type;
    if( type == "int" )
    {
      param = new ComponentModelParameter<int>(name);
    }
    else if( type == "float")
    {
      param = new ComponentModelParameter<float>(name);
    }
    else
    {
      assert(0);
    }

    const YAML::Node * value_node = parameter_node.FindValue("value");
    const YAML::Node * source_node = parameter_node.FindValue("source");
    const YAML::Node * derive_node = parameter_node.FindValue("derive");
    if( value_node != 0 )
    {
      param->setConstantValueFromYAML( *value_node );
    }
    if( source_node != 0 )
    {
      param->setSourceFromYAML( *source_node );
    }
    if( derive_node != 0 )
    {
      param->setDeriveRuleFromYAML( *derive_node );
    }
    std::cout << "Parameter: " << name << std::endl;
    parameter_list_.push_back(param);
  }

};

}
// now the extraction operators for these types
void operator >> (const YAML::Node& node, smart_cfg_server::ComponentModel& model)
{
  model.parseYAML(node);
}


#endif
