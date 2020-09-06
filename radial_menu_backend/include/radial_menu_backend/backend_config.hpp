#ifndef RADIAL_MENU_BACKEND_BACKEND_CONFIG_HPP
#define RADIAL_MENU_BACKEND_BACKEND_CONFIG_HPP

#include <string>
#include <memory>
#include <rclcpp/rclcpp.hpp>

namespace radial_menu_backend {

struct BackendConfig {
  BackendConfig()
      : allow_multi_selection(false), reset_on_enabling(false), reset_on_disabling(false),
        auto_select(false), enable_button(/* PS4's circle*/ 1), select_button(/* PS4's R1 */ 5),
        ascend_button(/* PS4's L1 */ 4), pointing_axis_v(/* PS4's LEFT Y */ 1),
        pointing_axis_h(/* PS4's LEFT X */ 0), invert_pointing_axis_v(false),
        invert_pointing_axis_h(false), pointing_axis_threshold(0.5) {}

  static BackendConfig fromParam(std::shared_ptr<rclcpp::SyncParametersClient> param) {
    BackendConfig config;
    config.allow_multi_selection = param->get_parameter("allow_multi_selection", false);
    config.reset_on_enabling = param->get_parameter("reset_on_enabling", false);
    config.reset_on_disabling = param->get_parameter("reset_on_disabling", false);
    config.auto_select = param->get_parameter("auto_select", false);
    config.enable_button = param->get_parameter("enable_button", 1);
    config.select_button = param->get_parameter("select_button", 5);
    config.ascend_button = param->get_parameter("ascend_button", 4);
    config.pointing_axis_v = param->get_parameter("pointing_axis_v", 1);
    config.invert_pointing_axis_v = param->get_parameter("invert_pointing_axis_v", false);
    config.pointing_axis_h = param->get_parameter("pointing_axis_h", 0);
    config.invert_pointing_axis_h = param->get_parameter("invert_pointing_axis_h", false);
    config.pointing_axis_threshold = param->get_parameter("pointing_axis_threshold", 0.5);
    return config;
  }

  bool allow_multi_selection;
  bool reset_on_enabling;
  bool reset_on_disabling;
  bool auto_select;
  int enable_button;
  int select_button;
  int ascend_button;
  int pointing_axis_v, pointing_axis_h;
  bool invert_pointing_axis_v, invert_pointing_axis_h;
  double pointing_axis_threshold;
};
} // namespace radial_menu_backend

#endif