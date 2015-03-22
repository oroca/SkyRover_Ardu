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

    Sky.led_toggle(0);
    
    Sky.delay(500);
  }
}