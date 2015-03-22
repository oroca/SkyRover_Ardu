
#include "SkyRover.h"


//-- 외부 변수
//
extern int16_t angle[2];
extern int16_t heading;
extern uint8_t thread_menu_enable;


int16_t imu_angle[3];
int16_t imu_gyro[3];
int8_t  arm_flag;
int8_t  cmd_ready = false;
int8_t  mw_enable = false;
bool    motor_safe = true;

static void uart1_putc(void *p, char c)
{
    serialWrite(core.mainport, c);
}

static void usb_putc(void *p, char c)
{
    Hw_VCom_Putch(c);
}


/*---------------------------------------------------------------------------
     TITLE	: begin
     WORK	:
     ARG	:
     RET	:
---------------------------------------------------------------------------*/
void SkyRover::begin(void) 
{

	DEBUG_PRINT("SkyRover Begin\r\n");

    motor_pwm[0] = 0;
    motor_pwm[1] = 0;
    motor_pwm[2] = 0;
    motor_pwm[3] = 0;
}


/*---------------------------------------------------------------------------
     TITLE  : motor_safe_off
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
void SkyRover::motor_safe_off(void) 
{
    motor_safe = false;    
}


/*---------------------------------------------------------------------------
     TITLE  : motor_safe_on
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
void SkyRover::motor_safe_on(void) 
{
    motor_safe = true;    
}


/*---------------------------------------------------------------------------
     TITLE  : menu_off
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
void SkyRover::menu_off(void) 
{
    thread_menu_enable = 0;    
}


/*---------------------------------------------------------------------------
     TITLE  : menu_off
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
void SkyRover::menu_on(void) 
{
    thread_menu_enable = 1;    
}


/*---------------------------------------------------------------------------
     TITLE	: begin
     WORK	:
     ARG	:
     RET	:
---------------------------------------------------------------------------*/
void SkyRover::delay( int32_t delay_data ) 
{
	osDelay( delay_data );
}


/*---------------------------------------------------------------------------
     TITLE  : uart1_printf
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
void SkyRover::uart1_printf( char *format, ... )
{
    //printf( format );
    va_list va;
    va_start(va, format);
    tfp_format(NULL, uart1_putc, format, va);
    va_end(va); 
}


/*---------------------------------------------------------------------------
     TITLE	: printf
     WORK	:
     ARG	:
     RET	:
---------------------------------------------------------------------------*/
void SkyRover::printf( char *format, ... )
{
	//Hw_VCom_Printf( format );
    va_list va;
    va_start(va, format);
    tfp_format(NULL, usb_putc, format, va);
    va_end(va);		
}


