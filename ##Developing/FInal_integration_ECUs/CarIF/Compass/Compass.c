#include "Compass.h"

static void ReadByteArray(unsigned int *arr, uint8_t cnt);
static void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...);
//static uint32_t I2CReceive(uint32_t slave_addr, int8_t reg);

static unsigned int data[6] = { 1, 2, 3, 4, 5, 6 };
static double heading;// headingDegrees;
static unsigned int x, y, z;
int x_, y_, z_;

void Compass_Init(void)
{

   ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
   while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_I2C1)){}; //wait until clock stable
   ROM_SysCtlPeripheralReset(SYSCTL_PERIPH_I2C1);

   ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
   while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){}; //wait until clock stable
   ROM_GPIOPinConfigure(GPIO_PA6_I2C1SCL);
   ROM_GPIOPinConfigure(GPIO_PA7_I2C1SDA);
   ROM_GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
   ROM_GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);

   ROM_I2CMasterInitExpClk(I2C1_BASE, ROM_SysCtlClockGet(), false);

    //Put the HMC5883 IC into the correct operating mode
    //open communication with HMC5883
    //select mode register
    //continuous measurement mode
    I2CSend(0x1E, 2, 0x02, 0x00);

}

void Compass_Get_Angles(double * Angle)
{

    ReadByteArray(data, 6);
    x = ((data[0] << 8) | data[1]);
    if (x & 0x8000)
        x_ =(signed int) -32768 + ((int)x & ~0x8000);
    else
        x_ = x;
    z = ((data[2] << 8) | data[3]);
    if (z & 0x8000)
        z_ =  (signed int) -32768 + ((int)z & ~0x8000);
    else
        z_ = z;
    y = ((data[4] << 8) | data[5]);
    if (y & 0x8000)
        y_ =  (signed int) -32768 + ((int)y & ~0x8000);
    else
        y_ = y;

    heading = atan2(y_, x_);

    // Correct for when signs are reversed.
    if (heading < 0)
        heading += 2 * PI;

// Check for wrap due to addition of declination.
    if (heading > 2 * PI)
        heading -= 2 * PI;

    // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
    // Find yours here: http://www.magnetic-declination.com/
    // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
    // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.

    // heading += 0.22;

    // Convert radians to degrees for readability.
    *Angle = heading * 180 / PI;

}

static void ReadByteArray(unsigned int *arr, uint8_t cnt)
{
    int i = 1;

    I2CMasterSlaveAddrSet(I2C1_BASE, 0x1E, false); //Tell the HMC5883L where to begin reading data

    I2CMasterDataPut(I2C1_BASE, 0x03); //select register 3, X MSB register

    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);

    while (I2CMasterBusy(I2C1_BASE))
        ;

    I2CMasterSlaveAddrSet(I2C1_BASE, 0x1E, true);

    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

    while (I2CMasterBusy(I2C1_BASE))
        ;

    arr[0] = I2CMasterDataGet(I2C1_BASE); //test

    for (i = 1; i < cnt; i++)
    {
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
//
        while (I2CMasterBusy(I2C1_BASE))
            ;

        arr[i] = I2CMasterDataGet(I2C1_BASE); //Receive
    }

    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
//
    while (I2CMasterBusy(I2C1_BASE))
        ;

}

static void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...)
{
    va_list vargs;
    uint8_t i;
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false);

    //stores list of variable number of arguments

    //specifies the va_list to "open" and the last fixed argument
    //so vargs knows where to start looking
    va_start(vargs, num_of_args);

    //put data to be sent into FIFO
    I2CMasterDataPut(I2C1_BASE, va_arg(vargs, uint32_t));

    //if there is only one argument, we only need to use the
    //single send I2C function
    if (num_of_args == 1)
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while (I2CMasterBusy(I2C1_BASE))
            ;

        //"close" variable argument list
        va_end(vargs);
    }

    //otherwise, we start transmission of multiple bytes on the
    //I2C bus
    else
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while (I2CMasterBusy(I2C1_BASE))
            ;

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module

        for (i = 1; i < (num_of_args - 1); i++)
        {
            //put next piece of data into I2C FIFO
            I2CMasterDataPut(I2C1_BASE, va_arg(vargs, uint32_t));
            //send next data that was just placed into FIFO
            I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while (I2CMasterBusy(I2C1_BASE))
                ;
        }

        //put last piece of data into I2C FIFO
        I2CMasterDataPut(I2C1_BASE, va_arg(vargs, uint32_t));
        //send next data that was just placed into FIFO
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
        // Wait until MCU is done transferring.
        while (I2CMasterBusy(I2C1_BASE))
            ;

        //"close" variable args list
        va_end(vargs);
    }
}

/*
static uint32_t I2CReceive(uint32_t slave_addr, int8_t reg)
{
    //specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false);

    //specify register to be read
    I2CMasterDataPut(I2C1_BASE, reg);

    //send control byte and register address byte to slave device
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    //wait for MCU to finish transaction
    while (I2CMasterBusy(I2C1_BASE))
        ;

    //specify that we are going to read from slave device
    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, true);

    //send control byte and read from the register we
    //specified
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

    //wait for MCU to finish transaction
    while (I2CMasterBusy(I2C1_BASE))
        ;

    //return data pulled from the specified register
    return I2CMasterDataGet(I2C1_BASE);
}
*/



