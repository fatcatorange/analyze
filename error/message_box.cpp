#include<cstdio>
#include<windows.h>
void checkOutput(int output);

void error()
{
	int output;
	output=MessageBox(NULL,"error!","error!",4);
	checkOutput(output);
}

void checkOutput(int output)
{
	if(output==6)
		error();
	if(output==7)
		error();
} 
int main()
{
	FreeConsole();
	error();
 } 
