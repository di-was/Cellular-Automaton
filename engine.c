#include <stdio.h>
#include <stdlib.h>

void print_array(int array[], int length, int horizontal_box) {
    for (int i=0; i<length; i++) {
        if (i % horizontal_box == 0 && i != 0) {
            printf("\n");  
        }
        printf(" %d \t", array[i]);
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

int fate_point_calculator(int matrix[], int top_left, int top, int top_right, int left , int right, int bottom_left, int bottom, int bottom_right) {
    int result = matrix[top_left] + matrix[top] +  matrix[top_right];
    result += matrix[left] + matrix[right];
    result += matrix[bottom_left] + matrix[bottom] + matrix[bottom_right];
    return result;
}

void normal_entry_operation(int buffer[], int matrix[], int i, int horizontal_box) {
    int fate_point = 0,  top_neighbor_index = (i -1) - horizontal_box,  bottom_neighbor_index = (i-1) + horizontal_box;
    fate_point = fate_point_calculator(matrix, top_neighbor_index - 1, top_neighbor_index , top_neighbor_index + 1, i -2, i, bottom_neighbor_index - 1, bottom_neighbor_index, bottom_neighbor_index + 1);
    buffer[i-1] = fate_decider(fate_point, matrix[i-1]);
}

void special_entry_operation(int buffer[], int matrix[], int total_box, int horizontal_box, int i) {
    int fate_point = 0,  top_neighbor_index = (i -1) - horizontal_box,  bottom_neighbor_index = (i-1) + horizontal_box;
    int index = i - 1;
    if (index - 1 < 0) {
        fate_point = fate_point_calculator(matrix, total_box - horizontal_box -1, total_box - horizontal_box, total_box - horizontal_box + 1, index + (horizontal_box-1), index + 1, index + (2*bottom_neighbor_index) - 1, bottom_neighbor_index, bottom_neighbor_index + 1);
    }
    else if (i - horizontal_box == 0) {
        // top right box
        fate_point = fate_point_calculator(matrix, total_box-2, total_box - 1, total_box - horizontal_box, index  -1 , 0, bottom_neighbor_index -1, bottom_neighbor_index, 0 + horizontal_box);
    }
    else if (index == total_box - horizontal_box) {
        // bottom left box
        fate_point = fate_point_calculator(matrix, i - 1, top_neighbor_index, top_neighbor_index + 1, total_box - 1, index, horizontal_box - 1, 0, 1);
    }
    else if (i == total_box) {
        // bottom right box
        fate_point = fate_point_calculator(matrix, top_neighbor_index - 1, top_neighbor_index, top_neighbor_index - horizontal_box -1, index -1, total_box - horizontal_box, horizontal_box -2, horizontal_box-1, 0);
    }
    else if ( index > 0 && index < horizontal_box - 1) {
        // top middle
        fate_point = fate_point_calculator(matrix, total_box - horizontal_box + index, total_box - horizontal_box + index + 1, total_box - horizontal_box + index - 1, index - 1, index + 1, bottom_neighbor_index - 1, bottom_neighbor_index, bottom_neighbor_index + 1); 
    }
    else if (index < total_box && index > total_box - horizontal_box) {
        // bottom middle
        fate_point = fate_point_calculator(matrix, top_neighbor_index - 1, top_neighbor_index, top_neighbor_index + 1, index - 1, index + 1, index - (total_box - horizontal_box), index - (total_box - horizontal_box ) + 1, index - (total_box - horizontal_box) - 1);
    } 
    else if (index % horizontal_box == 0) {
        // left vertical
        fate_point = fate_point_calculator(matrix, top_neighbor_index + (horizontal_box - 1), top_neighbor_index , top_neighbor_index + 1, index + 1, index + (horizontal_box - 1), bottom_neighbor_index + (horizontal_box - 1), bottom_neighbor_index, bottom_neighbor_index + 1);
    }
    else{
        // right vertical
        fate_point = fate_point_calculator(matrix, top_neighbor_index - 1, top_neighbor_index, top_neighbor_index - (horizontal_box - 1), index - 1, index - (horizontal_box - 1), bottom_neighbor_index - 1, bottom_neighbor_index, bottom_neighbor_index - (horizontal_box - 1));
    }
    buffer[i-1] = fate_decider(fate_point, matrix[i-1]);
}   



int * engine(int matrix[], int total_box, int horizontal_box, int vertical_box) {
    int * buffer = calloc(total_box, sizeof(int));

    for (int i=1; i <= total_box; i++) {

        if (is_special(total_box, horizontal_box, vertical_box, i)) {

           special_entry_operation(buffer, matrix, total_box, horizontal_box, i);
           
           continue;
        }
        
        normal_entry_operation(buffer, matrix, i, horizontal_box);
    } 
    return buffer;
}