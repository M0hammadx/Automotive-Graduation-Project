
#include "Ultrasonic.h"


uint32_t dist1 ,dist2,dist3,dist4,dist5,dist6,dist7,dist8;


int main(){
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //80 MHZ
	Ultrasonic_Init();
	ROM_IntMasterEnable();
	while(1){
    delay_microSec(30000);
		Ultrasonic_Read(Front_Left_Ultrasonic );
		
//		Ultrasonic_Read(Front_Right_Ultrasonic  );
    Ultrasonic_Read(Right_Front_Ultrasonic );
//	Ultrasonic_Read(Right_Back_Ultrasonic );
		Ultrasonic_Read(Back_Right_Ultrasonic );
	//	Ultrasonic_Read(Back_Left_Ultrasonic );
	//	Ultrasonic_Read(Left_Back_Ultrasonic );
	//	Ultrasonic_Read(Left_Front_Ultrasonic );
		dist1 = Get_Distant(Front_Left);
		dist2 = Get_Distant(Front_Right);
		dist3 = Get_Distant(Righ_Front);
		dist4 = Get_Distant(Right_Back);
		dist5 = Get_Distant(Back_Right);
		dist6 = Get_Distant(Back_Left);
		dist7 = Get_Distant(Left_Back);
		dist8 = Get_Distant(Left_Front);
	}		
}



void SystemInit(){
SCB_CPAC |=0x00F00000;}
