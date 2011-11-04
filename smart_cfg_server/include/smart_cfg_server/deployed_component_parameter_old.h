#ifndef __DEPLOYED_COMPONENT_PARAMETER_H_INCLUDED__
#define __DEPLOYED_COMPONENT_PARAMETER_H_INCLUDED__

namespace smart_cfg_server
{

class DeployedComponentParameter
{
public:
  typedef enum {
    UNKNOWN,
    GUESS,
    MEASURE,
    CALIBRATION
  } SourceType;

  typedef enum {
    COMPONENT_ONLY,
    SYNC_PENDING,
    SYNCHRONIZED,
    OVERRIDDEN
  } StateType;

protected:
  StateType state_;


public:
  DeployedComponentParameter() : state_( COMPONENT_ONLY )
  {
  }


};

}

#endif
