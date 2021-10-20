#include<cstdio>
#include<windows.h>

void error()
{
	MessageBox(NULL,"error!","error!",4);
	error();
}

int main()
{
	FreeConsole();
	error();
 } 
