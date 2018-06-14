

/**
 * main.c
 */
 //#define SYSTEM_CLOCK_16_MHZ
#define SYSTEM_CLOCK_80_MHZ
#include "DriverIncludes.h"
#include "CarIF/CarIF.h"
#include "encoder/Encoder.h"
#include "servo/Servo.h"
#include "UART.h"
#include "user_data_frames.h"
#include <math.h>


#define pi   3.14
#define e 0  //wheelbase
#define p 0  //front_and_rear_overhang
#define l 0 //length_of_vehicle
#define w 0 //width_of_vehicle
#define beta 22.5 //steering_angle cuz we always steer at max angle ;) //note : steering angle from center to max (most probably :V)





void delay_mSec(int time);


g_IncomeFrame_t Uart_Frame;
uint8_t* UartData_Frame_Ptr;
uint8_t ServoAngle=90;
uint16_t Motors_Speed=0;

typedef struct Motor_Speed_Data{
	g_Car_Direction Motors_Direction;
	uint8_t Data[6];
	
}s_Motor_Speed_Data_t;


int main(){
   
	 ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //80 MHZ
	 
	
  Car_Modules_Init();
	UART_Init();
	 
	 UART_OutString("ONLINE\n");
/*	 ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
   while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
   ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
	*/
   ROM_IntMasterEnable();
	while(1){
/*		UART_InString((char*)&Uart_Frame,sizeof(g_IncomeFrame_t));
		if(Uart_Frame.Frame_ID=='d' || Uart_Frame.Frame_ID=='D' ){ //D
				ServoAngle=0;
		   	UartData_Frame_Ptr= Uart_Frame.Data;
				while(*UartData_Frame_Ptr != '#'){
					ServoAngle = ServoAngle*10 + (*UartData_Frame_Ptr-'0');
					++UartData_Frame_Ptr;
				}
		Servo_Go(ServoAngle);
		}
		else if(Uart_Frame.Frame_ID=='s' || Uart_Frame.Frame_ID=='S' ){ //S625#*
    s_Motor_Speed_Data_t* UartFrame_MotorSpeed;
		UartFrame_MotorSpeed = (s_Motor_Speed_Data_t*)Uart_Frame.Data;
		Motor_Set_Direction((g_Motor_Direction)((char)UartFrame_MotorSpeed->Motors_Direction -'0'));
		Motors_Speed =0;	
		UartData_Frame_Ptr= UartFrame_MotorSpeed->Data;
		while(*UartData_Frame_Ptr != '#'){
				Motors_Speed = Motors_Speed*10 + (*UartData_Frame_Ptr-'0');
				++UartData_Frame_Ptr;
		   }
		*/
//	  Motor_Change_Speed(Motors_Speed,Motors_Speed);

			Car_Change_Speed(20);
	  }

	/*	
		 Motor_Change_Speed(120,120);
		// delay_mSec(1000);
		 Motor_Change_Speed(0,0);
		// delay_mSec(1000);
		 Motor_Change_Speed(500,500);
		 //delay_mSec(1000);
		 Motor_Change_Speed(625,625);
		 //delay_mSec(1000);
		 
		 
		//UART_OutChar('h');
		Servo_Go(75);
		UART_OutUDec(75);
	//	delay_mSec(1000);
	 Servo_Go(85);	
		UART_OutUDec(85);
 	//	delay_mSec(1000);
	  	Servo_Go(65);
		UART_OutUDec(65);
	//	delay_mSec(1000);
		*/
}
	




#ifdef SYSTEM_CLOCK_16_MHZ
#define TIMER_DELAY_MS_LOAD 16000  // 16000===> 1ms
#endif
#ifdef SYSTEM_CLOCK_80_MHZ
#define TIMER_DELAY_MS_LOAD 80000  // 80000===> 1ms
#endif 


