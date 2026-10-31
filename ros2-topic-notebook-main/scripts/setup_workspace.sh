#!/usr/bin/env bash
set -euo pipefail
ROS_DISTRO="${ROS_DISTRO:-humble}"
WORKSPACE="${1:-$HOME/ros2_ws}"
REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

if [[ ! -d "/opt/ros/${ROS_DISTRO}" ]]; then
  echo "找不到 /opt/ros/${ROS_DISTRO}，请检查 ROS 2 安装。" >&2
  exit 1
fi
source "/opt/ros/${ROS_DISTRO}/setup.bash"
mkdir -p "${WORKSPACE}/src"
if [[ "${REPO_ROOT}/src/topic_demo_cpp" != "${WORKSPACE}/src/topic_demo_cpp" ]]; then
  if [[ -e "${WORKSPACE}/src/topic_demo_cpp" ]]; then
    echo "目标包已存在，避免覆盖，脚本停止：${WORKSPACE}/src/topic_demo_cpp" >&2
    exit 1
  fi
  cp -r "${REPO_ROOT}/src/topic_demo_cpp" "${WORKSPACE}/src/"
fi
cd "${WORKSPACE}"
colcon build --packages-select topic_demo_cpp
echo "构建完成。接下来执行：source ${WORKSPACE}/install/setup.bash"