/*---------------------------------------------------------------------------
     TITLE  : mw_on
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
void SkyRover::mw_on( void )
{
    mw_enable = true;
}


/*---------------------------------------------------------------------------
     TITLE  : mw_off
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
void SkyRover::mw_off( void )
{
    mw_enable = false;
}


/*---------------------------------------------------------------------------
     TITLE  : mw_get_status
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
int8_t SkyRover::mw_get_status( void )
{
    return mw_enable;
}

/*---------------------------------------------------------------------------
     TITLE  : arm_get_status
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
int8_t SkyRover::arm_get_status( void )
{
    return arm_flag;
}

/*---------------------------------------------------------------------------
     TITLE  : imu_get_angle_roll
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
int16_t SkyRover::imu_get_angle_roll( void )
{
    return imu_angle[0];
}


/*---------------------------------------------------------------------------
     TITLE  : imu_get_angle_pitch
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
int16_t SkyRover::imu_get_angle_pitch( void )
{
    return imu_angle[1];
}


/*---------------------------------------------------------------------------
     TITLE  : imu_get_angle_yaw
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
int16_t SkyRover::imu_get_angle_yaw( void )
{
    return imu_angle[2];
}


/*---------------------------------------------------------------------------
     TITLE  : imu_get_gyro_roll
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
int16_t SkyRover::imu_get_gyro_roll( void )
{
    return imu_gyro[0];
}


/*---------------------------------------------------------------------------
     TITLE  : imu_get_gyro_pitch
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
int16_t SkyRover::imu_get_gyro_pitch( void )
{
    return imu_gyro[1];
}


/*---------------------------------------------------------------------------
     TITLE  : imu_get_gyro_yaw
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
int16_t SkyRover::imu_get_gyro_yaw( void )
{
    return imu_gyro[2];
}


/*---------------------------------------------------------------------------
     TITLE  : led_toggle
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
void SkyRover::led_toggle( uint8_t ch )
{
    ::led_toggle( ch, false );
}


/*---------------------------------------------------------------------------
     TITLE  : led_on
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
void SkyRover::led_on( uint8_t ch )
{
    ::led_on( ch, false );
}


/*---------------------------------------------------------------------------
     TITLE  : led_off
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
void SkyRover::led_off( uint8_t ch )
{
    ::led_off( ch, false );
}




/*---------------------------------------------------------------------------
     TITLE  : cmd_ready
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
bool SkyRover::cmd_ready( void )
{
    bool ret = false;

    if( ::cmd_ready == true )
    {
        ::cmd_ready = false;
        ret = true;
    }
    
    return ret;
}


/*---------------------------------------------------------------------------
     TITLE  : cmd_get_roll
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
int16_t SkyRover::cmd_get_roll( void )
{
    int16_t ret;

    ret = rcCommand[ROLL];

    return ret;
}


/*---------------------------------------------------------------------------
     TITLE  : cmd_get_pitch
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
int16_t SkyRover::cmd_get_pitch( void )
{
    int16_t ret;

    ret = rcCommand[PITCH];

    return ret;
}


/*---------------------------------------------------------------------------
     TITLE  : cmd_get_yaw
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
int16_t SkyRover::cmd_get_yaw( void )
{
    int16_t ret;

    ret = rcCommand[YAW];

    return ret;
}


/*---------------------------------------------------------------------------
     TITLE  : cmd_get_throttle
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
int16_t SkyRover::cmd_get_throttle( void )
{
    int16_t ret;
    int32_t range;

    range = mcfg.maxthrottle - mcfg.minthrottle;

    ret = (rcCommand[THROTTLE]-mcfg.minthrottle) * 1000 / range;

    ret = constrain( ret, 0, 1000 );

    return ret;
}


/*---------------------------------------------------------------------------
     TITLE  : motor_set_speed_REAR_R
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
void SkyRover::motor_set_speed_REAR_R( int16_t speed )
{
    int32_t range;

    speed = constrain( speed, 0, 1000 );

    motor_pwm[0] = speed;

    //range = mcfg.maxthrottle - mcfg.minthrottle;
    //range = speed * range / 1000;
    //motor[2] = mcfg.minthrottle + range; 

    motor[0] = mcfg.mincommand + speed;

    pwmWriteMotor(0, motor[0]);
}


/*---------------------------------------------------------------------------
     TITLE  : motor_set_speed_FRONT_R
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
void SkyRover::motor_set_speed_FRONT_R( int16_t speed )
{
    int32_t range;

    speed = constrain( speed, 0, 1000 );

    motor_pwm[1] = speed;

    //range = mcfg.maxthrottle - mcfg.minthrottle;
    //range = speed * range / 1000;
    //motor[2] = mcfg.minthrottle + range; 

    motor[1] = mcfg.mincommand + speed;

    pwmWriteMotor(1, motor[1]);
}


/*---------------------------------------------------------------------------
     TITLE  : motor_set_speed_REAR_L
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
void SkyRover::motor_set_speed_REAR_L( int16_t speed )
{
    int32_t range;

    speed = constrain( speed, 0, 1000 );

    motor_pwm[2] = speed;

    //range = mcfg.maxthrottle - mcfg.minthrottle;
    //range = speed * range / 1000;
    //motor[2] = mcfg.minthrottle + range; 

    motor[2] = mcfg.mincommand + speed;

    pwmWriteMotor(2, motor[2]);
}


/*---------------------------------------------------------------------------
     TITLE  : motor_set_speed_FRONT_L
     WORK   :
     ARG    :
     RET    :
---------------------------------------------------------------------------*/
void SkyRover::motor_set_speed_FRONT_L( int16_t speed )
{
    int32_t range;

    speed = constrain( speed, 0, 1000 );

    motor_pwm[3] = speed;

    //range = mcfg.maxthrottle - mcfg.minthrottle;
    //range = speed * range / 1000;
    //motor[3] = mcfg.minthrottle + range; 

    motor[3] = mcfg.mincommand + speed;

    pwmWriteMotor(3, motor[3]);
}

