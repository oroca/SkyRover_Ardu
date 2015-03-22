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
  if( Sky.mw_get_status() == false ) continue;

  
  // put your main code here, to run repeatedly:

  Sky.printf("R:%d\t P:%d\t Y:%d\t TH:%d\n" , Sky.cmd_get_roll()
                                            , Sky.cmd_get_pitch()
                                            , Sky.cmd_get_yaw()
                                            , Sky.cmd_get_throttle());
  Sky.delay(100);
}