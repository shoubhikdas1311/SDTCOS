/*
	C program for floating point sin/cos.
	Calls SD_modf.
	There are no error exits.
	Coefficients are #3370 from Hart & Cheney (18.80D).
*/

#include "SD_trigno.h"


double SD_modf (double x, double *IPtr)
{
    int intpart;
   intpart = x;
   *IPtr = intpart;
   x = x - intpart;
   return x;
}
static double sinus(double arg, int quad)
{
	double e, f, ysq, x, y, temp1, temp2;
	int k;

	x = arg;
	if(x < 0) {
		x = -x;
		quad += 2;
	}
	x *= 1/PIO2;	/* underflow? */
	if(x > 32764) {
		y = SD_modf(x, &e);
		e += quad;
		SD_modf(0.25*e, &f);
		quad = e - 4*f;
	} else {
		k = x;
		y = x - k;
		quad += k;
		quad &= 3;
	}
	if(quad & 1)
		y = 1-y;
	if(quad > 1)
		y = -y;

//	printf("e = %lf,\nf = %lf, \nysq = %lf, \nx = %lf, \ny = %lf, \ntemp1 = %lf, \ntemp = %lf,\nk = %d\n", e, f, ysq, x, y, temp1, temp2, k);

	ysq = y*y;
//	printf("PIO2 = %lf,\nysq = %lf,\np0 = %lf, \np1 = %lf, \np2 = %lf, \np3 = %lf", PIO2, ysq, p0,p1,p2,p3,p4, q0, q1, q2, q3);

	temp1 = ((((p4*ysq+p3)*ysq+p2)*ysq+p1)*ysq+p0)*y;
	temp2 = ((((ysq+q3)*ysq+q2)*ysq+q1)*ysq+q0);
//	printf("temp1 = %lf,\ntemp2 = %lf", temp1, temp2);
	return (temp1/temp2);
}

double cos(double arg)
{
	if(arg < 0)
		arg = -arg;
	return sinus(arg, 1);
}

double sin(double arg)
{
	return sinus(arg, 0);
}
double tan(double rad)
{
	double tan;
	tan = sin(rad)/cos(rad);
	return tan;
}
double deg_2_Rad(double deg)
{
	double val,rad;
	val = PI / 180;
    rad = deg * val;
    return rad;
}
int16_t SD_sin(double deg)
{
	int16_t res;
	if (deg <= 90) 
	{
		res = (sin(deg_2_Rad(deg))*2047) + 2047;//deg_2_Rad(deg)
	}
	else if(deg <= 180)
	{
		res = ((sin(deg_2_Rad(deg))*2047) + 2047);//deg_2_Rad(deg)
	}
	else if (deg <= 270) 
	{
		res = 2047 + (sin(deg_2_Rad(deg))*2047);
	}
	else if (deg <= 360) 
	{
		res = ((sin(deg_2_Rad(deg))*2047) + 2047);//deg_2_Rad(deg);		
	}
	return res;
}
int16_t SD_positive_half_sin(double deg)
{
	int16_t res;
	if (deg <= 90) 
	{
		res = (sin(deg_2_Rad(deg))*2047) + 2047;//deg_2_Rad(deg)
	}
	else if(deg <= 180)
	{
		res = 2047;//deg_2_Rad(deg)
	}
	else if (deg <= 270) 
	{
		res = 2047 + (sin(deg_2_Rad(deg))*2047);
	}
	else if (deg <= 360) 
	{
		res = 2047;//deg_2_Rad(deg);		
	}
	return res;
}
int16_t SD_negative_half_sin(double deg)
{
	int16_t res;
	if (deg <= 90) 
	{
		res = 2047;//deg_2_Rad(deg)
	}
	else if(deg <= 180)
	{
		res = ((sin(deg_2_Rad(deg))*2047) + 2047);//deg_2_Rad(deg)
	}
	else if (deg <= 270) 
	{
		res = 2047;//deg_2_Rad(deg)
	}
	else if (deg <= 360) 
	{
		res = ((sin(deg_2_Rad(deg))*2047) + 2047);//deg_2_Rad(deg);		
	}
	return res;
}
int16_t SD_step(int16_t deg)
{
	int16_t res;
	if (deg <= 180) 
	{
		res = 4095;//deg_2_Rad(deg)
	}
	else if (deg <= 360) 
	{
		res = 0;//deg_2_Rad(deg);		
	}
	return res;
}
int16_t SD_pwm(int16_t deg,int16_t clear)
{
	int16_t res;
	if (deg <= clear) 
	{
		res = 4095;//deg_2_Rad(deg)
	}
	else
	{
		res = 0;//deg_2_Rad(deg);		
	}
	return res;
}
int16_t SD_step_InStep(int16_t deg)
{
	int16_t res;
	if (deg <= 90) 
	{
		res = 4095;//deg_2_Rad(deg)
	}
	else if(deg <= 180)
	{
		res = 2047;//deg_2_Rad(deg)
	}
	else if (deg <= 270) 
	{
		res = 0;//deg_2_Rad(deg)
	}
	else if (deg <= 360) 
	{
		res = 2047;//deg_2_Rad(deg);		
	}
	return res;
}
int16_t SD_triangular(int16_t count, int16_t peak)
{
	int res;
	if(count > peak)
	{
		res = --peak;
		return res;
	}
	else
		return count;
}
int16_t SD_ramp(int16_t count, int16_t multiplier)
{
	int16_t sig;
	sig = count * multiplier;
	return sig;
}
