#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {
goto start;
int double_par1[100];
int double_return_value[100];
int double_return_control[100];
int double_stack_control;
int double_call_control;

double_subprogram:

	int double_par2[100];
	double_par2[double_stack_control] = 0;
	int a0;
	a0 = double_par1[double_stack_control];
	int a1;
	a1 = double_par1[double_stack_control];
	int i0;
	i0 = a0 + a1;
	double_par2[double_stack_control] = i0;
	int a2;
	a2 = double_par2[double_stack_control];
	double_return_value[double_stack_control] = a2;
	goto double_return;

start:

	int x;
	x = 0;
	int i;
	i = 0;
	x = 1;
	i = 0;
L0:

	bool b0;
	b0 = i > 10;
	if (b0) goto E0;
	int a3;
	a3 = x;
	double_par1[double_stack_control] = a3;
	double_call_control = 0;
	goto double_subprogram;

double_0:

	int a4;
	a4 = double_return_value[double_stack_control];
	x = a4;
	int a5;
	a5 = i;
	int a6;
	a6 = x;
	printf("%d - %d\n",i,x);
C0:

	i = i + 1;
	goto L0;

E0:

goto end;
	double_return:
switch (double_stack_control) {
case 0:
switch (double_call_control) {
case 0:
goto double_0;
}
}
end:

return 0;
}
