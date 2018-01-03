#include "MicroBit.h"

MicroBit uBit;
static char _out[1024];
char* volatile out = _out;

void run0(int i) {
	static int p = 45;
	uBit.io.P13.setServoValue(p);
	uBit.io.P14.setServoValue(p);
	uBit.io.P15.setServoValue(p);
	uBit.io.P16.setServoValue(p);
	p = 180 - p;
}

void run1(int i) {
	int v = uBit.io.P2.getDigitalValue(PullUp);
	uBit.serial.printf("%d\n", v);
}

int main() {
    uBit.init();
    int _line = 0;
    for (int i = 0; ; i = (i + 1) % 4) {
    	if (i == 0) run1(i);
        if (out != _out) {
        	uBit.serial.printf("\n%d:\n", ++_line);
        	*out = 0;
        	uBit.serial.printf(_out);
        	out = _out;
        	uBit.serial.printf("\n");
        }
        uBit.sleep(125);
    }
}

