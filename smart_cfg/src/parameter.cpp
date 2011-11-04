#include <smart_cfg/parameter.h>
#if 0
namespace smart_cfg
{

// Specialized implementation of setEncodedValue based on template argument



//////////
// Integer
//////////
template<>
bool Parameter<int>::setEncodedValue( const std::string& valueType, const std::string& encodedValue )
{
  // todo: very advanced parameter decoder
  assert(valueType == std::string("int"));
  int value = 0;
  if(sscanf(encodedValue.c_str(), "%d", &value) == EOF)
  {
     assert(false); //encoding error
  }
  return setValue(value);
}

template<>
void Parameter<int>::getEncodedValue( std::string& encodedValueOut )
{
  char buf[128];
  sprintf(buf, "%i", value_);
  encodedValueOut = std::string(buf);
}

template<>
void Parameter<int>::getType( std::string& typeOut )
{
  typeOut = "int";
}

/////////
// Double
/////////
template<>
bool Parameter<double>::setEncodedValue( const std::string& valueType, const std::string& encodedValue )
{
  // todo: very advanced parameter decoder
  assert(valueType == std::string("double") || valueType == std::string("float"));
  double value = 0.0;
  if(sscanf(encodedValue.c_str(), "%lf", &value) == EOF)
  {
     assert(false); //encoding error
  }
  return setValue(value);
}

template<>
void Parameter<double>::getEncodedValue( std::string& encodedValueOut )
{
  char buf[1024];
  sprintf(buf, "%10.5lf", value_);
  encodedValueOut = std::string(buf);
}

template<>
void Parameter<double>::getType( std::string& typeOut )
{
  typeOut = "double";
}

}

#endif

