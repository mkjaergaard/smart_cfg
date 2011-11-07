#include <smart_cfg/abstract_parameter.h>
#include <smart_cfg/parameterized_component.h>

namespace smart_cfg
{

AbstractParameter::AbstractParameter( ParameterizedComponent * owner, const std::string& name ):
  name_( name ),
  changed_( false )
{
  owner->registerParameter(this);
}

ParameterStatus::Type& AbstractParameter::status()
{
  return status_.status();
}

const ParameterStatus::Type& AbstractParameter::status() const
{
  return status_.status();
}

const std::string& AbstractParameter::name() const
{
  return name_;
}

bool AbstractParameter::hasChanged() const
{
  return changed_;
}

// Setter

void AbstractParameter::changeHandled()
{
  changed_ = false;
}

bool AbstractParameter::isValid() const
{
  return status_.isKnown();
}

}
