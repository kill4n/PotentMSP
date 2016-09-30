/*#include <msp430g2553.h>
#define LED_0 BIT0
#define LED_1 BIT6
#define LED_OUT P1OUT
#define LED_DIR P1DIR
unsigned int timerCount = 16000-2;
double porc=0.3;
void main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

	BCSCTL1 = CALBC1_16MHZ;
	DCOCTL = CALDCO_16MHZ;

	LED_DIR |= (LED_0 + LED_1); // Set P1.0 and P1.6 to output direction
	LED_OUT &= ~(LED_0 + LED_1); // Set the LEDs off

	TA0CCTL0 = CCIE;                       // CCR0 interrupt enabled
	TA1CCTL0 = CCIE;                       // CCR1 interrupt enabled
	TA1CTL =TASSEL_2 + MC_1 + TACLR;
	TA0CTL = TASSEL_2 + MC_1 + TACLR;           // SMCLK, upmode
	TA0CCR0 =  timerCount;                     // 12.5 Hz
	TA1CCR0 = 4000;

	// Clear the timer and enable timer interrupt
	__enable_interrupt();
	__bis_SR_register(LPM0 + GIE); // LPM0 with interrupts enabled
}

int state=1;
int count=0;
// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
	P1OUT ^= (LED_0);
	if (state && BIT0) {
		TA0CCR0 =  timerCount * porc+1;                     // 12.5 Hz
	} else {
		TA0CCR0 =  timerCount * (1-porc)+1;                     // 12.5 Hz
	}
	state ^= BIT0;
	// / *if((count++)>=100)
	//{ // un decimo de la frecuencia
	//	count=0;
	//	porc+=0.001;
	//	if(porc>=1)
	//		porc=0.1;
	//}* /
}
// Timer A1 interrupt
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0(void)
{
	P1OUT ^= LED_1;
}
 */
#include "msp430g2553.h"

void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);

unsigned char data;

void main(void)

{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

	P1DIR |= BIT0 + BIT6; // Set the LEDs on P1.0, P1.6 as outputs
	P1OUT = BIT0; // Set P1.0

	BCSCTL1 = CALBC1_1MHZ; // Set DCO to 1MHz
	DCOCTL = CALDCO_1MHZ; // Set DCO to 1MHz

	/* Configure hardware UART */
	P1SEL = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
	UCA0CTL1 |= UCSSEL_2; // Use SMCLK
	UCA0BR0 = 104; // Set baud rate to 9600 with 1MHz clock (Data Sheet 15.3.13)
	UCA0BR1 = 0; // Set baud rate to 9600 with 1MHz clock
	UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
	IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt

	__bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	data = UCA0RXBUF;
	UARTSendArray("Received command: ", 18);
	UARTSendArray(&data, 1);
	UARTSendArray("\n\r", 2);

	switch(data){
	case 'R':
	{
		P1OUT |= BIT0;
	}
	break;
	case 'r':
	{
		P1OUT &= ~BIT0;
	}
	break;
	case 'G':
	{
		P1OUT |= BIT6;
	}
	break;
	case 'g':
	{
		P1OUT &= ~BIT6;
	}
	break;
	default:
	{
		UARTSendArray("Unknown Command: ", 17);
		UARTSendArray(&data, 1);
		UARTSendArray("\n\r", 2);
	}
	break;
	}
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
