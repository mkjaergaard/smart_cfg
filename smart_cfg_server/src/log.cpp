#include <smart_cfg_server/log.h>

namespace smart_cfg_server
{

  ILogHandler * Log::handler_ = new ILogHandler();

}
