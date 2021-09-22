#include "mbed.h"
#include "binaryutils.hpp"
#include "USBSerial.h"

#define RED (uint32_t*)0x50000760 //pin 24
#define GREEN (uint32_t*)0x50000740 //pin 16
#define BLUE (uint32_t*)0x50000718 //pin 06
#define DIRSET (uint32_t*)0x50000514
#define OUTSET (uint32_t*)0x50000508
#define OUTCLR (uint32_t*)0x5000050C

typedef struct {
    uint32_t mills;
    uint32_t count = 0;   /* A counter value               */
} message_t;

Queue<message_t, 9> queue;
MemoryPool<message_t, 9> mpool;
Ticker flipper;

Thread thread1;
Thread thread2;

USBSerial serial;

void off(){
    setbit(OUTCLR, 16);
}

void Vanilla()
{
    flipper.attach(&off, 0.0003); // the address of the function to be attached (flip) and the interval (2 seconds)
    while(true)
    {
        serial.printf("Vanilla loop entered...\r\n");
        osEvent evt = queue.get();
        if(evt.status == osEventMessage){
            serial.printf("status is message...\r\n");
            message_t *message = (message_t*) osEventMessage;
            setbit(OUTSET, 16);
            mpool.free(message);
        }
        thread_sleep_for(1);
    }
}

void Strawberry()
{
    while(true)
    {
        serial.printf("strawberry loop entered...\r\n");
    }
}

void Producer()
{
    uint32_t i = 0;
    while(true)
    {
        serial.printf("Producer loop entered...\r\n");
        message_t *message = mpool.alloc();
        message->mills = 3;
        message->count = i;
        serial.printf("Count... %i\r\n", message->count);
        i++;
        queue.put(message);
        thread_sleep_for(1000);
    }
}

// main() runs in its own thread in the OS
int main()
{
    setbit(DIRSET, 16);
    serial.printf("Threads start...\r\n");
    thread1.start(callback(Producer));
    thread2.start(callback(Vanilla));
}

