#include "mbed.h"
#include "binaryutils.hpp"
#include "USBSerial.h"

#define PIN0 (uint32_t*)0x50000000
#define DIRSET (uint32_t*)0x50000514
#define OUTSET (uint32_t*)0x50000508
#define OUTCLR (uint32_t*)0x5000050C


typedef enum {
    NO_ERROR,
    ATTN_REQ,
    FATAL_ERROR,
} State;


Mail<State, 9> mail_box;

Thread thread;

USBSerial serial;

// State* cyclestate(State* p){
//     if(*p == NO_ERROR)
//     {
//         *p = ATTN_REQ;
//     }
//     else if(*p == ATTN_REQ)
//     {
//         *p = FATAL_ERROR;
//     }
//     else if(*p == FATAL_ERROR)
//     {
//         *p = NO_ERROR;
//     }
//     return *p;
// }

void led_diag_handler()
{
    setbit(DIRSET, 13);
    uint32_t t1 = 5000;

    while(true)
    {
        serial.printf("handler loop entered...\r\n");
        osEvent event = mail_box.get(0);
        serial.printf("mail got...\r\n");
        State* priority = (State*) event.value.p;
        serial.printf("mail is... %i\r\n", priority);
        if(*priority == NO_ERROR)
        {
            serial.printf("NO_ERROR\r\n");
            t1 = 2000;
            mail_box.free(priority);
        }
        if(*priority == ATTN_REQ)
        {
            serial.printf("ATTN_REQ\r\n");
           t1 = 1000;
           mail_box.free(priority);
        }
        if(*priority == FATAL_ERROR)
        {
            serial.printf("FATAL_ERROR\r\n");
            t1 = 500;
            mail_box.free(priority);
        }

        setbit(OUTSET, 13);
        thread_sleep_for(t1);
        setbit(OUTCLR, 13);
        thread_sleep_for(t1);
    }
}

void diag_tester()
{
    int count = 0;
    while(true)
    {
    serial.printf("tester loop entered...\r\n");
    serial.printf("count is... %i\r\n", count);
    State* priority = mail_box.try_alloc();
        if(count == 0){
            *priority = NO_ERROR;
            serial.printf("set prriority to NO_ERROR...\r\n");
        }
        if(count == 1){
            *priority = ATTN_REQ;
            serial.printf("set prriority to ATTN_REQ...\r\n");
        }
        if(count == 2){
            *priority = FATAL_ERROR;
            serial.printf("set prriority to FATAL_ERROR...\r\n");
            count = -1;
        }
    count++;
    serial.printf("mail put...\r\n");
    mail_box.put(priority);
    serial.printf("tester sleep (5000)...\r\n");
    thread_sleep_for(5000);
    //mail_box.put(priority);
    //switch priority
    }
}

// main() runs in its own thread in the OS
int main()
{
    serial.printf("Threads start...\r\n");
    thread.start(callback(diag_tester));
    thread.start(callback(led_diag_handler));
    /*
        setbit(DIRSET, 13);
    while (true) {
        //blink
        //uint32_t* LED = blinker + 0x508;
        //for(int i=0; i<50000; i++){
        //    clearbit(blinker, 13);
        //}
        setbit(OUTSET, 13);
        thread_sleep_for(500);
        setbit(OUTCLR, 13);
        thread_sleep_for(500);
    }
    */
}

