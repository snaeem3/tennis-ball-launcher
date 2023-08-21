header.h
#include "msp.h"
#include "driverlib.h"
#include "stdio.h"

#define DIR0 GPIO_PORT_P4,GPIO_PIN1
#define PUL0 GPIO_PORT_P5,GPIO_PIN1

#define ON_OFF TA0CCR1
#define DUTY TA0CCR1

#define SPEED TA0CCR0
#define PERIOD TA0CCR0

#define DC_PIN_1 GPIO_PORT_P5,GPIO_PIN4
#define DC_PIN_2 GPIO_PORT_P5,GPIO_PIN5

#define OFFSET ((9000 + 9250)/2)





void configure_clock();
void configure_uart();
void outs(void);
void configure_pwm(void);
void timer(void);

const eUSCI_UART_Config uartConfig =
{
 EUSCI_A_UART_CLOCKSOURCE_SMCLK,                // SMCLK Clock Source
 20,                                            // BRDIV = 78
 7,                                             // UCxBRF = 2
 214,                                           // UCxBRS = 0
 EUSCI_A_UART_NO_PARITY,                        // No Parity
 EUSCI_A_UART_LSB_FIRST,                        // LSB First
 EUSCI_A_UART_ONE_STOP_BIT,                     // One stop bit
 EUSCI_A_UART_MODE,                             // UART mode
 EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};
/*
const Timer_A_UpModeConfig upConfig_0 =     // Configure counter in Up mode
{
TIMER_A_CLOCKSOURCE_SMCLK,                  // Tie Timer A to SMCLK
TIMER_A_CLOCKSOURCE_DIVIDER_64,             // Increment counter every 64 clock cycles
3145728,//1.5*2^20/64                         // Period of Timer A (this value placed in TAxCCR0)
TIMER_A_TAIE_INTERRUPT_DISABLE,             // Disable Timer A rollover interrupt
TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,         // Enable Capture Compare interrupt
TIMER_A_DO_CLEAR                            // Clear counter upon initialization
};


void timer(void){
    Timer_A_configureUpMode(TIMER_A0_BASE,&upConfig_0);
    //Timer_A_configureUpMode(TIMER_A2_BASE,&upConfig_0);
    //start counter
    //Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
    //Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_UP_MODE);
    // Enable all interrupts
   // Interrupt_enableMaster();
}
*/


void configure_clock(){
    //set up clock
    unsigned int dcoFrequency = 3E+6;
    CS_setDCOFrequency(dcoFrequency);

    // Tie SMCLK to DCO
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
}



void configure_uart(){

        // Define GPIOs and UART TX/RX
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2 , GPIO_PRIMARY_MODULE_FUNCTION);
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

        /* Configuring UART Module */
        //uartConfig is in the header
        UART_initModule(EUSCI_A0_BASE,  &uartConfig);

        /* Enable UART module */
        UART_enableModule(EUSCI_A0_BASE);
}




void outs(){
    //GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN6);
    //GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN7);
    //GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN0);
    GPIO_setAsOutputPin(DIR0);
    GPIO_setAsOutputPin(DC_PIN_1);
    GPIO_setAsOutputPin(DC_PIN_2);

}





void configure_pwm() {
    //MAP_CS_setDCOFrequency(3E+6); // Set DCO clock source frequency
    //MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1); // Tie SMCLK to DCO
    P2SEL0 |= 0x10 ;  // Set bit 4 of P2SEL0 to enable TA0.1 functionality on P2.4
    P2SEL1 &= ~0x10 ; // Clear bit 4 of P2SEL1 to enable TA0.1 functionality on P2.4
    P2DIR |= 0x10 ; // Set pin 2.4 as an output pin

                                    // Set pin 2.4 as an output pin
    // Set Timer A period (PWM signal period)
    TA0CCR0 = 3000;  //not for stepper..
    // Set Duty cycle
    TA0CCR1 = 0; //not for stepper..
    // Set output mode to Reset/Set
    TA0CCTL1 = OUTMOD_7 ; // Macro which is equal to 0x00e0, defined in msp432p401r.h
    // Initialize Timer A
    TA0CTL = TASSEL__SMCLK | MC__UP | TACLR ;
    // PWM signal will now be available on P2.4







    /*

    //WDT_A_holdTimer();
    //CS_setDCOFrequency(3E+6); // Set DCO clock source frequency
    //CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1); // Tie SMCLK to DCO

    P2SEL0 |= 0x20 ;    // Set bit 4 of P2SEL0 to enable TA0.1 functionality on P2.4
    P2SEL1 &= ~0x20 ;   // Clear bit 4 of P2SEL1 to enable TA0.1 functionality on P2.4
    P2DIR |= 0x20 ;     // Set pin 2.4 as an output pin

    //P5SEL0 |= 0x40; // 5.6
    //P5SEL1 &= ~0x40;
    //P5DIR |= 0x40;


    // Set Timer A period (PWM signal period)
    TA0CCR0 = 3000;
    // Set Duty cycle
    TA0CCR1 = 500;
    // Set output mode to Reset/Set
    TA0CCTL1 = OUTMOD_7 ; // Macro which is equal to 0x00e0, defined in msp432p401r.h
    // Initialize Timer A
    TA0CTL = TASSEL__SMCLK | MC__UP | TACLR ;
    // PWM signal will now be available on P2.4


    //Configure Timer A2
    //TA2CCR0 = 3000;
    //TA2CCR1 = 1500;
    //TA2CCTL1 = OUTMOD_7 ;
    //TA2CTL = TASSEL__SMCLK | MC__UP | TACLR ;

     */

}
