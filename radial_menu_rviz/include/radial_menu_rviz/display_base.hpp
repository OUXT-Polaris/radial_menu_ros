#ifndef RADIAL_MENU_RVIZ_DISPLAY_BASE_HPP
#define RADIAL_MENU_RVIZ_DISPLAY_BASE_HPP

#include <radial_menu_msgs/State.h>
#include <radial_menu_rviz/image_overlay.hpp>
#include <radial_menu_rviz/properties.hpp>
#include <ros/console.h>
#include <ros/exception.h>
#include <ros/subscriber.h>
#include <rviz/display.h>

#include <boost/scoped_ptr.hpp>

namespace radial_menu_rviz {

// base implementation of display classes except Qt's signals and slots
// because template classes cannot have any slots and signals by Qt's limitation
template < typename DrawingProperty, class PropertyControl, class ImageDrawer >
class DisplayBase : public rviz::Display {
public:
  DisplayBase() {}

  virtual ~DisplayBase() {}

protected:
  // called once on initialization
  virtual void onInitialize() {
    // allocate objects
    prop_ctl_.reset(new PropertyControl(this));
    drawer_.reset(new ImageDrawer(closedState(), prop_ctl_->drawingProperty()));
    overlay_.reset(new ImageOverlay());

    // apply the initial properties
    // (except subscription. it will be executed in onEnable().)
    updateImage(prop_ctl_->drawingProperty());
    updatePosition(prop_ctl_->positionProperty());
  }

  // called when enabled
  virtual void onEnable() {
    updateSubscription(prop_ctl_->subscriptionProperty());
    overlay_->show();
  }

  // called when disabled
  virtual void onDisable() {
    overlay_->hide();
    state_sub_.shutdown();
  }

  void updateSubscription(const SubscriptionProperty &prop) {
    // unsubscribe
    state_sub_.shutdown();

    // destroy the last state from the previous session
    drawer_->setState(closedState());
    updateImage(prop_ctl_->drawingProperty());

    // subscribe the new topic
    try {
      state_sub_ =
          ros::NodeHandle().subscribe(prop.topic.toStdString(), 1, &DisplayBase::updateImage, this);
    } catch (const ros::Exception &error) {
      ROS_ERROR_STREAM(getName().toStdString()
                       << ": error on subscribing topic ('" << prop.topic.toStdString()
                       << "'): " << error.what());
    }
  }

  // update menu image with the given menu state
  void updateImage(const radial_menu_msgs::StateConstPtr &state) {
    drawer_->setState(*state);
    overlay_->setImage(drawer_->draw());
  }

  // update menu image with the given drawing property
  void updateImage(const DrawingProperty &prop) {
    drawer_->setProperty(prop);
    overlay_->setImage(drawer_->draw());
  }

  void updatePosition(const PositionProperty &prop) { overlay_->setTopLeft(prop.top_left); }

  static radial_menu_msgs::State closedState() {
    radial_menu_msgs::State state;
    state.is_opened = false;
    state.pointed_id = -1;
    return state;
  }

protected:
  // property control via Rviz
  boost::scoped_ptr< PropertyControl > prop_ctl_;
  // menu state subscriber
  ros::Subscriber state_sub_;
  // state drawer
  boost::scoped_ptr< ImageDrawer > drawer_;
  // overlay on Rviz
  boost::scoped_ptr< ImageOverlay > overlay_;
};
} // namespace radial_menu_rviz

#endif