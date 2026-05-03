# **Algorithmic Visualizer: ROS 2 and C++ Sliding Window**

## **Project Overview**
The **Algorithmic Visualizer** is a ROS 2 project that transforms abstract Data Structures and Algorithms (DSA) into a dynamic 3D environment. By implementing a real-time "Longest Substring Without Repeating Characters" analysis, the system maps internal logic states to 3D markers in Rviz2. This project demonstrates proficiency in **asynchronous message passing**, **O(n) algorithm optimization**, and **spatial data visualization**[cite: 1, 2].

## **The Problem: Longest Substring Without Repeating Characters**
The goal is to find the length of the longest unique substring in a continuous character stream.
*   **Time Complexity**: O(n) using a sliding window and hash-tracking approach.
*   **Space Complexity**: O(1) constant space for the ASCII character set.

## **System Architecture**
The project utilizes a decentralized ROS 2 architecture with two primary nodes:

| Component | Responsibility | Key ROS 2 Tool |
| :--- | :--- | :--- |
| **Streamer Node** | Publishes an increasing character prefix to simulate a real-time data stream. | `rclcpp::Publisher` |
| **Analyzer Node** | Subscribes to the stream, executes the DSA logic, and generates visual markers[cite: 1, 2]. | `rclcpp::Subscription` |
| **Rviz2** | Renders the state of the algorithm in a 3D coordinate system[cite: 1]. | `visualization_msgs/Marker` |

## **Visual Mapping**
To make the algorithm's state interpretable, internal variables are mapped to 3D attributes:
*   **Green Cubes**: Characters currently within the valid "Unique Substring" window.
*   **Red Cubes**: Characters that have been discarded as the window slides forward.
*   **Text Labels**: 3D floating labels providing real-time character identification above each cube.

## **Getting Started**

### **Prerequisites**
*   ROS 2 (Jazzy or Humble recommended).
*   `colcon` build tools.

### **Installation**
1. **Initialize Workspace**:
   ```bash
   mkdir -p ~/ros2_ws/src
   cd ~/ros2_ws/src
   git clone [YOUR_REPO_URL]

Build the Package:

Bash
cd ~/ros2_ws
colcon build --packages-select algorithmic_visualizer


Source the Environment:

Bash
   source install/setup.bash
[cite: 2]

Execution
Run the nodes in separate terminals:

Terminal 1: ros2 run algorithmic_visualizer streamer_node

Terminal 2: ros2 run algorithmic_visualizer analyzer_node

Terminal 3: rviz2

[cite: 2]

Note: In Rviz2, set the Fixed Frame to map and add a MarkerArray display for the /visualization_marker_array topic[cite: 2].

Technical Implementation Details
Memory Management: Utilizes std::vector<int> for O(1) character indexing over std::unordered_map to reduce overhead[cite: 2].

Visualization Logic: Implements a dual-pass callback to ensure the visual state of the entire string is updated relative to the final "start" pointer of the window[cite: 2].

Author: Suraj Prasad

Focus: Robotics Engineering, Modern C++, ROS 2[cite: 2]

Education: M.Tech in AI and ML, BITS Pilani[cite: 2]
