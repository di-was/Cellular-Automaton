#include <stdio.h>


void print_matrix(int matrix[3][3]) {
    for (int i=0; i < 3; i++) {
        for (int j=0; j < 3; j++) {
            printf("%d \t", matrix[i][j]);
        }
        printf("\n");
    }
}

int is_special(int total_box, int horizontal_box, int vertical_box, int i) {
    if (i - horizontal_box <= 0   || (i%horizontal_box) == 0 ||  ((i - 1)%horizontal_box) == 0 || ((float)i/(float)horizontal_box) >=  ((  (float)(total_box - horizontal_box) +1)/(float)horizontal_box)) {
        return 1;       
    }
    return 0;
}

void main(void) {
    int total_box = 20;
    int matrix[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    int buffer[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    int horizontal_box = 4;
    int vertical_box = 5;

    for (int i=1; i <= total_box; i++) {
        printf("%d : %d \n",  i , is_special(total_box, horizontal_box, vertical_box, i));
      
    }       

    }
    

 