#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#else
#include <locale>
#endif
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

int main()
{
  LOG(INFO) << "My first info log"; // g++ -std=c++17 elppExample.cpp easylogging++.cc
#ifdef _WIN32
  _setmode(_fileno(stdout),
           _O_WTEXT);
#else
  using namespace std;
  locale::global(locale(""));
  wcout.imbue(locale());
#endif

  LOG(INFO) << L"测试 test"; // g++ -std=c++17 -D ELPP_UNICODE elppExample.cpp easylogging++.cc
  LOG(INFO) << "Narrow ASCII always OK";
  // configuration file
  el::Configurations conf{"elpp.config"}; // -DELPP_NO_DEFAULT_LOG_FILE 则不生成默认配置文件
  el::Loggers::reconfigureAllLoggers(conf);
  LOG(DEBUG) << "A debug message";
  LOG(INFO) << "An info message";
}
