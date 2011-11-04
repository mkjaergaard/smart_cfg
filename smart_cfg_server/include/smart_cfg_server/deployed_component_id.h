#ifndef __DEPLOYED_COMPONENT_ID_H_INCLUDED__
#define __DEPLOYED_COMPONENT_ID_H_INCLUDED__

#include <boost/shared_ptr.hpp>
#include <string>

class DeployedComponentID
{
protected:
  boost::shared_ptr<std::string> id_txt_;

public:
  DeployedComponentID( const std::string& id_txt )
  {
    id_txt_.reset( new std::string(id_txt));
  }

  bool operator==( const DeployedComponentID& rhs)
  {
    return rhs.getText() == this->getText();
  }

  inline bool operator<(const DeployedComponentID& rhs) const
  {
    return this->getText() < rhs.getText();
  }

  const std::string& getText() const
  {
    return *(id_txt_.get());
  }

};

#endif
