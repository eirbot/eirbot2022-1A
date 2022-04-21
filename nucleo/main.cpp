#include <mbed.h>
#include "couleur.hpp"
#include "odometrie.hpp"
#include "couleur.hpp"

DigitalOut led_A(LED1);
 
int main() {
 
 // put your setup code here, to run once:
 
 while(1) {
   printf(“Hello\n”);
   led_A.write(1);
   ThisThread::sleep_for(200);
   led_A.write(0);
   ThisThread::sleep_for(200);
 }
}
