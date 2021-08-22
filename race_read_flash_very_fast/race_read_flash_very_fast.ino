/**
 * @brief The following code implements the read flash procedure
 * by directly writing to the GPIO registers of the Atmel SAM3x8e MCU.
 * By using this method, we may achieve the fastest possible logic transition
 * of the gpio (42MHz). In this code, the toggling of the IO is approximately 21 MHz.
 *
 * @author Michael Vigdorchik, 2021
 * */


#include "Arduino.h"

// pin numbers on the DUE board vs GPIO port
// https://www.arduino.cc/en/Hacking/PinMappingSAM3X
#define TCK 7  // C.23 == 7
#define TMS 8  // C.22 == 8
#define TDI 9  // C.21 == 9
#define TDO 10  // C.29 == 10

// constant hardcoded pin masks
#define tck 0x1 << 23
#define tms 0x1 << 22
#define tdi 0x1 << 21
#define tdo 0x1 << 29

#ifndef MAX_DR_LEN
#define MAX_DR_LEN 256    // usually BSR
#endif
uint8_t dr_out[MAX_DR_LEN] = {0};

__asm__ __volatile__(
  ".macro NOPX P \n\t"
  ".rept &P \n\t"
  "NOP \n\t"
  ".endr \n\t"
  ".endm \n\t"
  );

char getCharacter(const char * message){
    char inChar[1] = {0};
    // first, clean the input buffer
	while (Serial.available())
		Serial.read();
	// notify user to input a value
	Serial.print(message);
    // wait for user input
	while (Serial.available() == 0)
    {	}
    Serial.readBytesUntil('\n', inChar, 1);
	return inChar[0];
}


void read_usercode(){
	
	/*	READ USERCODE	*/
	REG_PIOC_CODR = (tck | tms);    // rti
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tms;      // select dr scan
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;   // select ir scan
	REG_PIOC_CODR = (tck | tms);  
	
	REG_PIOC_SODR = tdi;   // capture ir	
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;   // shift ir
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;   // shift ir 0x7
	REG_PIOC_CODR = tck;  
	
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = (tck | tdi);  
	
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tms;   // exit ir 1
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = (tck | tms);   // update ir
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;   REG_PIOC_SODR = tms;  
	REG_PIOC_SODR = tck;   // rti

	REG_PIOC_CODR = (tck | tms);   // select dr scan
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;   // capture dr
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;   // shift dr 32 bits
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;   REG_PIOC_SODR = tms;    // exit 1 dr
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = (tck | tms);   // update dr
	REG_PIOC_SODR = tck;  
}


void reset_tap(){
	REG_PIOC_SODR = tms;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
}


void setup(){
	/* initialize mode for jtag pins */
	pinMode(TCK, OUTPUT);
	pinMode(TMS, OUTPUT);
	pinMode(TDI, OUTPUT);
	pinMode(TDO, INPUT_PULLUP);

	/* initial pins state */
	REG_PIOC_SODR = tck;      // digitalWrite(TCK, 1);
	REG_PIOC_SODR = tms;      // digitalWrite(TMS, 1);
	REG_PIOC_SODR = tdi;      // digitalWrite(TDI, 1);

	/* Initialize serial communication */
	Serial.begin(115200);
	while (!Serial) { ; }
	Serial.setTimeout(500); // set timeout for various serial R/W funcs
	Serial.println("Ready...");

	getCharacter("Press enter to start\n");
	Serial.print("Executing\n");
}


uint32_t arrayToInt(uint8_t * arr, int len){
  
  uint32_t integer = 0;
    uint32_t mask = 1;
  
  for (int i = 0; i < len; i++) {
    if (arr[i])
      integer |= mask;
    
    mask = mask << 1;
  }
  return integer;
}


