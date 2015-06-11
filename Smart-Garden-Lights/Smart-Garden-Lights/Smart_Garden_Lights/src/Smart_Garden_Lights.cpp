// Smart Garden Lights By Xenon Photon - m_o_t_e_2005@yahoo.com
// 11 jun 2015

// The base arm_pro_mini_lib include.
#include "arm_pro_mini.h"
// Provides abstraction to digital I/o pins.
#include "io_pins.h"

// Provide system time using TIMER32 0.
#include "system_time.h"

// Provides interrupt free elapsed time measurement using system time.
#include "passive_timer.h"

// Provides serial I/O over USB/CDC.
#include "usb_serial.h"

// Allows to jump to ISP mode when ISP button is pressed.
#include "isp_button_monitor.h"

#include "math.h"
#include <stdarg.h>
#include <stdio.h>
#include "chip/clock_11xx.h"
#include <chip.h>
#define Minute_Timer (LPC_TIMER32_1)
#define Minute_TimerIRQn (TIMER_32_1_IRQn)

const uint32 system_clock_hz = Chip_Clock_GetSystemClockRate();
const uint32 prescale = system_clock_hz / 1000000;
const double PI = 3.14159265358979323846264338327950288419716939937510;

static int scanf_m = 0;
static float Latitude, Longitude, T_Zone;
static double Date = 0, Julian_Day, Julian_Century, Geom_Mean_Long_Sun,
		Geom_Mean_Anom_Sun, Eccent_Earth_Orbit, Sun_Eq_of_Ctr, Sun_True_Long,
		Sun_App_Long, Mean_Obliq_Ecliptic, Obliq_Corr, Sun_Declin, var_y,
		Eq_of_Time, HA_Sunris, Solar_Noon, Sunrise_Time, Sunset_Time, dumpZ;
static int Sunrise_TimeHH, Sunrise_TimeMM, Sunset_TimeHH, Sunset_TimeMM;
static int Year, Month, Day, Hour = 0, Minute = 0;
static char dummy = 0;
static bool SyS_Ready = false;

double RADIANS(double deg)
{
	return deg * PI / 180;
}

double DEGREES(double rad)
{
	return rad * 180 / PI;
}

// Red LED is at GPIO0_20.
static io_pins::OutputPin led(0, 20);

int scanf3(const char* format, ...)
{
	int n = 0;
	while (n == 0)
	{
		isp_button_monitor::loop();
		static char buf[1];
		static char buf2[127];
		buf[0] = 0;
		buf[1] = 0;
		if (usb_serial::Read_Serial((unsigned char*) buf) != 0)
		{
			printf("%s", buf);
			if ((buf[0] == 13 || buf[0] == 10) && scanf_m > 0)
			{
				buf2[scanf_m] = 0;
				va_list ap;
				va_start(ap, format);
				n = vsscanf(buf2, format, ap);
				va_end(ap);
				scanf_m = 0;
				printf("\r\n");

			}
			else
			{
				buf2[scanf_m] = buf[0];
				scanf_m++;
			}
		}
	}
	return n;
}
/*
 * The sunrise equation as follows can be used to derive the time of
 * sunrise and sunset for any solar declination and latitude in terms of
 * local solar time when sunrise and sunset actually occur
 *
 * Reference:
 * http://en.wikipedia.org/wiki/Sunrise_equation
 */
