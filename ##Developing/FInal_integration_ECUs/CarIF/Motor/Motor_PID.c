

#include "Motor_PID.h"
#include "../encoder/encoder.h"
#include "../../global.h"

//#define debug
#ifdef debug
int v[40][2],i=0;
#endif
extern uint8_t  QEI0_flag,QEI1_flag ;




void PID_Speed_Init(void){
	

	
}




void PID_Speed_System(void){
uint16_t current_RPM[2];
	double pwm[2];
	static uint16_t desired_pwm,desired_RPM,current_speed[2],last_RPM=0 ;
  static double  last_error[2],current_error[2],de[2],ie[2]={0,0};

	
	
	/*
	stop firing PID
	 */
	    NVIC_ST_CTRL_R&= ~0X07 ;
	    QEI0_flag=0;QEI1_flag=0;
	
	/*
	 RPM= PWM*k -b;
   */
	  desired_RPM= get_Desired_RPM();
	if(last_RPM!=desired_RPM){
	/*
	  start new PID claculations if desired_RPM changed
	 */
		last_RPM = desired_RPM;
    desired_pwm =(desired_RPM+b)/k ;  
    last_error[0]=desired_pwm;
	  last_error[1]=desired_pwm;
		
		

	}
  //  get_current_RPM(current_RPM);  // get current RPM from encoders
	Encoder_Get_Motors_RPM(current_RPM);
  /*
   calculate current speed in Km/hr
   */
	 	#ifdef CAR_SPEED_IN_Km_PER_HR
	   current_speed[0]=(current_RPM[0]*pi*60*diameter)/1000 ;
     current_speed[1]=(current_RPM[1]*pi*60*diameter)/1000  ;
    #endif
	/*
   calculate current speed in m/hr
   */
    #ifdef CAR_SPEED_IN_METER_PER_HR
     current_speed[0]=(current_RPM[0]*pi*60*diameter);
     current_speed[1]=(current_RPM[1]*pi*60*diameter);
    #endif
#ifdef debug
   v[i][0]=current_speed[0];
	 v[i][1]=current_speed[1];
	
	if(i<39){
	i++;
	}
	if(i==39) i=0;
#endif	
     set_Actual_Speed(current_speed);                      // set actual car speed
   /*
	 PWM= (RPM+b)/k;
    */
     current_error[0]=desired_pwm-((current_RPM[0]+b)/k); // calculate error in PWM motor0
     current_error[1]=desired_pwm-((current_RPM[1]+b)/k); // calculate error in PWM motor1

  /*
	 PID calculations
	 */
     de[0]=last_error[0]-current_error[0] ;  // get differential error motor0
	   de[1]=last_error[1]-current_error[1] ;  // get differential error motor1
	   ie[0]=ie[0]+current_error[0];           // get integral error motor0
     ie[1]=ie[1]+current_error[1];           // get integral error motor1
	   last_error[0]=current_error[0];         // save current error motor0
	   last_error[1]=current_error[1];         // save current error motor1

   	  pwm[0]=(Kp*current_error[0]+Ki*ie[0]+Kd*de[0]);   // PWM after PID calculations motor0
	    pwm[1]=(Kp*current_error[1]+Ki*ie[1]+Kd*de[1]);   // PWM after PID calculations motor1
			 
			 if(pwm[0]<0) pwm[0]=current_error[0]-pwm[0];
			
			 
			 if(pwm[1]<0) pwm[0]=current_error[0]-pwm[0];
		
			
	     if(pwm[0]>620 )   pwm[0]=620; // Motor0 limit
	     if(pwm[1]>620 )   pwm[1]=620; // Motor1 limit

	      Motor_PWM_Speed_Control(pwm[0],pwm[1]);                     // send pwm to motors
  
     }


		 
		 
void PID_Get_Current_Car_Speed(uint16_t* PtrCarSpeed){
	*PtrCarSpeed= get_Actual_Speed();
	
	
	
}
		 