void read_flash(){
	/*	REG_PIOC_SODR = tck    is x4 faster than 
		REG_PIOC_SODR |= tck
	*/
	/*	MAX10 TAP can withstand tck frequency of 20MHz at most ?? 
	I think its bullshit because the usb blaster works with 24MHz */
	
	// read_usercode();
	// reset_tap();
	uint8_t i=0;

	/*----------------------------------------------------------------------*/
	/* insert ir ISC_ENABLE 0x2cc
		this instruction must be invoked twice consequently, otherwise
		the flash read operation would not return the contents.
	*/
	REG_PIOC_CODR = (tck | tms);  
	REG_PIOC_SODR = tck;  
	REG_PIOC_SODR = tms;   REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = (tck | tms);  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = (tck | tdi);  
	REG_PIOC_SODR = tck; asm("nop");// tdi = '0' for 2 cycles
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;   REG_PIOC_SODR = tdi;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = (tck | tdi);  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;   REG_PIOC_SODR = tdi;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = (tck | tdi);  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;   REG_PIOC_SODR = (tdi | tms);  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = (tck | tms);  
	REG_PIOC_SODR = tck;  

	REG_PIOC_CODR = (tck | tms);  
	REG_PIOC_SODR = tck; 

	/* wait after ISC_ENABLE */
	/* minimal delay with 10MHz tck: 43 us */
	//delayMicroseconds(47);
  __asm__ __volatile__("NOPX 75"); 
  
	/* insert ir ISC_ADDRESS_SHIFT 0x203 */
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tck;  
	
	REG_PIOC_CODR = tck;  
	REG_PIOC_SODR = tms;   // select dr scan
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = (tck | tms);   // select ir scan

	REG_PIOC_SODR = tck;   // capture ir
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;   // shift ir
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;    // shift in 0x203
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = (tck | tdi);  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;   REG_PIOC_SODR = (tms | tdi);  
	
	REG_PIOC_SODR = tck;   // exit 1 ir
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;   // update ir
	REG_PIOC_CODR = (tck | tms);  

	REG_PIOC_SODR = tck;   // rti
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;   REG_PIOC_SODR = tms;  

	REG_PIOC_SODR = tck;   // select dr scan
	REG_PIOC_CODR = (tck | tms);  

	REG_PIOC_SODR = tck;   // capture dr
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;   // shift dr
	REG_PIOC_CODR = (tck | tdi);  

	REG_PIOC_SODR = tck;   // shift address 0x1700 23 bits
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;   //REG_PIOC_SODR = tdi;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = (tck | tdi);  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;   //REG_PIOC_SODR = tdi;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;   REG_PIOC_SODR = tdi;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;   REG_PIOC_CODR = tdi;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;   REG_PIOC_SODR = tms;  

	REG_PIOC_SODR = tck;   // exit 1 dr
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;   // update dr
	REG_PIOC_CODR = (tck | tms);  

	REG_PIOC_SODR = tck;   // rti
	REG_PIOC_CODR = tck;  



	/*	insert ir ISC_READ 0x205	*/
	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;   REG_PIOC_SODR = tms;  

	REG_PIOC_SODR = tck;   // select dr scan
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;   // select ir scan
	REG_PIOC_CODR = (tck | tms);  

	REG_PIOC_SODR = tck;   // capture ir
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;   // shift ir
	REG_PIOC_CODR = tck;   REG_PIOC_SODR = tdi;  

	REG_PIOC_SODR = tck;   // shift 0x205
	REG_PIOC_CODR = (tck | tdi);  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;   REG_PIOC_SODR = tdi;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = (tck | tdi);  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  
	REG_PIOC_CODR = tck;   REG_PIOC_SODR = (tms | tdi);  

	REG_PIOC_SODR = tck;   
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;   // exit 1 ir
	REG_PIOC_CODR = (tck | tms);  

	REG_PIOC_SODR = tck;   // update ir
	REG_PIOC_CODR = tck;  



	/*	shift out flash content  */
	
	REG_PIOC_SODR = tck;   // rti
	REG_PIOC_CODR = tck;   REG_PIOC_SODR = tms;  

	REG_PIOC_SODR = tck;   // select dr scan 
	REG_PIOC_CODR = (tck | tms);  

	REG_PIOC_SODR = tck;   // capture dr
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;   // shift dr
	REG_PIOC_CODR = (tck | tdi);   // shift 0x00000000 32 bits

	REG_PIOC_SODR = tck;  dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;  dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++; 
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;   

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29)); i++;
	REG_PIOC_CODR = tck;   REG_PIOC_SODR = tms;  

	REG_PIOC_SODR = tck; dr_out[i] = !!(PIOC->PIO_PDSR & (1<<29));  
	REG_PIOC_CODR = tck;  

	REG_PIOC_SODR = tck;   // update dr 
	REG_PIOC_CODR = (tck | tms);  

	REG_PIOC_SODR = tck;    // rti	
  
  Serial.print(" 0x"); Serial.print(arrayToInt(dr_out, 32), HEX);
  Serial.flush();  
}


void loop(){
	read_flash();
	while(1);
}
