#include <smart_cfg_server/parameter_value_impl.h>

#include <stdio.h>

///////////////////////
// General
///////////////////////

///////////////////////
// Unset
///////////////////////
template<>
const std::string& ParameterValueImpl<UnsetValue>::getType() const
{
  return ParameterTypes::TYPE_unknown;
}

template<>
const std::string ParameterValueImpl<UnsetValue>::getEncodedValue() const
{
  return std::string("");
}

template<>
void ParameterValueImpl<UnsetValue>::setFromEncodedValue( const std::string& encoded_value )
{
}

///////////////////////
// Integer Type
///////////////////////
template<>
const std::string& ParameterValueImpl<int>::getType() const
{
  return ParameterTypes::TYPE_int;
}

template<>
const std::string ParameterValueImpl<int>::getEncodedValue() const
{
  // todo: use yaml encoding
  char buf[128];
  sprintf(buf, "%i", value_);
  return std::string(buf);
}

template<>
void ParameterValueImpl<int>::setFromEncodedValue( const std::string& encoded_value )
{
  if(sscanf(encoded_value.c_str(), "%d", &value_) == EOF)
  {
     assert(false); //encoding error
  }
}
///////////////////////
// Float Type
///////////////////////
template<>
const std::string& ParameterValueImpl<double>::getType() const
{
  return ParameterTypes::TYPE_float;
}

template<>
const std::string ParameterValueImpl<double>::getEncodedValue() const
{
  // todo: use yaml encoding
  char buf[128];
  sprintf(buf, "%lf", value_);
  return std::string(buf);
}

template<>
void ParameterValueImpl<double>::setFromEncodedValue( const std::string& encoded_value )
{
}
