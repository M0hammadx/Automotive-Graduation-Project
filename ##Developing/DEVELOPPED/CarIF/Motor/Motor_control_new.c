/*
 * Motor_control_new.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Sahar Elnagar
 */

#include"Motor_control_new.h"


void Motors_control_init(void){


    SysCtlPWMClockSet(SYSCTL_PWMDIV_64); //make sure that PWM clk = sys/64
    //**** Init PWM0 & PWM1 on PB6 & PB7 ****//

    SYSCTL_RCGCPWM_R |= 0x03;               // Enable PWM Clock Module 0&1
    while (!(SYSCTL_PRPWM_R & SYSCTL_PRPWM_R))
        ;
    SYSCTL_RCGCGPIO_R |= 0X03;                    //Enable the clock to PORT B&A
    while (!(SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R1))
        ;
   /*
    * PORTB Initialization
    * */
    GPIO_PORTB_LOCK_R = 0X4C4F434B;
    GPIO_PORTB_CR_R |= 0XC0;
    GPIO_PORTB_DIR_R |= 0XC0;                // Output signal
    GPIO_PORTB_DEN_R |= 0XC0;                // Enable Digital
    GPIO_PORTB_AMSEL_R &= ~0XC0;             // Disable Analog
    GPIO_PORTB_AFSEL_R |= 0XC0;              // Alternative Function
    GPIO_PORTB_PCTL_R &= ~0XFF000000;
    GPIO_PORTB_PCTL_R |= 0X44000000;
    GPIO_PORTB_DR8R_R |= 0XC0;
    /*
     * PWM0&1 Module0 Initialization
     * */
    PWM0_0_CTL_R = 0;                  // COUNT DOWN MODE, disable during config

    PWM0_0_GENA_R |= 0XC8;                // LOW ON LOAD , HIGH ON CMPA
    PWM0_0_GENB_R |= 0XC08;               // LOW ON LOAD , HIGH ON CMPB

#ifdef SYSTEM_CLOCK_16_MHZ    //actually  PWMDIV = 64 from motor code
    /*PWM0_0_LOAD_R=8000-1 ;                // PWM FREQUENCY= 2000 HZ
     */
    PWM0_0_LOAD_R = 125-1;

#endif
#ifdef  SYSTEM_CLOCK_80_MHZ
    /*PWM0_0_LOAD_R=40000-1 ;                // PWM FREQUENCY= 2000 HZ
     */
    PWM0_0_LOAD_R = 625 - 1;

#endif

    /*
      * PORTA Initialization
      * */
      GPIO_PORTA_LOCK_R = 0X4C4F434B;
      GPIO_PORTA_CR_R  |= 0XC0;
      GPIO_PORTA_DIR_R |= 0XC0;                // Output signal
      GPIO_PORTA_DEN_R |= 0XC0;                // Enable Digital
      GPIO_PORTA_AMSEL_R &= ~0XC0;             // Disable Analog
      GPIO_PORTA_AFSEL_R |= 0XC0;              // Alternative Function
      GPIO_PORTA_PCTL_R &= ~0XFF000000;
      GPIO_PORTA_PCTL_R |= 0X55000000;
      GPIO_PORTA_DR8R_R |= 0XC0;

      /*
       * PWMA&B Generator1 Module1 Initialization
       * */
      PWM1_1_CTL_R = 0;                  // COUNT DOWN MODE, disable during config

      PWM1_1_GENA_R |= 0XC8;                // LOW ON LOAD , HIGH ON CMPA
      PWM1_1_GENB_R |= 0XC08;               // LOW ON LOAD , HIGH ON CMPB

  #ifdef SYSTEM_CLOCK_16_MHZ    //actually  PWMDIV = 64 from motor code
      /*PWM0_0_LOAD_R=8000-1 ;                // PWM FREQUENCY= 2000 HZ
       */
      PWM1_1_LOAD_R = 125-1;

  #endif
  #ifdef  SYSTEM_CLOCK_80_MHZ
      /*PWM0_0_LOAD_R=40000-1 ;                // PWM FREQUENCY= 2000 HZ
       */
      PWM1_1_LOAD_R = 625 - 1;

  #endif

}

void Motors_Control(uint16_t duty, g_Car_Direction CarDir)
{

    if(CarDir==Car_FORWARD){
        /*MotorLeft
          * */

        PWM1_1_CMPA_R = duty - 2 ;            // DECIDE DUTY PA6  M1PWM2
        PWM1_1_CMPB_R=2;                     //DECIDE DUTY PA7 M1PWM3

        /*MotorRight
          * */
        PWM0_0_CMPA_R = 2;                    // DECIDE DUTY PB6  M0PWM0
        PWM0_0_CMPB_R = duty - 2;             //DECIDE DUTY PB7 M0PWM1

    }

    else if(CarDir==Car_BACKWARD){


        /*MotorLeft
          * */

        PWM1_1_CMPA_R = 2   ;                    // DECIDE DUTY PA6  M1PWM2
        PWM1_1_CMPB_R =duty - 2;               //DECIDE DUTY PA7 M1PWM3

        /*MotorRight
          * */
        PWM0_0_CMPA_R = duty - 2;      // DECIDE DUTY PB6  M0PWM0
        PWM0_0_CMPB_R = 2;                     //DECIDE DUTY PB7 M0PWM1
    }
     PWM0_0_CTL_R = 0X00000001;      // START PWM0&1 module0
     PWM1_1_CTL_R = 0X00000001;      // START PWM2&3 module1

     PWM0_ENABLE_R = 0X00000003;     // ENABLE PWM0&1 output module0
     PWM1_ENABLE_R = 0X0000000C;     // ENABLE PWM2&3 output module1

}


