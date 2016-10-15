#include <msp430.h>

#define LED_0 BIT0
#define LED_1 BIT6
#define LED_OUT P1OUT
#define LED_DIR P1DIR
unsigned char data = '@';
unsigned int da1 = 99;
unsigned int da2 = 99;
unsigned int da3 = 99;
void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	/* Use Calibration values for 1MHz Clock DCO*/
	DCOCTL = 0;
	BCSCTL1 = CALBC1_16MHZ;
	DCOCTL = CALDCO_16MHZ;

	P1DIR |= BIT0 + BIT6; // Set the LEDs on P1.0, P1.6 as outputs
	P1OUT = BIT0; // Set P1.0

	/* Configure Pin Muxing P1.1 RXD and P1.2 TXD */
	P1SEL = BIT1 | BIT2 ;
	P1SEL2 = BIT1 | BIT2;

	/* Place UCA0 in Reset to be configured */
	UCA0CTL1 = UCSWRST;

	/* Configure */
	UCA0CTL1 |= UCSSEL_2; // SMCLK
	UCA0BR0 = 82; // 1MHz 9600
	UCA0BR1 = 06; // 1MHz 9600
	UCA0MCTL = UCBRS1+ UCBRS2; // Modulation UCBRSx = 1

	/* Take UCA0 out of reset */
	UCA0CTL1 &= ~UCSWRST;

	/* Enable USCI_A0 RX interrupt */
	IE2 |= UCA0RXIE;

	LED_DIR |= (LED_0 + LED_1); // Set P1.0 and P1.6 to output direction
	LED_OUT &= ~(LED_0 + LED_1); // Set the LEDs off

	TA0CCTL0 = CCIE;                       		// CCR0 interrupt enabled
	TA0CTL = TASSEL_2 + ID_3 + MC_1 + TACLR;    // SMCLK/8, upmode
	TA0CCR0 =  16000;                     		// ?¿ Hz

	// Clear the timer and enable timer interrupt
	__enable_interrupt();
	__bis_SR_register(LPM0 + GIE); // LPM0 with interrupts enabled
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
	P1OUT ^= (LED_1);
	//unsigned char dataArray[2] = {0x42, 0x43}; // Variable dataArray is now an unsigned char pointer (the type accepted by the function)
	//UARTSendArray(dataArray, 2);//data = sizeof(TxArray)/sizeof(unsigned char);

	// int data[2]={1023, 235};
	// UARTSendArray(data, 4); // Note because the UART transmits bytes it is necessary to send two bytes for each integer hence the data length is twice the array length

	//arr_int[0] = da2/da1;
	// convert 123 to string [buf]
	//	UARTSendByte((unsigned char)arr_int[0]);
	UARTSendArray("@0", 2);
}
/* Echo back RXed character, confirm TX buffer is ready first */
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	switch ((char)UCA0RXBUF) {
	case 'A':
		P1OUT |= BIT0;
		break;
	default:
		P1OUT &= ~BIT0;
		break;
	}
	while (!(IFG2&UCA0TXIFG)); // USCI_A0 TX buffer ready?
	UCA0TXBUF = UCA0RXBUF; // TX -&amp;gt; RXed character
}

void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength){
	// Send number of bytes Specified in ArrayLength in the array at using the hardware UART 0
	// Example usage: UARTSendArray("Hello", 5);
	// int data[2]={1023, 235};
	// UARTSendArray(data, 4); // Note because the UART transmits bytes it is necessary to send two bytes for each integer hence the data length is twice the array length

	while(ArrayLength--){ // Loop until StringLength == 0 and post decrement
		while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
		UCA0TXBUF = *TxArray; //Write the character at the location specified py the pointer
		TxArray++; //Increment the TxString pointer to point to the next character
	}
}
