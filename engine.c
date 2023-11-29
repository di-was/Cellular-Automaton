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
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0
                    };

    int buffer[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int horizontal_box = 5;
    int vertical_box = 5;

    for (int i=1; i <= total_box; i++) {
        int fate_point = 0;
        int top_neighbor_index = (i -1) - horizontal_box;
        int bottim_neighbor_index = (i-1) + horizontal_box;

        if (is_special(total_box, horizontal_box, vertical_box, i)) {
            int index = i - 1;
            if (index - 1 < 0) {
               
                // top left box
                fate_point += matrix[index + 1] + matrix[index + (horizontal_box - 1)]; // left right
                fate_point += matrix[bottim_neighbor_index] + matrix[bottim_neighbor_index + 1] + matrix[index + (2*horizontal_box) - 1]; // bottom left right
                fate_point += matrix[total_box - horizontal_box] + matrix[total_box - horizontal_box + 1] + matrix[total_box]; // top left right
            }
            else if (i - horizontal_box == 0) {
                // top right box
                fate_point += matrix[index - 1] + matrix[0]; // left right
                fate_point += matrix[bottim_neighbor_index] + matrix[bottim_neighbor_index - 1] + matrix[0 + horizontal_box]; // bottom left right
                fate_point += matrix[total_box - 1] + matrix[total_box - 2] + matrix[total_box - horizontal_box]; // top left right
            }
            else if (index == total_box - horizontal_box) {
                // bottom left box
                fate_point += matrix[index] + matrix[total_box - 1]; // left right
                fate_point += matrix[top_neighbor_index] + matrix[top_neighbor_index + 1] + matrix[i - 1]; // top left right
                fate_point += matrix[0] + matrix[1] + matrix[horizontal_box - 1]; // bottom left right;
            }
            else if (i == total_box) {
                // bottom right box
                fate_point += matrix[index - 1] + matrix[total_box - horizontal_box]; // left right
                fate_point += matrix[top_neighbor_index] + matrix[top_neighbor_index - 1] + matrix[top_neighbor_index - horizontal_box -1];
                fate_point += matrix[0] + matrix[horizontal_box - 1] + matrix[horizontal_box - 2];
            }
            else if ( index > 0 && index < horizontal_box - 1) {
                // top middle
                fate_point += matrix[index - 1] + matrix[index + 1]; // left right
                fate_point += matrix[bottim_neighbor_index] + matrix[bottim_neighbor_index + 1] + matrix[bottim_neighbor_index - 1]; // bottom left right
                fate_point +=  matrix[total_box - horizontal_box + index] + matrix[total_box - horizontal_box + index +1] + matrix[total_box - horizontal_box + index -1]; // top left right 
            }
            else if (index < 24 && index > 20) {
                // bottom middle
                fate_point += matrix[index - 1] + matrix[index + 1]; // left right
                fate_point += matrix[top_neighbor_index] + matrix[top_neighbor_index - 1] + matrix[top_neighbor_index + 1]; // top left right
                fate_point += matrix[index - (total_box - horizontal_box)] + matrix[index - (total_box - horizontal_box) + 1] + matrix[index - (total_box - horizontal_box) -1]; // bottom left right
            } 
            else if (index % horizontal_box == 0) {
                // left vertical
            }
            else{
                // right vertical
            }
            buffer[i-1] = fate_decider(fate_point, matrix[i-1]);
        }
        else{
            fate_point += matrix[top_neighbor_index] + matrix[top_neighbor_index - 1] + matrix[top_neighbor_index + 1];
            fate_point += matrix[bottim_neighbor_index] + matrix[bottim_neighbor_index - 1] + matrix[bottim_neighbor_index + 1];
            fate_point += matrix[i -2] + matrix[i];
            buffer[i-1] = fate_decider(fate_point, matrix[i-1]);
        }
    } 
    print_array(buffer, total_box);
    }
    
