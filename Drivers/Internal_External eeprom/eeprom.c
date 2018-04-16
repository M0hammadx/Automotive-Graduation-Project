
#define TARGET_IS_BLIZZARD_RB1
#define PART_TM4C123GH6PM


#include <stdint.h> // ift
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_i2c.h"


uint8_t lcd[18]={0x98,0x87,0x76,0x65,0x54,0x43,0x98,0x87,0x76,0x65,0x54,0x43,0x98,0x87,0x76,0x65,0x54,0x43};
	uint8_t dat[18]={0x98,0x87,0x76,0x65,0x54,0x43,0x98,0x87,0x76,0x65,0x54,0x43,0x98,0x87,0x76,0x65,0x54,0x43};


#define MAX_SIZE  20

#define ID_1    1
#define ID_2    2
#define ID_3    3
#define ID_4 		4
#define ID_5		5
#define MAX_ELEMENT_NO 5

#define Start_Address   0x0000
#define Address_step(element_size)   element_size+4
typedef struct E2PROM_Def
{
	uint8_t ID;
	uint16_t start_address;
	
	uint8_t act_size;
	
}def;  

def EE_var[5]= {{ID_1,Start_Address,18},
{ID_2,Start_Address+Address_step(MAX_SIZE),0},
{ID_3,Start_Address+2*Address_step(MAX_SIZE),0},
{ID_4,Start_Address+3*Address_step(MAX_SIZE),0},
{ID_5,Start_Address+4*Address_step(MAX_SIZE),0}};

typedef struct E2PROM_DATA
{
    uint8_t size;
    uint8_t data[MAX_SIZE];
}E2data;

unsigned long data;
uint32_t ReadByte(uint32_t address);
void WriteByte(uint32_t address,uint8_t send);
void WriteByteArray(uint32_t address,uint8_t *send,uint8_t n);
 void ReadByteArray(uint32_t address,uint32_t *arr,uint8_t cnt);

 void Write_ee(uint8_t ID,uint8_t *send,uint8_t n);
void Read_ee(uint8_t ID,uint32_t *arr,uint8_t *cnt);

int main(void)
{
uint32_t arr[19];
uint8_t cnt;
	for(int i=0;i<18;i++){
		dat[i]=i;
	}
//
// Set the clocking to run directly from the external crystal/oscillator.
// TODO: The SYSCTL_XTAL_ value must be changed to match the value of the
// crystal on your board.
//
ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);

//
// The I2C1 peripheral must be enabled before use.
//
ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);

//
// For this example I2C0 is used with PortB[3:2]. The actual port and
// pins used may be different on your part, consult the data sheet for
// more information. GPIO port B needs to be enabled so these pins can
// be used.
// TODO: change this to whichever GPIO port you are using.
//
ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

//
// Select the I2C function for these pins. This function will also
// configure the GPIO pins pins for I2C operation, setting them to
// open-drain operation with weak pull-ups. Consult the data sheet
// to see which functions are allocated per pin.
// TODO: change this to select the port/pin you are using.
//
//GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_2 | GPIO_PIN_3);

ROM_GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6); // I2CSCL
ROM_GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);

//
// Configure the pin muxing for I2C0 functions on port B2 and B3.
// This step is not necessary if your part does not support pin muxing.
// TODO: change this to select the port/pin you are using.
//
ROM_GPIOPinConfigure(GPIO_PA6_I2C1SCL);
ROM_GPIOPinConfigure(GPIO_PA7_I2C1SDA);

//
// Enable and initialize the I2C0 master module. Use the system clock for
// the I2C0 module. The last parameter sets the I2C data transfer rate.
// If false the data rate is set to 100kbps and if true the data rate will
// be set to 400kbps. For this example we will use a data rate of 100kbps.
//

ROM_I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), false);

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
Write_ee(ID_1,dat,18);
//WriteByteArray(0x0,dat,16);//max address 0x1FF 
//WriteByteArray(0x0+12,data,6);
	//WriteByte(0xF0,0x99);
	//WriteByte(0xF1,0x88);
	//data=ReadByte(0xF0);
	//data=ReadByte(0xF1);
//ReadByteArray(0x0,arr,19);
Read_ee(ID_1,arr,&cnt);
}
//return(0);
}

