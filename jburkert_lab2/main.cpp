// cd documents/github/biocomputingdesignlab1/jburkert_lab2
//arduino-upload COM9 jburkert_lab2.bin
#include "mbed.h"
#include "binaryutils.hpp"
#include "USBSerial.h"

#define DIRSET (uint32_t*)0x50000514
#define OUTSET (uint32_t*)0x50000508
#define OUTCLR (uint32_t*)0x5000050C

#define humidity_flag (1UL << 0)
#define temp_flag (1UL << 9)

int change = 0;

USBSerial serial;
Ticker hat;
Thread humidity_thread, temperature_thread;
EventFlags event;

void hatf(){
    if(change == 1){
        event.set(temp_flag);
        change = 0;
    }
    else{
        event.set(humidity_flag);
        change = 1;
    }
}

void read_humidity(){
    while(true){
        if(event.wait_all(humidity_flag)){
            event.clear(humidity_flag);
            serial.printf("Reading Humidity... \r\n");
            serial.printf("change... %i\r\n", change);
            setbit(OUTCLR, 6); //pin 6 is the blue LED
            thread_sleep_for(1);
            setbit(OUTSET, 16); //turn off green
            thread_sleep_for(1000);
        }
    }
}

void read_temperature(){
    while(true){
        if(event.wait_all(temp_flag)){
            event.clear(temp_flag);
            serial.printf("Reading Temperature... \r\n");
            serial.printf("change... %i\r\n", change);
            setbit(OUTCLR, 16); //pin 16 is the Green LED
            thread_sleep_for(1);
            setbit(OUTSET, 6); //turn off blue
            thread_sleep_for(1000);
        }
        else{
        }
        thread_sleep_for(100);
    }
}
// main() runs in its own thread in the OS
int main()
{
    setbit(DIRSET, 16);
    setbit(DIRSET, 6);
    humidity_thread.start(read_humidity);
    temperature_thread.start(read_temperature);
    hat.attach(&hatf, 2s);
    while (true) {

    }
}

