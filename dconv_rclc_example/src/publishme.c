#include <stdio.h>
#include <rclc/rclc.h>
#include <geometry_msgs/msg/point.h>
#include <rcl_interfaces/msg/intra_process_message.h>
#include <unistd.h>

int main(int argc, char** argv) {
  printf("Starting up...\n");
  rclc_init(0, NULL);
  rclc_node_t* node = rclc_create_node("my_node", "/ns");
  
  rclc_publisher_t * publisher =
      rclc_create_publisher(node,
       RCLC_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Point),
        "topic", 0);
    
    geometry_msgs__msg__Point* data = geometry_msgs__msg__Point__create();
    data->x = 1.0;
    data->y = 1.0;
    data->z = 1.0;
    
    sleep(2.0);
    while(rclc_ok()) {
      printf("Publishing\n");
      rclc_publish(publisher, data);
      sleep(1.0);
    }
    
    geometry_msgs__msg__Point__destroy(data);
    rclc_destroy_publisher(publisher);
    rclc_destroy_node(node);
  return 0;
}