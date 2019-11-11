/*
 * SD_sin.h
 *
 *  Created on: May 14, 2019
 *      Author: SYS5
 */

#include "../common/common.h"

#ifndef SD_SIN_H_
#define SD_SIN_H_

#define	PIO2	1.570796326794896619231e0
#define p0      .1357884097877375669092680e8
#define p1     -.4942908100902844161158627e7
#define p2      .4401030535375266501944918e6
#define p3     -.1384727249982452873054457e5
#define p4      .1459688406665768722226959e3
#define q0      .8644558652922534429915149e7
#define q1      .4081792252343299749395779e6
#define q2      .9463096101538208180571257e4
#define q3      .1326534908786136358911494e3
#define PI 3.14159265

double SD_modf (double x, double *IPtr);
static double sinus(double arg, int quad);
double cos(double arg);
double sin(double rads);
double deg_2_Rad(double deg);
int16_t SD_sin(double deg);
int16_t SD_ramp(int16_t count, int16_t multiplier);
int16_t SD_positive_half_sin(double deg);
int16_t SD_negative_half_sin(double deg);
int16_t SD_triangular(int16_t count, int16_t peak);
int16_t SD_step_InStep(int16_t deg);
int16_t SD_step(int16_t deg);
int16_t SD_pwm(int16_t deg,int16_t clear);


#endif /* SD_SIN_H_ */
