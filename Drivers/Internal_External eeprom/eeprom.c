
#include <stdint.h> // ift
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_i2c.h"

uint8_t lcd[6]={0x98,0x87,0x76,0x65,0x54,0x43};


#define GPIO_PA6_I2C1SCL        0x00001803
#define GPIO_PA7_I2C1SDA        0x00001C03

unsigned long data;
uint32_t ReadByte(uint32_t address);
void WriteByte(uint32_t address,uint8_t send);
void WriteByteArray(uint32_t address,uint8_t *send,uint8_t n);
 void ReadByteArray(uint32_t address,uint32_t *arr,uint8_t cnt);

int main(void)
{//some source said delay is 5-10mx max
uint32_t arr[6];
//
// Set the clocking to run directly from the external crystal/oscillator.
// TODO: The SYSCTL_XTAL_ value must be changed to match the value of the
// crystal on your board.
//
SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);

//
// The I2C1 peripheral must be enabled before use.
//
SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);

//
// For this example I2C0 is used with PortB[3:2]. The actual port and
// pins used may be different on your part, consult the data sheet for
// more information. GPIO port B needs to be enabled so these pins can
// be used.
// TODO: change this to whichever GPIO port you are using.
//
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

//
// Select the I2C function for these pins. This function will also
// configure the GPIO pins pins for I2C operation, setting them to
// open-drain operation with weak pull-ups. Consult the data sheet
// to see which functions are allocated per pin.
// TODO: change this to select the port/pin you are using.
//
//GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_2 | GPIO_PIN_3);
GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6); // I2CSCL
GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);

//
// Configure the pin muxing for I2C0 functions on port B2 and B3.
// This step is not necessary if your part does not support pin muxing.
// TODO: change this to select the port/pin you are using.
//
GPIOPinConfigure(GPIO_PA6_I2C1SCL);
GPIOPinConfigure(GPIO_PA7_I2C1SDA);

//
// Enable and initialize the I2C0 master module. Use the system clock for
// the I2C0 module. The last parameter sets the I2C data transfer rate.
// If false the data rate is set to 100kbps and if true the data rate will
// be set to 400kbps. For this example we will use a data rate of 100kbps.
//
I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), false);

//
// Tell the master module what address it will place on the bus when
// communicating with the slave. Set the address to SLAVE_ADDRESS
// (as set in the slave module). The receive parameter is set to false
// which indicates the I2C Master is initiating a writes to the slave. If
// true, that would indicate that the I2C Master is initiating reads from
// the slave.
//

while(1)
{
	
WriteByteArray(0xF0,lcd,6);//max address 0x1FF 
	WriteByte(0xF0,0x99);
	WriteByte(0xF1,0x88);
	data=ReadByte(0xF0);
	data=ReadByte(0xF1);
ReadByteArray(0xF0,arr,6);

}
//return(0);
}


//takes address + data to send
void WriteByte(uint32_t address,uint8_t send){

	bool A0=(address>>8)&1;
	I2CMasterSlaveAddrSet(I2C1_BASE, 0x50|A0, false); // The address of the Slave is 0x50

I2CMasterDataPut(I2C1_BASE, address); 

I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);

while(I2CMasterBusy(I2C1_BASE));


I2CMasterDataPut(I2C1_BASE, send); 

I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

while(I2CMasterBusy(I2C1_BASE));

SysCtlDelay(5500000); // writing time 
	
}
//	takes address returns data at address
uint32_t ReadByte(uint32_t address){

	
	uint32_t recv=0x5555;
		bool A0=(address>>8)&1;
	
I2CMasterSlaveAddrSet(I2C1_BASE, 0x50|A0, false);

I2CMasterDataPut(I2C1_BASE, address);

I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND); //dummy

while(I2CMasterBusy(I2C1_BASE));


I2CMasterSlaveAddrSet(I2C1_BASE, 0x50|A0, true);

I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

while(I2CMasterBusy(I2C1_BASE));

recv = I2CMasterDataGet(I2C1_BASE); //test


	
	return recv;
	
}

	//takes address , data array , and size of array
void WriteByteArray(uint32_t address,uint8_t *send,uint8_t n){
	
	
	int i,bla;
	
	bool A0=(address>>8)&1;
	
	I2CMasterSlaveAddrSet(I2C1_BASE, 0x50|A0, false); // The address of the Slave is 0x50

I2CMasterDataPut(I2C1_BASE, address); 

I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);

while(I2CMasterBusy(I2C1_BASE));

if(n>=15)n=15;
	
for (i=0;i<n;i++)
{
	bla=send[i];
I2CMasterDataPut(I2C1_BASE, lcd[i]); // data to be saved at Addr 0x11 under autoincrement mode

I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

while(I2CMasterBusy(I2C1_BASE));

}
	

I2CMasterDataPut(I2C1_BASE, lcd[i]); // data to be saved at Addr 0x12 under autoincrement mode

I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

while(I2CMasterBusy(I2C1_BASE));

SysCtlDelay(5500000); // writing time
	
}

//takes address , arr to store data in , number of bytes to read
void ReadByteArray(uint32_t address,uint32_t *arr,uint8_t cnt){
int i=1;
	
		bool A0=(address>>8)&1;
	
I2CMasterSlaveAddrSet(I2C1_BASE, 0x50|A0, false);

I2CMasterDataPut(I2C1_BASE, address); // Addr 0x11

I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);

while(I2CMasterBusy(I2C1_BASE));

//
I2CMasterSlaveAddrSet(I2C1_BASE, 0x50|A0, true);

I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

while(I2CMasterBusy(I2C1_BASE));

arr[0] = I2CMasterDataGet(I2C1_BASE); //test
	

for (i=1;i<cnt;i++)
{
I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
//
while(I2CMasterBusy(I2C1_BASE));

arr[i] = I2CMasterDataGet(I2C1_BASE); //Receive
}

I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
//
while(I2CMasterBusy(I2C1_BASE));


	
}