void Write_ee(uint8_t ID,uint8_t *send,uint8_t n){
	int idx=0;
	while(EE_var[idx].ID!=ID){idx++;}
	
	
	uint8_t arr[16];
	arr[0]=n;
	int i=1;
	for(;i<16;i++){//send 1st 15-byte
		arr[i]=send[i-1];
	}
	
  WriteByteArray(EE_var[idx].start_address,arr,16 );		
if(n>15){
	/*uint8_t arr2[n-15];
	for(i=0;i<n-15;i++){
		arr2[i]=send[i+15];
	}*/
  WriteByteArray(EE_var[idx].start_address+16,&send[15],n-15 );		
	
}
}

void Read_ee(uint8_t ID,uint32_t *arr,uint8_t *cnt){
	*cnt=EE_var[0].act_size;
	int i=0;
	while(EE_var[i].ID!=ID){
	i++;*cnt=EE_var[i].act_size;
	}
	
	ReadByteArray(EE_var[i].start_address,arr,(*cnt )+1);		
	
}

//takes address + data to send
void WriteByte(uint32_t address,uint8_t send){

	bool A0=(address>>8)&1;
	ROM_I2CMasterSlaveAddrSet(I2C1_BASE, 0x50|A0, false); // The address of the Slave is 0x50

ROM_I2CMasterDataPut(I2C1_BASE, address); 

ROM_I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);

while(ROM_I2CMasterBusy(I2C1_BASE));


ROM_I2CMasterDataPut(I2C1_BASE, send); 

ROM_I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

while(ROM_I2CMasterBusy(I2C1_BASE));

ROM_SysCtlDelay(5500000); // writing time
	
}
//	takes address returns data at address
uint32_t ReadByte(uint32_t address){

	
	uint32_t recv=0x5555;
		bool A0=(address>>8)&1;
	
ROM_I2CMasterSlaveAddrSet(I2C1_BASE, 0x50|A0, false);

ROM_I2CMasterDataPut(I2C1_BASE, address);

ROM_I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND); //dummy

while(ROM_I2CMasterBusy(I2C1_BASE));


ROM_I2CMasterSlaveAddrSet(I2C1_BASE, 0x50|A0, true);

ROM_I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

while(ROM_I2CMasterBusy(I2C1_BASE));

recv = ROM_I2CMasterDataGet(I2C1_BASE); //test


	
	return recv;
	
}

	//takes address , data array , and size of array
void WriteByteArray(uint32_t address,uint8_t *send,uint8_t n){
	
	
	int i,bla;
	
	bool A0=(address>>8)&1;
	
	ROM_I2CMasterSlaveAddrSet(I2C1_BASE, 0x50|A0, false); // The address of the Slave is 0x50

ROM_I2CMasterDataPut(I2C1_BASE, address); 

ROM_I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);

while(ROM_I2CMasterBusy(I2C1_BASE));

if(n>16)n=16;
	
for (i=0;i<n-1;i++)
{
	bla=send[i];
ROM_I2CMasterDataPut(I2C1_BASE, send[i]); // data to be saved at Addr 0x11 under autoincrement mode

ROM_I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

while(ROM_I2CMasterBusy(I2C1_BASE));

}
	

ROM_I2CMasterDataPut(I2C1_BASE, send[i]); // data to be saved at Addr 0x12 under autoincrement mode

ROM_I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

while(ROM_I2CMasterBusy(I2C1_BASE));

ROM_SysCtlDelay(5500000); // writing time
	
}

//takes address , arr to store data in , number of bytes to read
void ReadByteArray(uint32_t address,uint32_t *arr,uint8_t cnt){
int i=1;
	
		bool A0=(address>>8)&1;
	
ROM_I2CMasterSlaveAddrSet(I2C1_BASE, 0x50|A0, false);

ROM_I2CMasterDataPut(I2C1_BASE, address); // Addr 0x11

ROM_I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);

while(ROM_I2CMasterBusy(I2C1_BASE));

//
ROM_I2CMasterSlaveAddrSet(I2C1_BASE, 0x50|A0, true);

ROM_I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

while(ROM_I2CMasterBusy(I2C1_BASE));

arr[0] = ROM_I2CMasterDataGet(I2C1_BASE); //test
	

for (i=1;i<cnt;i++)
{
ROM_I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
//
while(ROM_I2CMasterBusy(I2C1_BASE));

arr[i] = ROM_I2CMasterDataGet(I2C1_BASE); //Receive
}

ROM_I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
//
while(ROM_I2CMasterBusy(I2C1_BASE));


	
}


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

