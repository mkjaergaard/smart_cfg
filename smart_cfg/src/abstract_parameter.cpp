#include <smart_cfg/abstract_parameter.h>
#include <smart_cfg/parameterized_component.h>

namespace smart_cfg
{

AbstractParameter::AbstractParameter( ParameterizedComponent * owner )
{
  owner->registerParameter(this);
}

}
