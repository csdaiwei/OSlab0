/*************************************************************************
	> File Name: math.c
	> Author: david
	> Mail: david9321@163.com 
	> Created Time: Sat 16 Mar 2013 10:00:48 PM CST
 ************************************************************************/

//float absolute value 
float fabs(float x)
{
	if(x < 0)
		x = -x;
	return x;
}
