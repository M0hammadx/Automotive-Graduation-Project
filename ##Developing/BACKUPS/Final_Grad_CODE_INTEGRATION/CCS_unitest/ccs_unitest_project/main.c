

/**
 * main.c
 */
int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //80 MHZ
    while(1){}

	return 0;
}
