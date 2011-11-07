#ifndef __PARAMETER_H_INCLUDED__
#define __PARAMETER_H_INCLUDED__

#include <yaml-cpp/yaml.h>
#include <smart_cfg/abstract_parameter.h>
#include <smart_cfg/parameter_types.h>

class ParameterizedComponent;

namespace smart_cfg
{

template<typename T>
class Parameter : public AbstractParameter
{

protected:
  T value_;

public:
  Parameter( ParameterizedComponent * owner, const std::string& name ) :
    AbstractParameter( owner, name )
  {
  }

  virtual ~Parameter() {}

  // Getter
  const T& value() const
  {
    return value_;
  }

  const std::string& type() const
  {
    return ParameterTypes::typeOf<T>();
  }

  // Encoding
  bool setEncodedValue( const std::string& value_type, const std::string& encoded_value )
  {
    // check right type
    assert( value_type == ParameterTypes::typeOf<T>() );

    // todo: do some try/catch
    std::stringstream encoded_stream(encoded_value);
    YAML::Parser parser(encoded_stream);

    YAML::Node node;
    if (parser.GetNextDocument(node))
    {
      node >> value_;
      return true;
    }
    else
    {
      // return false;
      assert(false);
    }
  }

  bool getEncodedValue( std::string& encoded_value_out ) const
  {
    YAML::Emitter yaml_encoded;
    yaml_encoded << value_;
    encoded_value_out = yaml_encoded.c_str();
    return true;
  }

};

}

#endif
