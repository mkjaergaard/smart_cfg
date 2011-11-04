#ifndef __CONTROLLED_COMPONENT_H_INCLUDED__
#define __CONTROLLED_COMPONENT_H_INCLUDED__

namespace smart_cfg
{

class ControlledComponent
{
private:
  // Control stuff
  typedef enum  { INITIALIZING, RUNNING, IDLE, STOPPED } statetype;
  statetype state_;

protected:
  ControlledComponent() :
    state_( INITIALIZING )
  {
  }

  bool isRunning()
  {
    return state_ == RUNNING;
  }

  bool isInitialized()
  {
    return state_ != INITIALIZING;
  }

  void work()
  {
    switch( state_ )
    {
      case INITIALIZING:
        if( verifyInitializing() )
        {
          state_ = RUNNING;
          initializedEventHandler();
        }
        break;
      default:
        break;
    }
  }

  virtual void initializedEventHandler()
  {
  }

  virtual bool verifyInitializing()
  {
    return true;
  }

  const statetype& getState()
  {
    return state_;
  }


public:

};

}

#endif
