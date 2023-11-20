#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {
int* increase_a[100];
int increase_return_control[100];
int increase_stack_control = 0;
int increase_external_call_control = 0;
int increase_internal_call_control[100];

goto start;
increase_subprogram:

	int a0[100];
	a0[increase_stack_control] = *increase_a[increase_stack_control];
	int i0[100];
	i0[increase_stack_control] = a0[increase_stack_control] + 10;
	*increase_a[increase_stack_control] = i0[increase_stack_control];
	goto increase_return;

start:

	int x;
	x = 0;
	x = 1;
	int* a1;
	a1 = &x;
	increase_a[increase_stack_control+1] = a1;
	increase_external_call_control = 0;
	increase_stack_control = increase_stack_control + 1;
	goto increase_subprogram;

increase_external_call_0:

	int a2;
	a2 = x;
	printf("%d\n",a2);
goto end;
	increase_return:
switch (increase_stack_control--) {
case 1:
switch (increase_external_call_control) {
case 0:
goto increase_external_call_0;
}
default:
switch (increase_internal_call_control[increase_stack_control]) {
}
}
end:

return 0;
}
