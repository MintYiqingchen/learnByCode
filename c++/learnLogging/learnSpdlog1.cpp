#include "template/output_container.hpp" // have to be included before spdlog

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

using namespace std;
using namespace spdlog::sinks;

void set_multi_sink()
{
  auto console_sink = make_shared<stdout_color_sink_mt>();
  console_sink->set_level(spdlog::level::warn);
  console_sink->set_pattern("%H:%M:%S.%e %^%L%$ %v");

  auto file_sink = make_shared<basic_file_sink_mt>("test.log");
  file_sink->set_level(spdlog::level::trace);
  file_sink->set_pattern("%Y-%m-%d %H:%M:%S.%f %L %v");

  auto logger = shared_ptr<spdlog::logger>(
      new spdlog::logger("multi_sink",{console_sink, file_sink}));
  logger->set_level(spdlog::level::debug);
  spdlog::set_default_logger(logger);
}

int main()
{
  set_multi_sink();
  spdlog::warn(
    "this should appear in both "
    "console and file");
  spdlog::info(
    "this message should not "
    "appear in the console, only "
    "in the file");
  std::vector<int> a{1,2,3}; // g++ -std=c++17 -lspdlog -I ../ learnSpdlog1.cpp
  spdlog::info("Content of a {}", a);
}