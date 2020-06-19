#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

int main()
{
  spdlog::info("My first info log"); // g++ -lspdlog -DSPDLOG_COMPILED_LIB learnSpdlog.cpp
  spdlog::warn("Message with arg {}", 42);
  spdlog::error("{0:d}, {0:x}, {0:o}, {0:b}",42);
  auto file_logger = spdlog::basic_logger_mt("basic_logger", "test.log"); // set log file
  spdlog::set_default_logger(file_logger);
  spdlog::info("Into file: {1} {0}","world", "hello");
} 