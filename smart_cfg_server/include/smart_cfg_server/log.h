#ifndef __LOG_H_INCLUDED__
#define __LOG_H_INCLUDED__

#include <iostream>

namespace smart_cfg_server
{

class ILogHandler
{
public:
  virtual void Info( const std::string& msg )
  {
    std::cout << "-Info- " << msg << std::endl;
  }

  virtual void Info( const std::string& msg1, const std::string& msg2 )
  {
    std::cout << "-Info- " << msg1 << " : " << msg2 << std::endl;
  }

  virtual void Warning( const std::string& msg )
  {
    std::cout << "-Warn- " << msg << std::endl;
  }

  virtual void Warning( const std::string& msg1, const std::string& msg2 )
  {
    std::cout << "-Warn- " << msg1 << " : " << msg2 << std::endl;
  }

  virtual void Error( const std::string& msg )
  {
    std::cout << "-Err- " << msg << std::endl;
  }

};


class Log
{
protected:
  static ILogHandler * handler_;

public:
  static void Info( const std::string& msg )
  {
    handler_->Info(msg);
  }

  static void Info( const std::string& msg1, const std::string& msg2 )
  {
    handler_->Info(msg1, msg2);
  }

  static void Warning( const std::string& msg)
  {
    handler_->Warning(msg);
  }

  static void Warning( const std::string& msg1, const std::string& msg2 )
  {
    handler_->Warning(msg1, msg2);
  }

  static void Error( const std::string& msg)
  {
    handler_->Error(msg);
  }

};

}

#endif
