main.c
#include "header.h"

//NEW
//#define LED1 GPIO_PORT_P1,GPIO_PIN0


/*
//Configure Clock
const Timer_A_UpModeConfig upConfig_0 = // Configure counter in Up mode
{
    TIMER_A_CLOCKSOURCE_SMCLK, // Tie Timer A to SMCLK
    TIMER_A_CLOCKSOURCE_DIVIDER_64, // Increment counter every 1 clock cycles
    46875, // Period of Timer A (this value placed in TAxCCR0)(46875)
    TIMER_A_TAIE_INTERRUPT_DISABLE, // Disable Timer A rollover interrupt
    TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE, // Enable Capture Compare interrupt
    TIMER_A_DO_CLEAR // Clear counter upon initialization
};
*/


//int dir = 0;
//volatile int counter = 0;
//NEW END


  void main(void) {
    WDT_A_holdTimer();      // stop watchdog timer

    configure_clock();
    //timer();
    outs();
    configure_pwm();
    configure_uart();

    //NEW
    //DIR pin
    //MAP_GPIO_setAsOutputPin(DIR0);
    //MAP_GPIO_setOutputHighOnPin(DIR0);


    /* Configuring GPIO5.6 as peripheral outputs for PWM */
    /*
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);

        P5SEL0 |= 0x40;
        P5SEL1 &= ~0x40;//Configure 5.6

        P5DIR |= 0x40; //Set 5.6 as output pin
        // Set Timer A period (PWM signal period)
        // Set output mode to Reset/Set

        //Configure Timer A2 in 5.6
        TA2CCR0 = 3000;
        TA2CCR1 = 0;
        TA2CCTL1 = OUTMOD_7 ;
        TA2CTL = TASSEL__SMCLK | MC__UP | TACLR ;



        //Timer configuration
        Timer_A_configureUpMode(TIMER_A1_BASE,&upConfig_0); // Configure Timer A using above struct
        Interrupt_enableInterrupt(INT_TA1_0); // Enable Timer A interrupt

        Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE); // Start Timer A
        Interrupt_enableMaster();


        TA2CCR1 = .1 *3000;
        MAP_GPIO_setOutputHighOnPin(DIR0);
        */

    //NEW END



    FPU_enableModule();
    // Enable all interrupts
    Interrupt_enableMaster();

    //PERIOD = 10000;
    //DUTY = .5*PERIOD;
    //while (1) {
    //;
    //}




/*
    double test[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    for (i = 0; i < sizeof(test); i++) {


        int dir = i%2;
        if (dir) {
            GPIO_setOutputLowOnPin(DC_PIN_1);
            GPIO_setOutputHighOnPin(DC_PIN_2);
            int dum = 0;
        } else {
            GPIO_setOutputLowOnPin(DC_PIN_2);
            GPIO_setOutputHighOnPin(DC_PIN_1);
            int dumbo = 0;
        }
    }
    */






    //ON_OFF = ON;

    /*
    double test[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    for (i = 0; i < sizeof(test); i++) {
        double mult = test[9-i]/10;

        //TA0CCR1 = (int) (5000*mult);
        SPEED = 3000*mult;
        ON_OFF = SPEED/2;

        int dir = i%2;
        if (dir) {
            //GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN0);
            //GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN7);
            GPIO_setOutputHighOnPin(DIR0);
        } else {
            //GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN0);
            //GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN7);
            GPIO_setOutputLowOnPin(DIR0);
        }
    }
    */



    unsigned char x_error[3];
    float x_err;
    float x_err_last = 0;
    unsigned long integral = 0;


    //GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN0);
    //GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN7);
    //TA0CCR1 = (int) 3000*1;
/*
    SPEED = 3000*.5;
    ON_OFF = SPEED/2;
    while(1)
    {

    }
    */



    while (1) {

        int i = 0;
        while (i < 3) {
            _delay_cycles(10000);
            unsigned char read = UART_receiveData(EUSCI_A0_BASE);
            if (read != '\x0a') {
                x_error[i] = read;
                i++;
            }
        }

        int Kp_x = 1600;
        int Kd_x = 700;
        int Ki_x = 00;

        //Kp = 1600
        //Kd = 300;

        x_err = ((x_error[1] - '0')*.1 + (x_error[2] - '0')*.01);
        if (x_error[0] == '0') {
            x_err *= -1;
        }

        integral += x_err;
        if ((x_err < .1) || (x_err > -.1)) {
            integral *= 0;
        }


        PERIOD = OFFSET + Kp_x*x_err + Kd_x*(x_err - x_err_last) + Ki_x*(integral);

        DUTY = .5*PERIOD;
        x_err_last = x_err;


        /*//Working stepper
        //direction
        if (x_error[0] == '1') {
            GPIO_setOutputHighOnPin(DIR0);
        } else {
            GPIO_setOutputLowOnPin(DIR0);
        }

        //speed
        x_err = ((x_error[1] - '0')*.1 + (x_error[2] - '0')*.01);

        double Kp = 10; //smaller means faster
        SPEED = 3000*(.5 - x_err) * Kp;
        ON_OFF = SPEED/2;

        if (x_err <= .05) {
            ON_OFF = 0;
        }
        */




        /*
        //x_err = ((float)((int) x_err*100))/100;
        //TA0CCR1 = 3000*x_err;

        if (x_error[1] > 2) {
            TA0CCR1 = 3000*.1;
        } else {
            TA0CCR1 = 0;
        }

        if (x_error[0] == '1') {
            GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN0);
            GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN7);
        } else {
            GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN7);
            GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN0);
        }
        */
    }
}


