/**
 * Author: Laurenz Kamp
 * Created: 10.09.2015
 */

#ifndef IO_H_
#define IO_H_

void initIO(void);

void seg_show(int value);

void wait(long d);

int getADCValue(int channel);
void initADC(void);


#endif /* IO_H_ */
