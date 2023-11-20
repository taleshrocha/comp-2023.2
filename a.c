#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {
goto start;
int fatorial_x[100];
int fatorial_return_value[100];
int fatorial_return_control[100];
int fatorial_stack_control;
int fatorial_external_call_control;
int fatorial_internal_call_control;

fatorial_subprogram:

	int a0;
	a0 = fatorial_x[fatorial_stack_control];
	bool b0;
	b0 = a0 == 1;
	if (b0) goto I0;
	goto I1;

I0:

	fatorial_return_value[fatorial_stack_control] = 1;
	goto fatorial_return;

	goto I2;

I1:

I2:

	int a1;
	a1 = fatorial_x[fatorial_stack_control];
	int a2;
	a2 = fatorial_x[fatorial_stack_control];
	int i0;
	i0 = a2 - 1;
	fatorial_stack_control = fatorial_stack_control + 1;
	fatorial_x[fatorial_stack_control] = i0;
	fatorial_internal_call_control = 0;
	goto fatorial_subprogram;

fatorial_internal_call_0:

	int a3;
	a3 = fatorial_return_value[fatorial_stack_control+1];
	int i1;
	i1 = a1 * a3;
	fatorial_return_value[fatorial_stack_control] = i1;
	goto fatorial_return;

start:

	int x;
	x = 0;
	x = 4;
	int a4;
	a4 = x;
	int a5;
	a5 = x;
	fatorial_stack_control = fatorial_stack_control + 1;
	fatorial_x[fatorial_stack_control] = a5;
	fatorial_external_call_control = 0;
	goto fatorial_subprogram;

fatorial_external_call_0:

	int a6;
	a6 = fatorial_return_value[fatorial_stack_control+1];
	printf("fatorial of %d is %d\n",a5,a6);
goto end;
	fatorial_return:
switch (fatorial_stack_control--) {
case 1:
switch (fatorial_external_call_control) {
case 0:
goto fatorial_external_call_0;
}
default:
switch (fatorial_internal_call_control) {
case 0:
goto fatorial_internal_call_0;
}
}
end:

return 0;
}
