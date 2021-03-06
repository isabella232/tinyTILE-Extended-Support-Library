// Copyright (c) 2016 Intel Corporation.  All rights reserved.
// See the bottom of this file for the license terms.

/*
 *  This sketch is to demonstrate I2C reading as a I2C device, slave mode.  The sketch generates a data pattern upon
 *  each read request and send it to the master.  Notice that all the processing are done in an event handler -
 *  routine that is called, by the I2C library, upon the detection of an event (eg. bus master wants to read).
 *
 *  Please note:
 *    1. This sketch makes use of I2C0.  One of the two I2C connections from the Quark core.  Only the Quark I2C
 *       interface has the slave mode capability.  For the ARC core I2C connection, please refer to the Wire library.
 *    2. This sketch can easily be changed to make use of I2C1 - just change to the I2C1 object instead of I2C0.
 *    3. The Quark I2C connections are not available in the Arduino 101 hardware platform.
 *    4. The sketch set the board to have a device number (address) of 8.  This address can be changed to fit your setup.
 */


#include <quarkI2C.h>

void setup() {
    Serial.begin(9600);           // start serial for output
    while(!Serial);               // Wait here till serial terminal is ready/opened

    I2C0.begin(0x8);                           // join i2c bus with address #8
    I2C0.onRequest(masterReadFromMeHandler);               // register event
}
void loop() {

    delay(2000);
}

static int count = 0;
static uint8_t buffer[32];

// When I2C library detects a write request from the Master,
// this function is called.  It first generates a data pattern.
// Then send it to the master via a write() call.  In the point
// of view of a slave, it is writing to the master.
void masterReadFromMeHandler() {
    int i;
    count++;
    Serial.print("call masterReadFromMeHandler ");
    Serial.print(count);
    Serial.println(" times");

    // Putting the lap count at the upper nibble of a byte.
    for (i = 0; i < sizeof(buffer); i++) {
        buffer[i] = ((count & 0xf) << 4) | i;
    }
    I2C0.write(buffer, sizeof(buffer));
}


/*
   Copyright (c) 2016 Intel Corporation.  All rights reserved.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

