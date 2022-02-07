/**
 * @file Input.h
 * @author Guy Burroughes
 * @brief
 * @version 0.1
 * @date 2022-01-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
/// \cond
#include <errno.h>
#include <poll.h>
#include <rclcpp/rclcpp.hpp>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <thread>
#include <unistd.h>
/// \endcond

std::string readStdIn(std::shared_ptr<std::atomic<bool>> st) {
  struct pollfd pfd = {STDIN_FILENO, POLLIN, 0};

  std::string line;
  int ret = 0;
  while (ret == 0 && rclcpp::ok() && !*st) {
    ret = poll(&pfd, 1, 200); // timeout of 1000ms
    if (ret == 1)             // there is something to read
    {
      std::getline(std::cin, line);
    } else if (ret == -1) {
      std::cout << "Error: " << strerror(errno) << std::endl;
    }
  }
  return line;
}

/**
 * @brief Wait until keyboard input, while running ROS spin
 *
 * @param executor
 * @return true if Y or y is entered into stdin
 * @return false if anything else is entered
 */
bool spin_till_input(rclcpp::executors::MultiThreadedExecutor *executor,
                     std::shared_ptr<std::atomic<bool>> st) {
  /**
   * @brief input from stdin for async
   *
   */
  auto read_input = [=]() {
    std::string input;
    while (input.empty() && rclcpp::ok() && !*st) {
      input = readStdIn(st);
    }
    return input;
  };
  std::shared_future<std::string> future_input;
  future_input = std::async(read_input);
  executor->spin_until_future_complete(future_input);
  if (!rclcpp::ok()) {

    return false;
  }
  {
    auto s = future_input.get();
    if (s == "Y" || s == "y" || st) {
      *st = false;
      return true;
    }
  }
  return false;
}

/**6
 * @brief input from stdin for async
 *
 */
auto ignore_input = []() {
  std::string input;
  auto systemRet = system("bash -c 'read -N1'");
  if (systemRet == -1) {
    // The system method failed
    return input;
  }
  return input;
};

/**
 * @brief Wait until keyboard input, while running ROS spin
 *
 * @param executor
 */
void execute_till_keypress(rclcpp::executors::MultiThreadedExecutor *executor) {
  std::shared_future<std::string> future_input;
  future_input = std::async(ignore_input);
  executor->spin_until_future_complete(future_input);
}

/**
 * @brief Set the environment variable for LD_LIBRARY PATH for ROS2 in appimages
 *
 */
void set_env_var() {
  std::stringstream s;
  auto ld_library_path_str = getenv("LD_LIBRARY_PATH");
  if (ld_library_path_str) {
    s << ld_library_path_str;
  }
  auto appdir_str = getenv("APPDIR");
  if (ld_library_path_str && appdir_str) {
    s << ":";
  }
  if (appdir_str) {
    s << appdir_str << "/usr/lib";
  }
  setenv("LD_LIBRARY_PATH", s.str().c_str(), true);
}