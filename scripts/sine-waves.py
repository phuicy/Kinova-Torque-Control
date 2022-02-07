

from copy import deepcopy
import rclpy
from rclpy.node import Node

from sensor_msgs.msg import JointState

import numpy as np



class SinePublisher(Node):

    def __init__(self):
        super().__init__('sine')
        self.publisher_ = self.create_publisher(JointState, 'demand', 10)
        timer_period = 0.01  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        time11 = np.arange(0, 2*3.14159, 0.01)
        time12 = np.arange(0, 2*3.14159, 0.013)
        time13 = np.arange(0, 2*3.14159, 0.009)
        time14 = np.arange(0, -2*3.14159, -0.009)

        self.time      = np.concatenate([time11, time12, time14, time11, time12, time13])
        self.time1      = np.concatenate([time12, time14, time13, time12, time14, time13])
        self.time2      = np.concatenate([time13, time12, time11, time14, time12, time11])

        self.position  = 10 * np.sin(self.time)
        self.velocity  = 10 * np.cos(self.time)
        self.position1 = 15 * np.sin(self.time1)
        self.velocity1 = 15 * np.cos(self.time1)
        self.position2 = 35 * np.sin(self.time2)
        self.velocity2 = 35 * np.cos(self.time2)
        self.i = 0
        self.msg = JointState()
        for i in range(7):
            self.msg.position.append(0)
            self.msg.velocity.append(0)
            self.msg.effort.append(0)
        self.msg.position[1] = 270
        self.msg.position[3] = 90
        self.msg.position[5] = 90

        self.msg_default = deepcopy(self.msg)

    def timer_callback(self):
        self.msg.position[0] = self.msg_default.position[0] + 2 * self.position[self.i]
        self.msg.velocity[0] = self.msg_default.velocity[0] + 2 * self.velocity[self.i]
        self.msg.position[1] = self.msg_default.position[1] - self.velocity[self.i] + 10
        self.msg.velocity[1] = self.msg_default.velocity[1] - self.position[self.i] + 10
        self.msg.position[2] = self.msg_default.position[2] + self.position1[self.i] 
        self.msg.velocity[2] = self.msg_default.velocity[2] + self.velocity1[self.i] 
        self.msg.position[3] = self.msg_default.position[3] + self.position[self.i] 
        self.msg.velocity[3] = self.msg_default.velocity[3] + self.velocity[self.i] 
        self.msg.position[4] = self.msg_default.position[4] + self.position2[self.i] 
        self.msg.velocity[4] = self.msg_default.velocity[4] + self.velocity2[self.i] 
        self.msg.position[5] = self.msg_default.position[5] + self.position2[self.i] 
        self.msg.velocity[5] = self.msg_default.velocity[5] + self.velocity2[self.i] 
        self.msg.position[6] = self.msg_default.position[6] + 5* self.position1[self.i] 
        self.msg.velocity[6] = self.msg_default.velocity[6] + 5* self.velocity1[self.i] 
        self.publisher_.publish(self.msg)
        self.i += 1



def main(args=None):
    rclpy.init(args=args)

    sine_publisher = SinePublisher()

    rclpy.spin(sine_publisher)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    sine_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
