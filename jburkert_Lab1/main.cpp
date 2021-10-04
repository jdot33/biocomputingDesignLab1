#include "mbed.h"
#include "binaryutils.hpp"
#include "USBSerial.h"

#define RED (uint32_t*)0x50000760 //pin 24
#define GREEN (uint32_t*)0x50000740 //pin 16
#define BLUE (uint32_t*)0x50000718 //pin 06
#define DIRSET (uint32_t*)0x50000514
#define OUTSET (uint32_t*)0x50000508
#define OUTCLR (uint32_t*)0x5000050C

uint32_t counter = 0;

typedef struct {
    uint32_t mills;
    uint32_t period;
    float CDC; //chocolate duty cycle variable 
    uint32_t count = 0;   /* A counter value               */
} message_t;

MemoryPool<message_t, 9> mpool;
Queue<message_t, 9> queue;

Ticker Flipper;
Semaphore qMessage(1);

PwmOut blue(LED4);

Thread thread1, thread2, thread3;

USBSerial serial;

void flip(){
    if(counter <= 333){
        setbit(OUTCLR, 16);
    }
    else{
        setbit(OUTSET, 16);
    }

    if(counter == 1000){
        counter = -1;
    }
    counter++;
}


void Vanilla()
{
    setbit(DIRSET, 16);
    Flipper.attach(&flip, 0.000001); // the address of the function to be attached (flip) and the interval (2 seconds)
    while(true){}
}

void Strawberry()
{
    while(true)
    {
        //serial.printf("strawberry loop entered...\r\n");
        //nrf_pwn_enable;
    }
}

void Chocolate()
{
    serial.printf("chocolate loop entered...\r\n");
    float cDuty;
    blue.period_us(1000);      // period in us
    while (true){
        qMessage.acquire();
        osEvent event = queue.get(0);
        if (event.status == osEventMessage) {
            message_t* dutycycle = (message_t*) event.value.p;
            cDuty = dutycycle->CDC;
            mpool.free(dutycycle);
        }
        serial.printf("dutycycle->CDC... %i \r\n", cDuty);
        // specify period first
        blue.write(cDuty);      // 50% duty cycle, relative to period
        //blue = 0.5f;          // shorthand for blue.write()
        //blue.pulsewidth(2);   // alternative to blue.write, set duty cycle time in seconds
        thread_sleep_for(10);
        qMessage.release();
    };
}

void Producer()
{
    int i = 0;
    float Chocpercent = 0;
    while(true)
    {
        if(Chocpercent >= 1){
            Chocpercent = 0;
        }
        serial.printf("Producer loop entered...\r\n");
        message_t *message = mpool.alloc();
        message->mills = 333;
        message->period = 1000;
        message->CDC = Chocpercent;
        message->count = i;
        serial.printf("Count... %i\r\n", message->count);
        i++;
        Chocpercent = Chocpercent + 0.1;
        queue.put(message);
        thread_sleep_for(100);
    }
}

// main() runs in its own thread in the OS
int main()
{
    //serial.printf("Threads start...\r\n");
    thread1.start(callback(Producer));
    //thread2.start(callback(Vanilla));
    thread3.start(callback(Chocolate));
    while(true){}
}

