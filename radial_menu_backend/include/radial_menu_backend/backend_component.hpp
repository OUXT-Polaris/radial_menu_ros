#ifndef RADIAL_MENU_BACKEND_BACKEND_NODELET_HPP
#define RADIAL_MENU_BACKEND_BACKEND_NODELET_HPP

#include <radial_menu_backend/backend_config.hpp>
#include <radial_menu_backend/backend_controller.hpp>
#include <radial_menu_model/model.hpp>
#include <radial_menu_msgs/msg/state.hpp>
#include <sensor_msgs/msg/joy.h>
#include <rclcpp/rclcpp.hpp>

namespace radial_menu_backend {
  class BackendComponent: public rclcpp::Node{
    public:
      BackendComponent(const rclcpp::NodeOptions & options) 
      : Node("radial_menu_backend", options)
      {
        std::string menu_description;
        declare_parameter("menu_description");
        if(!get_parameter("menu_description",menu_description))
        {
          std::string message = "Cannot set a model description from the param menu_description";
          throw std::runtime_error(message);
        }
        model_->setDescription(menu_description);

        auto param = std::make_shared<rclcpp::SyncParametersClient>(this,"param_holder");
        controller_.reset(
          new BackendController(model_, BackendConfig::fromParam(param)));
        state_pub_ = this->create_publisher<radial_menu_msgs::msg::State>("menu_state", 1);
        state_pub_->publish(*model_->exportState(get_clock()->now()));
        auto callback = std::bind(&BackendComponent::onJoyRecieved, this, std::placeholders::_1);
        joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>("joy", 1, callback);
      }
    private:
      void onJoyRecieved(const sensor_msgs::msg::Joy::SharedPtr joy)
      {
        state_pub_->publish(*controller_->update(*joy));
      }
    protected:
      radial_menu_model::ModelPtr model_;
      BackendControllerPtr controller_;
      rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
      rclcpp::Publisher<radial_menu_msgs::msg::State>::SharedPtr state_pub_;
  };
}

#endif
