#include <geometry_msgs/msg/quaternion.h>
#define EPSILON 1E-12

void quat2rot(geometry_msgs__msg__Quaternion* quat, double rot[9]) {
  double w2 = quat->w*quat->w;
  double x2 = quat->x*quat->x;
  double y2 = quat->y*quat->y;
  double z2 = quat->z*quat->z;
  rot[0] = w2+x2-y2-z2; rot[1] = 2*quat->x*quat->y-2*quat->w*quat->z; rot[2] = 2*quat->x*quat->z+2*quat->w*quat->y;
  rot[3] = 2*quat->x*quat->y+2*quat->w*quat->z; rot[4] = w2-x2+y2-z2; rot[5] = 2*quat->y*quat->z-2*quat->w*quat->x;
  rot[6] = 2*quat->x*quat->z-2*quat->w*quat->y; rot[7] = 2*quat->y*quat->z+2*quat->w*quat->x; rot[8] = w2-x2-y2+z2;
}

void rot2quat(double rot[9], double quat[4]) {
  double trace = rot[0] + rot[4] + rot[8];
  double s;
  if( trace > EPSILON ){
    s = 0.5 / sqrt(trace + 1.0);
    quat[0] = 0.25 / s;
    quat[1] = ( rot[7] - rot[5] ) * s;
    quat[2] = ( rot[2] - rot[6] ) * s;
    quat[3] = ( rot[3] - rot[1] ) * s;
  } else {
    if ( rot[0] > rot[4] && rot[0] > rot[8] ){
      s = 2.0 * sqrt( 1.0 + rot[0] - rot[4] - rot[8]);
      quat[0] = (rot[7] - rot[5] ) / s;
      quat[1] = 0.25 * s;
      quat[2] = (rot[1] + rot[3] ) / s;
      quat[3] = (rot[2] + rot[6] ) / s;
    } else if (rot[4] > rot[8]) {
      s = 2.0 * sqrt( 1.0 + rot[4] - rot[0] - rot[8]);
      quat[0] = (rot[2] - rot[6] ) / s;
      quat[1] = (rot[1] + rot[3] ) / s;
      quat[2] = 0.25 * s;
      quat[3] = (rot[5] + rot[7] ) / s;
    } else {
      s = 2.0 * sqrt( 1.0 + rot[8] - rot[0] - rot[4] );
      quat[0] = (rot[3] - rot[1] ) / s;
      quat[1] = (rot[2] + rot[6] ) / s;
      quat[2] = (rot[5] + rot[7] ) / s;
      quat[3] = 0.25 * s;
    }
  }    
}