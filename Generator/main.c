/************************************************
 *  Generador									*
 *  Crhistian Segura							*
 *  main.c 										*
 ************************************************/
#include <msp430g2452.h>
#define LED_0 BIT0
#define LED_1 BIT6
#define LED_OUT P1OUT
#define LED_DIR P1DIR

unsigned int timerCount = 10, overVal=16000;
void main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

	BCSCTL1 = CALBC1_16MHZ;
	DCOCTL = CALDCO_16MHZ;

	LED_DIR |= (LED_0 + LED_1); // Set P1.0 and P1.6 to output direction
	LED_OUT &= ~(LED_0 + LED_1); // Set the LEDs off

	TA0CCTL0 = CCIE;                       // CCR0 interrupt enabled
	TA0CTL = TASSEL_2 + MC_1 + TACLR;           // SMCLK, upmode
	TA0CCR0 =  timerCount;                     // 12.5 Hz

	// Clear the timer and enable timer interrupt
	__enable_interrupt();
	__bis_SR_register(LPM0 + GIE); // LPM0 with interrupts enabled
}

int state=1;
unsigned int min=100,max=16000-1000;
int count=0;
int dir=1;
// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
	P1OUT ^= (LED_1);
	if (state && BIT0) {
		TA0CCR0 =  timerCount;                     // 12.5 Hz
	} else {
		TA0CCR0 =  overVal-timerCount;                     // 12.5 Hz
	}
	state ^= BIT0;
	if(timerCount<=min){
		timerCount=min;
		dir=+1;
	}
	if(timerCount >= max){
		timerCount=max;
		dir=-1;
	}
	timerCount+=dir;
	if((count++)>=100)
	{ // un decimo de la frecuencia
		count=0;
		P1OUT ^= LED_0;
		/*porc+=0.001;
		if(porc>=0.9)
			porc=0.1;*/
	}
}
