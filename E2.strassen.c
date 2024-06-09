#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {

int** matrix;
int size;

}MAT;

void constr(MAT* mat, int size) {
     mat->size = size;
     mat->matrix = (int**)malloc(size * sizeof(int*));
     
     for(int i = 0; i < size; i++) {
           mat->matrix[i] = (int*)malloc(size * sizeof(int));
     }
}

void destr(MAT* mat) {
     for(int i = 0; i < mat->size; i++) {
          free(mat->matrix[i]);
     }

     free(mat->matrix); 
}

void fill(MAT* mat) {
     int choice;

     srand(time(0));
     
     do{
          printf("chcete zapisat vsetky prvky matice: 1 - z klavesnice, 2 - auto?");
          scanf("%d",&choice);
     } while (choice != 1 && choice != 2);
     
     for(int i = 0; i < mat->size; i++) {
          for(int j = 0; j < mat->size; j++) {
               switch(choice) {
                    case 1: {
                         printf("[%d][%d]:", i + 1, j + 1);
                         scanf("%d", &(mat->matrix[i][j]));
                         break;
                    }
                    case 2: {
                         mat->matrix[i][j] = rand()%200 - 100;
                         break;
                    }
               }
          }
     }
}

void show(MAT mat) {
     
     for(int i = 0; i < mat.size; i++) {
          for(int j = 0; j < mat.size; j++) {
               printf("%d ", mat.matrix[i][j]);
          }
          printf("\n");
     }

}



int main(){
     srand(time(0));
     MAT m1;
     int size = 0;

     do{
     printf("napiste rozmer n matice 2^n x 2^n: ");
     scanf("%d", &size);
     } while(size < 1);
     
     printf("%d", (int)pow(2,size));
     
     constr(&m1,(int)pow(2,size));
     fill(&m1);
     show(m1);
     destr(&m1);
}









