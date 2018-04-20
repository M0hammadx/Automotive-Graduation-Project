

/*

Wiring :
         BackRigh_Encoder QEI0 ==> channelA:PD6   ,channelB:PD7 
         BackRigh_Encoder QEI1 ==> channelA:PC5   ,channelB:PC6 
 */

#include "Encoder.h"


static uint32_t Encoder0_read,Encoder1_read ;
 uint8_t  flag = 0 , QEI0_flag , QEI1_flag , dir , overFlow=0 ;
 
  double forwardDistance =0 ;
 uint32_t pulse ; 
 
 double QEI0_readDistance(void){
																					// dir = 1 position decrement 
		pulse = QEI0_POS_R ;     							//dir ==0 position increment 
	 dir = QEI0_STAT_R & 0x002 ;
	 
	 if(pulse < 5 && dir == 0 && flag == 0){   //forward
			overFlow+=1 ;
		  
		  flag =1;
	 }
	 if (pulse >= 5 )
		 flag = 0; 
			
	 forwardDistance  =(pulse /580.0)*(2*pi*7.0) ;
	 
   	 return   overFlow* maxDistance + forwardDistance;
 
 }
 
void QEI0_Handler(void){
		QEI0_flag=1;
	  Encoder0_read=QEI0_SPEED_R ;
	  QEI0_ISC_R|=0x2;
		
		 if(QEI0_flag==1&&QEI1_flag==1){
		   // fire PID
			// NVIC_ST_CTRL_R|= 0X07 ;
			}}
	
  void QEI1_Handler(void){
		 QEI1_flag=1;
	   Encoder1_read=QEI0_SPEED_R ;
	   QEI1_ISC_R|=0x2;
			if(QEI0_flag==1&&QEI1_flag==1){
		    // fire PID
			//  NVIC_ST_CTRL_R|= 0X07 ;
		  }}


      /*
			 rpm = (clock * SPEED * 60) ÷ (LOAD * Max_Position*gear_ratio )
			 timer_tick_freq=clock/Load
			 
			 */
 void get_current_RPM(uint16_t* RPM){
	  
    RPM[0]=(system_freq*60*Encoder0_read)/(Encoder_timer_Load*gear_ratio*Max_Position);  // calculate RPM for motor 0
    RPM[1]=(system_freq*60*Encoder1_read)/(Encoder_timer_Load*gear_ratio*Max_Position);  // calculate RPM for motor 1

	
	
}
void Encoder_Init(void){
/*
 // 
	(SYSCTL_SYSDIV_1| SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //clock 80 MHZ
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);	                     //Run Clock on port D
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);	                     //Run clock on port C
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);	                       //Run clock on QEI0
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);	                       //Run clock on QEI1
  ROM_GPIODirModeSet(GPIO_PORTD_BASE,GPIO_PIN_6,GPIO_DIR_MODE_IN );      // PD6 input
  ROM_GPIODirModeSet(GPIO_PORTD_BASE,GPIO_PIN_7,GPIO_DIR_MODE_IN );      // PD7 input
  ROM_GPIODirModeSet(GPIO_PORTC_BASE,GPIO_PIN_5,GPIO_DIR_MODE_IN );      // PC6 input
  ROM_GPIODirModeSet(GPIO_PORTC_BASE,GPIO_PIN_6,GPIO_DIR_MODE_IN );      // PC7 input
  ROM_GPIOPinTypeQEI(GPIO_PORTD_BASE,GPIO_PIN_6);                        // use QEI0 ,phA0
  ROM_GPIOPinTypeQEI(GPIO_PORTD_BASE,GPIO_PIN_7);                        // use QEI1 ,phB0
  ROM_GPIOPinTypeQEI(GPIO_PORTC_BASE,GPIO_PIN_5);                        // use QEI0 ,phA1
  ROM_GPIOPinTypeQEI(GPIO_PORTC_BASE,GPIO_PIN_6);                        // use QEI1 ,phB1
	
  ROM_QEIConfigure(QEI0_BASE,QEI_CONFIG_CAPTURE_A_B|QEI_CONFIG_NO_RESET|QEI_CONFIG_NO_RESET|QEI_CONFIG_NO_SWAP,Max_Position);       // capture A,B , max_pos=12
  ROM_QEIConfigure(QEI1_BASE,QEI_CONFIG_CAPTURE_A_B|QEI_CONFIG_NO_RESET|QEI_CONFIG_NO_RESET|QEI_CONFIG_NO_SWAP,Max_Position);       // capture A,B , max_pos=12
  ROM_QEIPositionSet(QEI0_BASE,1);
	
	ROM_QEIVelocityConfigure(QEI0_BASE,QEI_VELDIV_1,Timer_Period);   // capture pulses every 1s
  ROM_QEIVelocityConfigure(QEI1_BASE,QEI_VELDIV_1,Timer_Period);   // capture pulses every 1s
  ROM_QEIVelocityEnable(QEI0_BASE);                                //Enable Velocity capture mode
  ROM_QEIVelocityEnable(QEI1_BASE);                                //Enable Velocity capture mode	
  ROM_QEIIntEnable(QEI0_BASE,QEI_INTTIMER);                        //Enable Interrupt every timer tick
  ROM_QEIIntEnable(QEI1_BASE,QEI_INTTIMER);                        //Enable Interrupt every timer tick
  ROM_QEIEnable(QEI0_BASE);                                        //Enable QEI0
  ROM_QEIEnable(QEI1_BASE);                                        //Enable QEI1			
  ROM_IntEnable(INT_QEI0_TM4C123);                                     //Enable QEI0 interrupt number in NVIC -->13
  ROM_IntEnable(INT_QEI1_TM4C123);                                     //Enable QEI1 interrupt number in NVIC -->38
  ROM_IntPrioritySet(QEI0_INT_NUM,priority1);                       // priority 1 for QEI0 interrupt
  ROM_IntPrioritySet(QEI0_INT_NUM,priority1);                       // priority 1 for QEI1 interrupt
	*/
	
		SYSCTL_RCGCGPIO_R|=0x0C;    //enable clocks on port C&D
  while((SYSCTL_PRGPIO_R&(SYSCTL_PRGPIO_R3|SYSCTL_PRGPIO_R2))==0){} //wait clocks to be stable 
  SYSCTL_RCGCQEI_R|=0x03;
  while((SYSCTL_PRQEI_R&(SYSCTL_PRQEI_R0|SYSCTL_PRQEI_R1))==0){}	
   GPIO_PORTD_LOCK_R |=0x4C4F434B;
  GPIO_PORTD_CR_R  |=0xC0;
	 GPIO_PORTD_DIR_R &=~0xC0;
  GPIO_PORTD_DEN_R |=0xC0;
  GPIO_PORTD_AMSEL_R &=~0xC0;
	GPIO_PORTD_AFSEL_R |=0xC0;
	GPIO_PORTD_PCTL_R &=~0xFF000000;
	GPIO_PORTD_PCTL_R |= 0x66000000;
		
	   GPIO_PORTC_LOCK_R |=0x4C4F434B;
  GPIO_PORTC_CR_R  |=0x60;
	 GPIO_PORTC_DIR_R &=~0x60;
  GPIO_PORTC_DEN_R |=0x60;
  GPIO_PORTC_AMSEL_R &=~0x60;
	GPIO_PORTC_AFSEL_R |=0x60;
	GPIO_PORTC_PCTL_R &=~0x0FF00000;
	GPIO_PORTC_PCTL_R |= 0x06600000;
	
	//QEI0
	
	QEI0_CTL_R|=0X00028;
	
  QEI0_MAXPOS_R=Max_Position;
  QEI0_LOAD_R=(Timer_Period )-1;
	QEI0_CTL_R|=0X0001;	
	QEI0_POS_R = 0x5;
		//Interrupt
	NVIC_EN0_R |=0x2000;
	NVIC_PRI3_R &=~0xFF00;	
	NVIC_PRI3_R |= 0x1000;	
  QEI0_INTEN_R|=0x2;	
	
	QEI1_CTL_R|=0X00028;
	QEI1_POS_R = 1;
  QEI1_MAXPOS_R=Max_Position;
  QEI1_LOAD_R=(Timer_Period )-1;
	QEI1_CTL_R|=0X0001;	
		//Interrupt
	NVIC_EN1_R |=0x0040;
	NVIC_PRI9_R &=~0xFF0000;	
	NVIC_PRI9_R |= 0x100000;	
  QEI1_INTEN_R|=0x2;	
	
}

void SysTick_Init(void){
	NVIC_ST_CTRL_R= 0 ;            // disable systick 
	NVIC_ST_RELOAD_R= 80000000-1 ;     // 1s
	NVIC_ST_CURRENT_R= 0 ;
	NVIC_SYS_PRI3_R &=~0XFF000000 ;  // priority 0
	NVIC_ST_CTRL_R= 0X04 ;  // setup the clk src
}








