#ifndef __PARAMETER_STATUS_H_INCLUDED__
#define __PARAMETER_STATUS_H_INCLUDED__

class ParameterStatus
{
public:
  typedef enum
  {
    OVERRIDDEN = 0,
    DEFAULT = 95,
    UNKNOWN = 98,
    MISSING = 99
  } Type;

protected:
  Type status_;

public:
  ParameterStatus( Type status = UNKNOWN ) :
    status_( status )
  {
  }

  const Type& status() const
  {
    return status_;
  }

  Type& status()
  {
    return status_;
  }

  bool isKnown() const
  {
    return (status_ != UNKNOWN) && (status_ != MISSING);
  }

};

#endif
