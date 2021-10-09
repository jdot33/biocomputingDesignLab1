// cd documents/github/biocomputingdesignlab1/jburkert_Lab1
//arduino-upload COM9 jburkert_Lab1.bin

#include "mbed.h"
#include "binaryutils.hpp"
#include "USBSerial.h"

#define RED (uint32_t*)0x50000760 //pin 24
#define GREEN (uint32_t*)0x50000740 //pin 16
#define BLUE (uint32_t*)0x50000718 //pin 06
#define DIRSET (uint32_t*)0x50000514
#define OUTSET (uint32_t*)0x50000508
#define OUTCLR (uint32_t*)0x5000050C

uint32_t pass = 0;
int VDC = 333;

typedef struct {
    uint32_t mills;
    uint32_t period;
    int VanillaState; //Vanilla duty cycle
    int CDC; //chocolate duty cycle variable 
} message_t;

MemoryPool<message_t, 18> Vmpool;
Queue<message_t, 9> Vqueue;
Queue<message_t, 9> Cqueue;
Queue<message_t, 9> Squeue;

Ticker Flipper;
Semaphore qMessage(1);

PwmOut blue(LED4);

Thread thread1, thread2, thread3;

USBSerial serial;

void flip(){
    if(pass <= VDC){
        setbit(OUTCLR, 16);
    }
    else{
        setbit(OUTSET, 16);
    }

    if(pass == 1000){
        pass = -1;
    }
    pass++;
}


void Vanilla()
{
    setbit(DIRSET, 16);
    Flipper.attach(&flip, 30us); // the address of the function to be attached (flip) and the interval (2 seconds)
    while(true){
        osEvent event = Vqueue.get(0);
        if (event.status == osEventMessage) {
            message_t* Vstate = (message_t*) event.value.p;
            if(Vstate->VanillaState == 1){
                VDC = 1000;
            }
            else if(Vstate->VanillaState == 2){
                VDC = 900;
            }
            else if(Vstate->VanillaState == 3){
                VDC = 800;
            }
            else if(Vstate->VanillaState == 4){
                VDC = 700;
            }
            else if(Vstate->VanillaState == 5){
                VDC = 600;
            }
            else if(Vstate->VanillaState == 6){
                VDC = 500;
            }
            else if(Vstate->VanillaState == 7){
                VDC = 400;
            }
            else if(Vstate->VanillaState == 8){
                VDC = 300;
            }
            else if(Vstate->VanillaState == 9){
                VDC = 200;
            }
            else if(Vstate->VanillaState == 10){
                VDC = 0;
            }
            Vmpool.free(Vstate);
            
        }
        thread_sleep_for(10);
    }
}

void Strawberry()
{
    while(true)
    {
        serial.printf("strawberry loop entered...\r\n");

        //nrf_pwn_enable;
    }
}

void Chocolate()
{
    float cDuty;
    blue.period_us(500);      // period in us
    while (true){
        qMessage.acquire();
        osEvent event = Cqueue.get(0);
        if (event.status == osEventMessage) {
            message_t* dutycycle = (message_t*) event.value.p;
            if(dutycycle->CDC == 1){
                cDuty = 0.8;
            }
            else if(dutycycle->CDC == 2){
                cDuty = 0.6;
            }
            else if(dutycycle->CDC == 3){
                cDuty = 0.4;
            }
            else if(dutycycle->CDC == 4){
                cDuty = 0.2;
            }
            else if(dutycycle->CDC == 5){
                cDuty = 0;
            }
            else if(dutycycle->CDC == 6){
                cDuty = 0.2;
            }
            else if(dutycycle->CDC == 7){
                cDuty = 0.4;
            }
            else if(dutycycle->CDC == 8){
                cDuty = 0.6;
            }
            else if(dutycycle->CDC == 9){
                cDuty = 0.8;
            }
            else if(dutycycle->CDC == 10){
                cDuty = 1.0;
            }
            Vmpool.free(dutycycle);
        }
        // specify period first
        blue.write(cDuty);      // 50% duty cycle, relative to period
        //blue = 0.5f;          // shorthand for blue.write()
        //blue.pulsewidth(2);   // alternative to blue.write, set duty cycle time in seconds
        thread_sleep_for(10);
        qMessage.release();
    }
}

void Producer()
{
    int i = 0;
    int ChocFlag = 0;
    int ChocState = 0;
    while(true)
    {
        if(ChocState == 0){
            ChocFlag = 0;
        }
        if(ChocState >= 10){
            ChocFlag = 1;
        }
        switch(ChocFlag){
            case 0:
                    ChocState++;
                    break;
            case 1:
                    ChocState--;
                    break;
            default:
                    ChocState++;
                    break;
        }
        if(i >= 100){
            i = 0;
        }
        serial.printf("Producer loop entered...\r\n");
        message_t *message = Vmpool.alloc();
        //message_t *message = Cmpool.alloc();
        //message_t *message = Smpool.alloc();
        message->CDC = ChocState;
        message->VanillaState = ChocState;
        serial.printf("Count... %i\r\n", i);
        i++;
        Vqueue.put(message);
        Cqueue.put(message);
        //Squeue.put(message);
        thread_sleep_for(100);
    }
}

// main() runs in its own thread in the OS
int main()
{
    //serial.printf("Threads start...\r\n");
    thread1.start(callback(Producer));
    thread2.start(callback(Vanilla));
    thread3.start(callback(Chocolate));
    while(true){}
}

