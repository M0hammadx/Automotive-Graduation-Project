/*
 * eeprom.c
 *
 *  Created on: Jun 29, 2018
 *      Author: MHmed Hatem
 */

#include "Eeprom.h"

#define MAX_SIZE  16
#define MAX_ELEMENT_NO 5
#define Start_Address   0x0000
#define Address_step(element_size)   element_size+4

typedef struct E2PROM_MetaData
{
    uint8_t ID;
    uint16_t start_address;
    uint8_t act_size;

} g_MetaData;

typedef struct E2PROM_DATA
{
    uint8_t size;
    uint8_t data[MAX_SIZE - 1];
} g_E2data;

g_MetaData EE_var[5] = {
        { ID_1, Start_Address, 0 }, { ID_2, Start_Address
                                              + Address_step(MAX_SIZE),
                                      0 },
        { ID_3, Start_Address + 2 * Address_step(MAX_SIZE), 0 }, {
                ID_4, Start_Address + 3 * Address_step(MAX_SIZE), 0 },
        { ID_5, Start_Address + 4 * Address_step(MAX_SIZE), 0 } };

//static bool I2CMasterTimeout(uint32_t ui32Base);

void Eeprom_init(void)
{
    int i;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C2);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinConfigure(GPIO_PE4_I2C2SCL);
    GPIOPinConfigure(GPIO_PE5_I2C2SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTE_BASE, GPIO_PIN_4);
    GPIOPinTypeI2C(GPIO_PORTE_BASE, GPIO_PIN_5);
    I2CMasterInitExpClk(I2C2_BASE, SysCtlClockGet(), false);
    I2CMasterTimeoutSet(I2C2_BASE, 0xFF);
    //ROM_SysCtlDelay(5500000);

    for (i = 0; i < MAX_ELEMENT_NO; i++)
    {
        EE_var[i].act_size = Eeprom_readByte(EE_var[i].start_address);
    }
}

void Eeprom_writeArrayID(uint8_t ID, uint8_t* array, uint8_t size)
{
    int i = 1;
    uint8_t arr[MAX_SIZE];
    int idx = 0;
    if (size < MAX_SIZE)
    { //check data length
        while ((idx < (MAX_ELEMENT_NO)) && EE_var[idx].ID != ID)
        {
            idx++;
        }
        if (idx >= MAX_ELEMENT_NO)
        {
            //error report
        }
        else
        {
            EE_var[idx].act_size = size;

            arr[0] = size;

            for (; i < 16; i++)
            { //send 1st 15-byte
                arr[i] = array[i - 1];
            }

            Eeprom_writeArray(EE_var[idx].start_address, arr, size + 1);
        }
    }
    else
    {
    }
}

void Eeprom_readArrayID(uint8_t ID, uint8_t *array, uint8_t *size)
{
    int idx = 0;
    while ((idx < (MAX_ELEMENT_NO)) && EE_var[idx].ID != ID)
    {
        idx++;
    }
    if (idx >= MAX_ELEMENT_NO)
    {
        //error report
    }
    else
    {
        *size = EE_var[idx].act_size;
        Eeprom_readArray(EE_var[idx].start_address + sizeof(array[0]), array,
                         (*size));
    }
}

//takes address + data to send
void Eeprom_writeByte(uint32_t address, uint8_t data)
{
    bool A0 = (address >> 8) & 1;
    ROM_I2CMasterSlaveAddrSet(I2C2_BASE, 0x50 | A0, false); // The address of the Slave is 0x50
    ROM_I2CMasterDataPut(I2C2_BASE, address);
    ROM_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while (ROM_I2CMasterBusy(I2C2_BASE))
        ;
    ROM_I2CMasterDataPut(I2C2_BASE, data);
    ROM_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while (ROM_I2CMasterBusy(I2C2_BASE))
        ;
    ROM_SysCtlDelay(5500000); // writing time
}

//  takes address returns data at address
uint8_t Eeprom_readByte(uint32_t address)
{
    uint32_t recv = 0x5555;
    bool A0 = (address >> 8) & 1;
    ROM_I2CMasterSlaveAddrSet(I2C2_BASE, 0x50 | A0, false);
    ROM_I2CMasterDataPut(I2C2_BASE, address);
    ROM_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_SEND); //dummy
    while (ROM_I2CMasterBusy(I2C2_BASE))
        ;
    ROM_I2CMasterSlaveAddrSet(I2C2_BASE, 0x50 | A0, true);
    ROM_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
    while (ROM_I2CMasterBusy(I2C2_BASE))
        ;
    recv = ROM_I2CMasterDataGet(I2C2_BASE); //test
    return recv;
}

//takes address , data array , and size of array
void Eeprom_writeArray(uint32_t address, uint8_t *data, uint8_t size)
{
    int i;
    //int bla;
    bool A0 = (address >> 8) & 1;
    ROM_I2CMasterSlaveAddrSet(I2C2_BASE, 0x50 | A0, false); // The address of the Slave is 0x50
    ROM_I2CMasterDataPut(I2C2_BASE, address);
    ROM_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while (ROM_I2CMasterBusy(I2C2_BASE))
        ;
    if (size > 16)
        size = 16;
    for (i = 0; i < size - 1; i++)
    {
        //bla = data[i];
        ROM_I2CMasterDataPut(I2C2_BASE, data[i]); // data to be saved at Addr 0x11 under autoincrement mode
        ROM_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
        while (ROM_I2CMasterBusy(I2C2_BASE))
            ;
    }
    ROM_I2CMasterDataPut(I2C2_BASE, data[i]); // data to be saved at Addr 0x12 under autoincrement mode
    ROM_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while (ROM_I2CMasterBusy(I2C2_BASE))
        ;
    ROM_SysCtlDelay(5500000); // writing time
}

//takes address , arr to store data in , number of bytes to read
void Eeprom_readArray(uint32_t address, uint8_t *array, uint8_t size)
{
    int i = 1;
    bool A0 = (address >> 8) & 1;
    ROM_I2CMasterSlaveAddrSet(I2C2_BASE, 0x50 | A0, false);
    ROM_I2CMasterDataPut(I2C2_BASE, address); // Addr 0x11
    ROM_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_SEND);
    while (I2CMasterBusy(I2C2_BASE))
        ;
    //
    ROM_I2CMasterSlaveAddrSet(I2C2_BASE, 0x50 | A0, true);
    ROM_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
    while (I2CMasterBusy(I2C2_BASE))
        ;
    array[0] = ROM_I2CMasterDataGet(I2C2_BASE); //test
    for (i = 1; i < size; i++)
    {
        ROM_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
        //
        while (I2CMasterBusy(I2C2_BASE))
            ;
        array[i] = ROM_I2CMasterDataGet(I2C2_BASE); //Receive
    }
    ROM_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    //
    while (I2CMasterBusy(I2C2_BASE))
        ;
}

//bool I2CMasterTimeout(uint32_t ui32Base)
//{
//    // Return the bus timeout status
//    if (HWREG(ui32Base + I2C_O_MCS) & I2C_MCS_CLKTO)
//    {
//        return (true);
//    }
//    else
//    {
//        return (false);
//    }
//}

/*
 n is number of bytes and >= 3.

 1)
 Put data to I2C
 Send control command:I2C_MASTER_CMD_BURST_SEND_START
 wait until ready

 2)
 Put data to I2C
 I2C_MASTER_CMD_BURST_SEND_CONT
 wait until ready

 ....
 repeat step 2) n-3 times
 .....

 3)
 Put data to I2C
 I2C_MASTER_CMD_BURST_SEND_FINISH
 wait until ready
 */

