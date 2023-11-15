#include <stdio.h>

int main() {
    int asda_x[100];
    int asda_return_value[100];
    int asda_stack_control = 0;
    int asda_call_control = 0;

    int asda_z[100];
    
    goto start;

    asda_begin:
    int b0;
    b0 = asda_x[asda_stack_control] == 1;
    if (!b0) goto I0;
    asda_return_value[asda_stack_control] = 1;
    goto asda_return;
    I0:
    int i0;
    i0 = asda_x[asda_stack_control] - 1;
    asda_x[asda_stack_control+1] = i0;
    asda_stack_control += 1;
    goto asda_begin;
    asda_rec:
    int i1;
    i1 = asda_return_value[asda_stack_control+1];
    int i2 = asda_x[asda_stack_control];
    int i3 =  i2 * i1;
    asda_return_value[asda_stack_control] = i3;
    goto asda_return;

    start:
    int x;
    asda_x[asda_stack_control] = 3;
    asda_call_control = 0;
    goto asda_begin;
    asda_0:
    x = asda_return_value[asda_stack_control];

    int y;
    asda_x[asda_stack_control] = 6;
    asda_call_control = 1;
    goto asda_begin;
    asda_1:
    y = asda_return_value[asda_stack_control];

    goto end;
    asda_return:
    switch (asda_stack_control) {
        case 0:
            switch (asda_call_control) {
                case 0:
                    goto asda_0;
                    break;
                case 1:
                    goto asda_1;
                    break;
            }
        default:
            asda_stack_control -= 1;
            goto asda_rec;
    }
    end:
    printf("%d\n", x);
    printf("%d\n", y);
    return 0;
}