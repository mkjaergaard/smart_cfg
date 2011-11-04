#ifndef __ABSTRACT_COMPONENT_MODEL_PARAMETER_H_INCLUDED__
#define __ABSTRACT_COMPONENT_MODEL_PARAMETER_H_INCLUDED__

#include <assert.h>
#include <string>
#include <yaml-cpp/yaml.h>

namespace smart_cfg_server
{

class AbstractComponentModelParameter
{
protected:
  std::string name_;
  typedef enum {
    UNKNOWN,
    GUESS,
    MEASURE,
    CALIBRATION
  } SourceType;

  SourceType source_;

public:

  virtual void setConstantValueFromYAML( const YAML::Node& yaml ) = 0;

  void setSourceFromYAML( const YAML::Node& yaml )
  {
    std::string source_str;
    yaml >> source_str;
    if( source_str == "guess")
    {
      source_ = GUESS;
    }
    else
    {
      assert(0);
    }
    std::cout << "Source is: " << (int)source_ << std::endl;
  }

  void setDeriveRuleFromYAML( const YAML::Node& yaml )
  {

  }

};

}

#endif
