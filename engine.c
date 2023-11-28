#include <stdio.h>


void print_array(int array[], int length) {
    for (int i=0; i<length; i++) {
        printf(" [%d] %d \n", i+1, array[i]);
    }
}

int is_special(int total_box, int horizontal_box, int vertical_box, int i) {
    if (i - horizontal_box <= 0   || (i%horizontal_box) == 0 ||  ((i - 1)%horizontal_box) == 0 || ((float)i/(float)horizontal_box) >=  ((  (float)(total_box - horizontal_box) +1)/(float)horizontal_box)) {
        return 1;       
    }
    return 0;
}

int fate_decider(int fate_point, int current_status) {

    if (current_status == 1 && (fate_point == 2 || fate_point == 3 )) {
        return 1;
    }

    if (fate_point == 3 && current_status == 0 ) {
        return 1;
    }

    return 0;
}

/*
    1 1 1 0 0
    1 0 0 0 0
    0 0 0 0 0
    0 0 0 0 0
    0 0 0 0 0

*/

void main(void) {
    int total_box = 25;
    int matrix[] = {0, 0, 0, 0, 0,
                    0, 0, 1, 0, 0,
                    0, 0, 1, 0, 0,
                    0, 0, 1, 0, 0,
                    0, 0, 0, 0, 0
                    };

    int buffer[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int horizontal_box = 5;
    int vertical_box = 5;

    for (int i=1; i <= total_box; i++) {
        int fate_point = 0;

        if (is_special(total_box, horizontal_box, vertical_box, i)) {
            continue;
        }

        int top_neighbor_index = (i -1) - horizontal_box;
        int bottim_neighbor_index = (i-1) + horizontal_box;

        fate_point += matrix[top_neighbor_index] + matrix[top_neighbor_index - 1] + matrix[top_neighbor_index + 1];
        fate_point += matrix[bottim_neighbor_index] + matrix[bottim_neighbor_index - 1] + matrix[bottim_neighbor_index];
        fate_point += matrix[i -2] + matrix[i];


        buffer[i-1] = fate_decider(fate_point, matrix[i-1]);
    } 

    print_array(buffer, total_box);


    }
    

 