void delay_mSec(int time)
{
	  SYSCTL_RCGCTIMER_R |= 0x01;        // T0(delay)& T2 & T3
    while ((SYSCTL_PRTIMER_R & 0x01 )!= 0x01);
   
    TIMER0_CTL_R = 0;    // disable timer while init
    TIMER0_CFG_R &=~ 0x7;// 16 bit mode
    TIMER0_TAMR_R |= 0x02;//  periodic mode
    TIMER0_TAMR_R &= ~0x10;// count down
    TIMER0_TAR_R = 0x00;//reset count
    TIMER0_ICR_R |= 0x01;//clear flag (acknowledge) during init
    TIMER0_TAILR_R = TIMER_DELAY_MS_LOAD - 1;

    TIMER0_CTL_R |= 0x01;// enable timer0

    int i;
    for (i = 0; i < time; i++)
    {
        while ((TIMER0_RIS_R & 0x01) == 0)
        ;
        TIMER0_ICR_R |= 0x01;
    }
    TIMER0_CTL_R = 0;    // disable timer
}




void vla(double ys, double* arc_dist, double* delta_x) ;

int Park4U() {
	Car_Modules_Init();
	//g_Car_Direction carDir;
	
	//double ys = ultra();
	double arc_dist, delta_x;
	//vla(ys, &arc_dist, &delta_x);

		Car_Change_Steer_Angle(10);
		Car_Change_Direction(Car_FORWARD);
		Car_Change_Speed(1500);
		g_CarInfo_t carInfo;
		
	
		while (!(carInfo.Distance_Elapsed<=(delta_x))){
		Car_Get_Car_Info(&carInfo);	
		}
				//walk till u reach starting point

		Car_Change_Steer_Angle(20);
		Car_Change_Direction(Car_BACKWARD);
		while (!(carInfo.Distance_Elapsed<=(arc_dist))){
		Car_Get_Car_Info(&carInfo);	
		}	//walk till u reach turn point

		Car_Change_Steer_Angle(0);
	while (!(carInfo.Distance_Elapsed<=(arc_dist))){
		Car_Get_Car_Info(&carInfo);	
		}		;	//walk till u reach end point

		//stop motors
	//Motor_Stop();
	

	return 0;
}
void vla(double ys, double* arc_dist, double* delta_x) {

	//matlab trials show starting pos doesnt matter but u have to be in parallel with the nextcar

	double yc1 = 0.0; //(an input) last y from desired end pos // or calculate from ri-w/2 //or maybe assumed 0 ? wtvr
	double xc1 = 0.0; //(an input) last x from desired end pos // or calculate from lastcar + p //or maybe assumed 0 ? wtvr
//	double ys = 0.0; //(an input) start y from start parking pos

	double r = e / sin(beta);
	double ri = sqrt(r * r - e * e) - w / 2; //or  e / tan(beta) - w / 2  bs 8aleban el 2ola faster ;D
	double re = sqrt((ri + w) * (ri + w) + (e + p) * (e + p));
	double min_lenth_for_parking = p + sqrt(re * re - ri * ri); //b4 parking check whether u can park :)

	double ri_dash = ri + w / 2; //assumed operating r
	double re_dash = sqrt((ri_dash + w) * (ri_dash + w) + (e + p) * (e + p));
	double distance_to_nextcar = sqrt(re_dash * re_dash - ri_dash * ri_dash);

	double yc2 = ys - ri_dash; //y coordinates for c2
//now for pt where we counter steer
	double yt = (yc1 + yc2) / 2;
	double xt = xc1 + sqrt(ri_dash * ri_dash - (yt - yc1) * (yt - yc1));

	double xs = 2 * xt - xc1;
	double xc2 = xs; //x coordinates for c2.
//calc theta
	double delta_c1_c2 = sqrt(
			(xc1 - xc2) * (xc1 - xc2) + (xc1 - xc2) * (xc1 - xc2));
	double costheta = (xc2 - xc1) / delta_c1_c2;
	double theta = acos(theta);

//so finally :)
	double curve_distance_to_fking_walk = 2 * pi * ri_dash * theta / 360.0; //curve distance to walk before making fully reversing steering angle
	double distance_after_nextcar = xs - distance_to_nextcar - p;
	*arc_dist = curve_distance_to_fking_walk;
	*delta_x = distance_after_nextcar;
//embedded code ? apply above equations to determine path
//start steering at max angle (aka beta) from starting pos (aka (xs,ys)) //note : walk distance_after_nextcar after u start seeing nextcar
//after walking distance=curve_distance_to_fking_walk reverse steering to max angle
//walk another curve_distance_to_fking_walk and tada u have parked or hit smt :)

}

