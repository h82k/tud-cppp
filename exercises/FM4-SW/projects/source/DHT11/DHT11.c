#include "DHT11.h"

/**
 * Reading the dataline of the DHT11 for temperature and humidity
 */
uint8_t readDHT11(uint8_t *feuchtigkeit, uint8_t *temperatur) 
{
  Gpio1pin_Put(GPIO1PIN_PF7, 1);
  microDelay(250);
	if (Gpio1pin_Get(GPIO1PIN_PF7) == 0) {return 1;}									// Bus not free
	          // MCU start signal (>=18MS
  

  Gpio1pin_InitOut(GPIO1PIN_PF7, Gpio1pin_InitVal(0u));
	microDelay(20000);

  Gpio1pin_InitIn(GPIO1PIN_PF7, Gpio1pin_InitPullup(1u));
	uint16_t timeout = 1000;
	while(Gpio1pin_Get(GPIO1PIN_PF7) == 1) {if (!timeout--) {return 2;}}				// Wait for DHTís response (20-40us)
	timeout = 1000; 
	while(Gpio1pin_Get(GPIO1PIN_PF7) == 0) {if (!timeout--) {return 3;}}				// Response signal (80us)
	timeout = 1000;	
	while(Gpio1pin_Get(GPIO1PIN_PF7) == 1) {if (!timeout--) {return 4;}}				// Preparation for sending data (80us)
  timeout = 1000;  
  while(Gpio1pin_Get(GPIO1PIN_PF7) == 0) {if (!timeout--) {return 8;}}        
  timeout = 1000;  
  while(Gpio1pin_Get(GPIO1PIN_PF7) == 1) {if (!timeout--) {return 9;}}  
	uint8_t dht11_data[5]={0};
  uint8_t i,j = 0;
	for(i=0;i<5;i++)
	{
		uint8_t dht11byte = 0;
		for(j=1;j<=8;j++)
		{
			timeout = 1000;
			while(Gpio1pin_Get(GPIO1PIN_PF7) == 0) {if (!timeout--) {return 5;}}		// Start to transmit 1-Bit (50 us)
			microDelay(30);
			dht11byte <<= 1;
			if (Gpio1pin_Get(GPIO1PIN_PF7) == 1)										// Hi > 30us (70 us) -> Bit=1										
			{
				dht11byte |= 1;
				timeout = 1000;
				while(Gpio1pin_Get(GPIO1PIN_PF7) == 1) {if (!timeout--) {return 6;}}
			}														// Hi <  30us (26-28 us) -> Bit=0	
		}
		dht11_data[i] = dht11byte;
	}
  
	//if (dht11_data[0]+dht11_data[1]+dht11_data[2]+dht11_data[3] != dht11_data[4]) 	// Checksum
  if( !(data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) )
	{
		return 7;													
	}	
  
	*feuchtigkeit = dht11_data[0];
	*temperatur = dht11_data[2];
	return 0;
} 


void rauminformationen(){
      setCursor(480,320);
      char freeSpace[] = " ";
      char headlineText[] = "      Umgebungssensoren";
      writeTextln(freeSpace);
      writeTextln(freeSpace);
      writeTextln(freeSpace);
      writeTextln(headlineText);
      writeTextln(freeSpace);
      
      uint8_t feuchtigkeit, temperatur  = 0;
      uint8_t result = readDHT11(&feuchtigkeit, &temperatur);
      
      char helligkeitText[] = "      Helligkeit (%) : ";
      writeText(helligkeitText);
      uint8_t helligkeit = map(analog17, 0, 255, 0, 100);
      write3Digits8Bit(&helligkeit);
      
      char temperaturText[] = "      Temperatur (Celsius) : ";
      writeText(temperaturText);
      write3Digits8Bit(&temperatur);
      
      char feuchtigkeitText[] = "      Feuchtigkeit (%) : ";
      writeText(feuchtigkeitText);
      write3Digits8Bit(&feuchtigkeit); 
      
      microDelay(50000);
}