void Do_the_Math()
{
	Date = int((1461 * (Year + 4800 + int((Month - 14) / 12))) / 4)
			+ int((367 * (Month - 2 - 12 * ((Month - 14) / 12))) / 12)
			- int((3 * (int((Year + 4900 + int((Month - 14) / 12)) / 100))) / 4)
			+ Day - 2415019 - 32075;

	Julian_Day = Date + 2415018.5 - T_Zone / 24;
	Julian_Century = (Julian_Day - 2451545) / 36525;
	Geom_Mean_Long_Sun = fmod(
			280.46646
					+ Julian_Century
							* (36000.76983 + Julian_Century * 0.0003032), 360);
	Geom_Mean_Anom_Sun = 357.52911
			+ Julian_Century * (35999.05029 - 0.0001537 * Julian_Century);
	Eccent_Earth_Orbit = 0.016708634
			- Julian_Century * (0.000042037 + 0.0000001267 * Julian_Century);
	Sun_Eq_of_Ctr = sin(RADIANS(Geom_Mean_Anom_Sun))
			* (1.914602
					- Julian_Century * (0.004817 + 0.000014 * Julian_Century))
			+ sin(RADIANS(2 * Geom_Mean_Anom_Sun))
					* (0.019993 - 0.000101 * Julian_Century)
			+ sin(RADIANS(3 * Geom_Mean_Anom_Sun)) * 0.000289;
	Sun_True_Long = Geom_Mean_Long_Sun + Sun_Eq_of_Ctr;
	Sun_App_Long = Sun_True_Long - 0.00569
			- 0.00478 * sin(RADIANS(125.04 - 1934.136 * Julian_Century));
	Mean_Obliq_Ecliptic =
			23
					+ (26
							+ ((21.448
									- Julian_Century
											* (46.815
													+ Julian_Century
															* (0.00059
																	- Julian_Century
																			* 0.001813))))
									/ 60) / 60;
	Obliq_Corr = Mean_Obliq_Ecliptic
			+ 0.00256 * cos(RADIANS(125.04 - 1934.136 * Julian_Century));
	Sun_Declin = DEGREES(
			asin(sin(RADIANS(Obliq_Corr)) * sin(RADIANS(Sun_App_Long))));
	var_y = tan(RADIANS(Obliq_Corr / 2)) * tan(RADIANS(Obliq_Corr / 2));
	Eq_of_Time = 4
			* DEGREES(
					var_y * sin(2 * RADIANS(Geom_Mean_Long_Sun))
							- 2 * Eccent_Earth_Orbit
									* sin(RADIANS(Geom_Mean_Anom_Sun))
							+ 4 * Eccent_Earth_Orbit * var_y
									* sin(RADIANS(Geom_Mean_Anom_Sun))
									* cos(2 * RADIANS(Geom_Mean_Long_Sun))
							- 0.5 * var_y * var_y
									* sin(4 * RADIANS(Geom_Mean_Long_Sun))
							- 1.25 * Eccent_Earth_Orbit * Eccent_Earth_Orbit
									* sin(2 * RADIANS(Geom_Mean_Anom_Sun)));
	HA_Sunris =
			DEGREES(
					acos(
							cos(RADIANS(90.833))
									/ (cos(RADIANS(Latitude))
											* cos(RADIANS(Sun_Declin)))
									- tan(RADIANS(Latitude))
											* tan(RADIANS(Sun_Declin))));
	Solar_Noon = (720 - 4 * Longitude - Eq_of_Time + T_Zone * 60) / 1440;
	Sunrise_Time = Solar_Noon - HA_Sunris * 4 / 1440;
	Sunset_Time = Solar_Noon + HA_Sunris * 4 / 1440;
	Sunrise_TimeHH = Sunrise_Time * 24;
	Sunrise_TimeMM = modf(Sunrise_Time * 24, &dumpZ) * 60;
	Sunset_TimeHH = Sunset_Time * 24;
	Sunset_TimeMM = modf(Sunset_Time * 24, &dumpZ) * 60;
}

