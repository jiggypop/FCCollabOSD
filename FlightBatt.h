/**
 ******************************************************************************
 *
 * @file       FlightBatt.h
 * @author     Joerg-D. Rothfuchs
 * @brief      Implements voltage and current measurement of the flight battery
 * 	       on the Ardupilot Mega MinimOSD using built-in ADC reference.
 * @see        The GNU Public License (GPL) Version 3
 *
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/> or write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */


// !!! For using this, you have to solder a little bit on the MinimOSD, see the wiki !!!


#ifndef FLIGHT_BATT_H_
#define FLIGHT_BATT_H_


#define VOLTAGE_PIN			2                       // Batt1/VidVoltage=2, Batt2/Voltage=0 on minimOSD w/ KV mod
#define CURRENT_PIN			1                       // KV team mode board

#define REF_VOLTAGE			1.1			// INTERNAL: a built-in reference, equal to 1.1 volts on the ATmega168 or ATmega328
#define LOW_VOLTAGE			9.6			// filter start value for 3s LiPo


// #define VOLT_DIV_RATIO			15.55			// Vref 1.1V based: This is the start value for calibrating a 16k0/1k1 voltage divider usable up to 4s LiPo
// #define VOLT_DIV_RATIO			16.16			// Witespy OSD 16.0 = 12.16v of 12.28, 16.5 = 12.53v of 12.27
#define VOLT_DIV_RATIO			15.98                   // 16.16 = 12.38 of 12.25

// !!! for the +-50A Current Sensor(AC/DC) DFRobot SEN0098 we need approx. a 1/4 voltage divider 3k0/1k1 so that we stay below 1.1 V -> 2*50A * 0.04V/A / (4.1/1.1) = 1.073 V !!!
// For Pololu ACS715 0 -> 30A sensor.  Need .25 voltage divider. 100k/33k to stay below 1.1V -> (30A * .133V/A + .5V) / (100k/33k) = 1.114.
// #define CURR_AMP_PER_VOLT		100.00			// Vref 1.1V based: This is the start value for calibrating a +-50A Current Sensor(AC/DC) DFRobot SEN0098 Sensitivity: 40 mV/A
#define CURR_AMP_PER_VOLT		30.30                   // (133mV/A*.25 voltage divider) = 30.303 A/V
// #define CURR_AMPS_OFFSET		0.0000			// Vref 1.1V based: This is the start value for calibrating a +-50A Current Sensor(AC/DC) DFRobot SEN0098 Sensitivity: 40 mV/A
#define CURR_AMPS_OFFSET		0.1241                  // Current sensor output @ 0A = 500mV.  So 500mv * .25 voltage divider = .12406

#define CURRENT_VOLTAGE(x)		(double(x)*REF_VOLTAGE/1024.0)*(volt_div_ratio/100.0)
// #define CURRENT_VOLTAGE(x)		(double(x)*REF_VOLTAGE/1024.0)*(VOLT_DIV_RATIO)
// #define CURRENT_AMPS(x)			((double(x)*REF_VOLTAGE/1024.0)-(curr_amp_offset/10000.0))*(curr_amp_per_volt/100.0)
#define CURRENT_AMPS(x)			((double(x)*REF_VOLTAGE/1024.0)-(CURR_AMPS_OFFSET))*(CURR_AMP_PER_VOLT)


void flight_batt_init(void);
void flight_batt_read(void);

#endif /* FLIGHT_BATT_H_ */
