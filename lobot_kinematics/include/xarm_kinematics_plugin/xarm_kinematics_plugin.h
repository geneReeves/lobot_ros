#ifndef XARM_KINEMATICS_PLUGIN_H
#define XARM_KINEMATICS_PLUGIN_H

#include <moveit/kinematics_base/kinematics_base.h>
#include <ros/ros.h>
#include <tf/tf.h>

namespace xarm_kinematics_plugin {

#define JOINT_NUM 5

class XArmKinematicsPlugin : public kinematics::KinematicsBase {
 public:
  XArmKinematicsPlugin();
  ~XArmKinematicsPlugin();

  const std::vector<std::string> &getJointNames() const override {
    return jointNames_;
  }

  const std::vector<std::string> &getLinkNames() const override {
    return linkNames_;
  }

  bool getPositionFK(const std::vector<std::string> &link_names,
                     const std::vector<double> &joint_angles,
                     std::vector<geometry_msgs::Pose> &poses) const override;

  bool getPositionIK(const geometry_msgs::Pose &ik_pose,
                     const std::vector<double> &ik_seed_state,
                     std::vector<double> &solution,
                     moveit_msgs::MoveItErrorCodes &error_code,
                     const kinematics::KinematicsQueryOptions &options =
                         kinematics::KinematicsQueryOptions()) const override;

  bool initialize(const std::string &robot_description,
                  const std::string &group_name, const std::string &base_frame,
                  const std::string &tip_frame,
                  double search_discretization) override;

  bool searchPositionIK(
      const geometry_msgs::Pose &ik_pose,
      const std::vector<double> &ik_seed_state, double timeout,
      std::vector<double> &solution, moveit_msgs::MoveItErrorCodes &error_code,
      const kinematics::KinematicsQueryOptions &options =
          kinematics::KinematicsQueryOptions()) const override;

  bool searchPositionIK(
      const geometry_msgs::Pose &ik_pose,
      const std::vector<double> &ik_seed_state, double timeout,
      const std::vector<double> &consistency_limits,
      std::vector<double> &solution, moveit_msgs::MoveItErrorCodes &error_code,
      const kinematics::KinematicsQueryOptions &options =
          kinematics::KinematicsQueryOptions()) const override;

  bool searchPositionIK(
      const geometry_msgs::Pose &ik_pose,
      const std::vector<double> &ik_seed_state, double timeout,
      std::vector<double> &solution, const IKCallbackFn &solution_callback,
      moveit_msgs::MoveItErrorCodes &error_code,
      const kinematics::KinematicsQueryOptions &options =
          kinematics::KinematicsQueryOptions()) const override;

  bool searchPositionIK(
      const geometry_msgs::Pose &ik_pose,
      const std::vector<double> &ik_seed_state, double timeout,
      const std::vector<double> &consistency_limits,
      std::vector<double> &solution, const IKCallbackFn &solution_callback,
      moveit_msgs::MoveItErrorCodes &error_code,
      const kinematics::KinematicsQueryOptions &options =
          kinematics::KinematicsQueryOptions()) const override;

 private:
  std::vector<std::string> jointNames_;
  std::vector<std::string> linkNames_;

  std::vector<double> lowerLimits_;
  std::vector<double> upperLimits_;
};

}  // namespace xarm_kinematics_plugin

#endif  // XARM_KINEMATICS_PLUGIN_H
