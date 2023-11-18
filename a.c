#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {
goto start;
int not_par1[100];
int not_return_value[100];
int not_return_control[100];
int not_stack_control;
int not_call_control;

not:

	int a0;
	a0 = not_par1[not_stack_control];
	int a1;
	a1 = not_par1[not_stack_control];
	int i0;
	i0 = a0 + a1;
	not_return_value[not_stack_control] = i0;
	goto not_return;

start:

	int x;
	x = 0;
	x = 10;
	int a2;
	a2 = x;
	not_par1[not_stack_control] = a2;
	not_call_control = 0;
	goto not;

not_0:

	int a3;
	a3 = not_return_value[not_stack_control];
	x = a3;
	int a4;
	a4 = x;
	printf("%d\n",x);
goto end;
	not_return:
switch (not_stack_control) {
case 0:
switch (not_call_control) {
case 0:
goto not_0;
}
}
end:

return 0;
}
