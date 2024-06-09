#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
     free(mat);
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
                         scanf("%d", mat->matrix[i][j]);
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

void print(MAT mat) {
     printf("%c", (char)214);
     
     for(int i = 0; i < mat.size; i++) {
          for(int j = 0; j < mat.size; j++) {
               printf("%d", mat.matrix[i][j]);
               if(i==0 && j==mat.size-1)
                    printf("%c\n",(char)183);
               else if(j==mat.size-1)
                    printf("%c\n",(char)186);
               else
                    printf(" ");
          }
          if(i==mat.size)
               printf("%c",(char)211);
          else
               printf("%c",(char)186)
     }
     printf("%c", (char)189);

}



int main(){

}









