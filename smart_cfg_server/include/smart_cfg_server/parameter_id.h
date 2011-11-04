#ifndef ___PARAMETER_ID_H_INCLUDED__
#define ___PARAMETER_ID_H_INCLUDED__

#include <string>

class ParameterID
{
protected:
  std::string name_;

public:
  ParameterID( const std::string& id_text ) :
    name_( id_text )
  {
  }

  const std::string& getName() const
  {
    return name_;
  }

  const std::string& getAsText() const
  {
    return name_;
  }

  inline bool operator<(const ParameterID& rhs) const
  {
    return name_ < rhs.name_;
  }

};

#endif
