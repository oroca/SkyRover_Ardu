#include <SkyRover.h>

SkyRover Sky;


void setup() 
{
  // put your setup code here, to run once:
                                     
  Sky.begin();
  Sky.menu_off();
  Sky.mw_off();
}

void loop() 
{
  if( Sky.mw_get_status() == false )
  {
    // put your main code here, to run repeatedly:

    Sky.printf("R:%d\t P:%d\t Y:%d\n", Sky.imu_get_angle_roll()/10
                                     , Sky.imu_get_angle_pitch()/10
                                     , Sky.imu_get_angle_yaw());
    Sky.delay(100);
  }
}