static void setup()
{
	arm_pro_mini::setup();
	// Initialize the USB serial connection. This will allow us to print messages.
	usb_serial::setup();
	// Get ready to monitor the ISP button
	isp_button_monitor::setup();
	//Newlib Nano support for scanf float
	asm (".global _scanf_float");
	//Newlib Nano support for printf float
	asm (".global _printf_float");

	Chip_TIMER_Init(Minute_Timer);
	Chip_TIMER_PrescaleSet(Minute_Timer, prescale - 1);
	Chip_TIMER_Reset(Minute_Timer);
	Chip_TIMER_SetMatch(Minute_Timer, 0, 60000000 - 1);
	Chip_TIMER_ResetOnMatchEnable(Minute_Timer, 0);
	Chip_TIMER_SetMatch(Minute_Timer, 1, 60000000 - 1);
	Chip_TIMER_MatchEnableInt(Minute_Timer, 1);
	Chip_TIMER_Enable(Minute_Timer);
	NVIC_EnableIRQ(Minute_TimerIRQn);
	//Ask for a dummy input
	scanf3("%c", &dummy);
	printf("Please Enter The Current Latitude\r\n");
	scanf3("%f", &Latitude);
	printf("%f\r\n", Latitude);
	printf("Please Enter The Current Longitude\r\n");
	scanf3("%f", &Longitude);
	printf("%f\r\n", Longitude);
	printf("Please Enter The Current Time Zone\r\n");
	scanf3("%f", &T_Zone);
	printf("%f\r\n", T_Zone);
	printf("Please Enter The Current Year\r\n");
	scanf3("%d", &Year);
	printf("%d\r\n", Year);
	printf("Please Enter The Current Month\r\n");
	scanf3("%d", &Month);
	printf("%d\r\n", Month);
	printf("Please Enter The Current Day\r\n");
	scanf3("%d", &Day);
	printf("%d\r\n", Day);
	printf("Please Enter The Current Hour\r\n");
	scanf3("%d", &Hour);
	printf("%d\r\n", Hour);
	printf("Please Enter The Current Minute\r\n");
	scanf3("%d", &Minute);
	printf("%d\r\n", Minute);
	Do_the_Math();
	printf("Sun Rise %d:%d \r\nSun Set %d:%d\r\n", Sunrise_TimeHH,
			Sunrise_TimeMM, Sunset_TimeHH, Sunset_TimeMM);
	//Are we at Night?
	if (((Hour * 60 + Minute) >= 0
			&& (Hour * 60 + Minute) < (Sunrise_TimeHH * 60 + Sunrise_TimeMM))
			|| ((Hour * 60 + Minute) >= (Sunset_TimeHH * 60 + Sunset_TimeMM)
					&& (Hour * 60 + Minute) <= 24 * 60))
		led.set(true); //Turn ON the Lights
	SyS_Ready = true;
}

static void loop()
{
	// If the ISP button is pressed, this will jump to the USB/ISP
	// mode, allowing to upgrade the firmware via drag and drop.
	// Otherwise just reset the board while the ISP button is pressed.
	isp_button_monitor::loop();
}

void INTERRUPT()
{
	if (SyS_Ready)
	{
		//Minute passed
		if (Minute == 59)//last minute in the hour?
		{
			Minute = 0;//reset the minute and increase the hour
			if (Hour == 23)//last hour in the day?
			{
				Hour = 0;//reset the hour and increase the date
				Date++;
				Do_the_Math();//Calculate the new sunrise time and sunset time of the new day
			}
			else//it is not the last hour in the day
				Hour++;
		}
		else//it is not the last minute in the hour
			Minute++;
		if (Hour == Sunrise_TimeHH)//the current time is sunrise?
			if (Minute == Sunrise_TimeMM)
				led.set(false);//Turn OFF the Lights, we are not longer at night
		if (Hour == Sunset_TimeHH)//the current time is sunset?
			if (Minute == Sunset_TimeMM)
				led.set(true);//Turn ON the Lights, we are at night
	}
}

extern "C"
{
void TIMER32_1_IRQHandler(void)

{
	Chip_TIMER_ClearMatch(Minute_Timer, 1);
	INTERRUPT();
	return;
}
}

int main(void)
{
	setup();
	for (;;)
	{
		loop();
	}
}
