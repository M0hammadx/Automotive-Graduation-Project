#include "steering.h"
#include <math.h>
#include "inc/tm4c123gh6pm.h"

static char InitFlag = 0;
//static void Motor_Forward(void);
//static void Motor_Backward(void);	
static void Motor_Stop(void);
static void Delay_20ms(void);

static void Motor_Backward(void);
static void Motor_Forward(void);
static void steering_speed(uint16_t duty);



void steering_init(unsigned long initial_position){ //initial_position in degree for example most left = 0

  // Enable the clock for peripherals PortD and QEI0
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
    while (!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_QEI0))
    {
    }; //wait until clock stable
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while (!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
    {
    }; //wait until clock stable

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    while (!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1))
    {
    }; //wait until clock stable

    // Configure the PD6, PD7 for QEI signals
    GPIO_PORTD_LOCK_R |= 0x4C4F434B;
    GPIO_PORTD_CR_R |= 0xC0;
    GPIO_PORTD_DIR_R &= ~0xC0;
    GPIO_PORTD_DEN_R |= 0xC0;
    GPIO_PORTD_AMSEL_R &= ~0xC0;
    GPIO_PORTD_AFSEL_R |= 0xC0;
    GPIO_PORTD_PCTL_R &= ~0xFF000000;
    GPIO_PORTD_PCTL_R |= 0x66000000;

    // Configure the QEI0 to increment for both PhA and PhB for quadrature input with "QEI0_PPR" PPR
    //  ROM_QEIConfigure(QEI0_BASE, QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_QUADRATURE, (MAX_POS));
    // Configure the QEI0 for Velocity Calculation, Predivide by 1 at "VEL_INT_FREQ" Hz
    //  ROM_QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1, ROM_SysCtlClockGet() / VEL_INT_FREQ);
    //  ROM_QEIVelocityEnable(QEI0_BASE);
    QEI0_CTL_R |= 0X00028;
    QEI0_MAXPOS_R = 0xFFFFFF;
    QEI0_LOAD_R = (800000) - 1;
    QEI0_CTL_R |= 0X0001;
    // Enable the QEI0
    // ROM_QEIEnable(QEI0_BASE);

    //Set the current encoder position to 0
    // QEIPositionSet(QEI0_BASE,initial_position);
    QEI0_POS_R = initial_position * 203;

    /*************************MOTOR_INIT Direction pins***********************************/
    //B2 E0
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);//enable clocks on port
    while (!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
    {
    }; //wait until clock stable
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);//enable clocks on port
    while (!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
    {
    }; //wait until clock stable
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2);//set digital output
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0);//set digital output
    ROM_GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_STRENGTH_8MA,
            GPIO_PIN_TYPE_STD);
    ROM_GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_STRENGTH_8MA,
            GPIO_PIN_TYPE_STD);
    ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
    ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, 0x00);

    /*********************** MOTOR_INIT Speed pin ****************************************/
    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    ROM_GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
    ROM_GPIOPinConfigure(GPIO_PD0_M1PWM0); //PWM1_0_CMPA_R
    PWM1_0_CTL_R = 0;
    PWM1_0_GENA_R |= 0XC8;// LOW ON LOAD , HIGH ON CMPA
    PWM1_0_LOAD_R = 625 - 1;
    PWM1_0_CTL_R = 0X00000001;// START PWM1 module1
    PWM1_ENABLE_R = 0X00000001;// ENABLE PWM0 output module1
    InitFlag = 1;

}

static void steering_speed(uint16_t duty)
{
    PWM1_0_CMPA_R = duty - 2;
}

unsigned long steering_AngleGet(void)
{
// Calculate the position in degree
    return ROM_QEIPositionGet(QEI0_BASE) / 203; //*MAX_ANGLE / MAX_POS; //203 1 degree ticks
}

//unsigned long steering_VelocityGet(void){
//unsigned long ret_val=0;
// Calculate the velocity in RPM
//ret_val= ROM_QEIVelocityGet(QEI0_BASE) * VEL_INT_FREQ * 60 / QEI0_PPR;
//return ret_val;
//}

long steering_DirectionGet(void)
{

    return ROM_QEIDirectionGet(QEI0_BASE);
}

uint8_t steering_AngleSet(unsigned long angle)
{
    signed long current_angle = steering_AngleGet();
    signed long angle_in_ticks = angle * 203; // MAX_ANGLE *MAX_POS;
    uint16_t steerSpeed = 100;

    while (1)
    {
        if (current_angle < angle)
        {
            Motor_Backward();

            steerSpeed = 300;
            //steering_speed(steerSpeed);
            while (angle_in_ticks - ROM_QEIPositionGet(QEI0_BASE) > 3500)
            {
                //if()//increment current angle
                steerSpeed++;
                if (steerSpeed == 620)
                    steerSpeed = 100;

                steering_speed(steerSpeed);
                Delay_20ms();

                //delay;
            }
            steerSpeed = 200;
            while (angle_in_ticks - ROM_QEIPositionGet(QEI0_BASE) > 2000)
            {
                steerSpeed++;
                if (steerSpeed == 620)
                    steerSpeed = 100;
                steering_speed(steerSpeed);
                Delay_20ms();
            }
            steerSpeed = 200;
            while (angle_in_ticks - ROM_QEIPositionGet(QEI0_BASE) > 200)
            {
                steering_speed(steerSpeed++);
                if (steerSpeed == 620)
                    steerSpeed = 100;
                Delay_20ms();

            }

            Motor_Stop();
        }
        if (current_angle > angle)
        {
            Motor_Forward();
            steerSpeed = 300;
            //steering_speed(steerSpeed);
            while (ROM_QEIPositionGet(QEI0_BASE) - angle_in_ticks > 3500)
            {
                //if()//increment current angle
                steerSpeed++;
                if (steerSpeed == 620)
                    steerSpeed = 100;
                steering_speed(steerSpeed);
                Delay_20ms();
                //delay;
            }
            steerSpeed = 200;
            while (ROM_QEIPositionGet(QEI0_BASE) - angle_in_ticks > 2000)
            {
                steerSpeed++;
                if (steerSpeed == 620)
                    steerSpeed = 100;
                steering_speed(steerSpeed);
                Delay_20ms();
            }
            steerSpeed = 200;
            while (ROM_QEIPositionGet(QEI0_BASE) - angle_in_ticks > 200)
            {
                steering_speed(steerSpeed++);
                if (steerSpeed == 620)
                    steerSpeed = 100;
                Delay_20ms();

            }

            Motor_Stop();
        }
        else
        {
            Motor_Stop();
        }
        if ((ROM_QEIPositionGet(QEI0_BASE) - angle_in_ticks) <= 200
                || (angle_in_ticks - ROM_QEIPositionGet(QEI0_BASE)) <= 200)
            break;

    }
    return 0;
}
static void Motor_Forward(void)
{
    if (InitFlag == 0)
    {
        //generate error flag
    }
    else
    {
        ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_PIN_2);
        ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, 0x00);
    }
}

static void Motor_Backward(void)
{

    if (InitFlag == 0)
    {
        //generate error flag
    }
    else
    {

        ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
        ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_PIN_0);
    }
}

static void Motor_Stop(void)
{
    ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
    ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, 0x00);
    steering_speed(2);
}

static void Delay_20ms(void)
{
    int k = 0;
    for (k = 0; k <= 16000; k++)
        ;
}
