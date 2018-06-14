#include "global.h"


static uint16_t U16Desired_RPM_MotorIF_System_PID ;    //shared desired_RPM Global variable
static uint16_t U16Actual_speed_System_PID_MotorIF ;   //shared actual_speed Global variable

 /*
  set Desired RPM value
  */
  void set_Desired_RPM(uint16_t desired_rpm){
    
		U16Desired_RPM_MotorIF_System_PID = desired_rpm;
   }
	
	 
	 
  /*
  get Desired RPM value
  */
  uint16_t get_Desired_RPM(void){
		
   return U16Desired_RPM_MotorIF_System_PID ;
   }
	
	 
   /*
    set Desired actual speed value
   */
  void set_Actual_Speed(uint16_t* act_speed){
  
		U16Actual_speed_System_PID_MotorIF=(act_speed[0]+act_speed[1])/2; 
   }


    /*
    set Desired actual speed value
     */
   uint16_t get_Actual_Speed(void){

	 return U16Actual_speed_System_PID_MotorIF;
    }


