#ifndef RADIAL_MENU_BACKEND_BACKEND_CONFIG_HPP
#define RADIAL_MENU_BACKEND_BACKEND_CONFIG_HPP

#include <string>

namespace radial_menu_backend {

struct BackendConfig {
  BackendConfig()
      : allow_multi_selection(false), reset_on_enabling(false), reset_on_disabling(false),
        auto_select(false), enable_button(/* PS4's circle*/ 1), select_button(/* PS4's R1 */ 5),
        ascend_button(/* PS4's L1 */ 4), pointing_axis_v(/* PS4's LEFT Y */ 1),
        pointing_axis_h(/* PS4's LEFT X */ 0), invert_pointing_axis_v(false),
        invert_pointing_axis_h(false), pointing_axis_threshold(0.5) {}

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