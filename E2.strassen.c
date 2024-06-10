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
          printf("ako chcete zapisat vsetky prvky matice? 1 - z klavesnice, 2 - automaticky");
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

void add_subtract_matrix(MAT A, MAT B,MAT* C, int add) {
    for (int i = 0; i < C->size; i++) {
        for (int j = 0; j < C->size; j++) {
            if (add) {
                C->matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
            } else {
                C->matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
            }
        }
    }
}

void mat_multiply_strassen(MAT* A, MAT* B, MAT* C) {

     int newSize = C->size / 2;
     MAT A11,A12,A21,A22,B11,B12,B21,B22,C11,C12,C21,C22,M1,M2,M3,M4,M5,M6,M7,AResult,BResult;
     constr(&A11 ,newSize);
     constr(&A12 ,newSize);
     constr(&A21 ,newSize);
     constr(&A22 ,newSize);
     constr(&B11 ,newSize);
     constr(&B12 ,newSize);
     constr(&B21 ,newSize);
     constr(&B22 ,newSize);
     constr(&C11 ,newSize);
     constr(&C12 ,newSize);
     constr(&C21 ,newSize);
     constr(&C22 ,newSize);
     constr(&M1 ,newSize);
     constr(&M2 ,newSize);
     constr(&M3 ,newSize);
     constr(&M4 ,newSize);
     constr(&M5 ,newSize);
     constr(&M6 ,newSize);
     constr(&M7 ,newSize);
     constr(&AResult ,newSize);
     constr(&BResult ,newSize);
    
     /*rozdelme matice A a B*/
     for (int i = 0; i < newSize; i++) {
          for (int j = 0; j < newSize; j++) {
               A11.matrix[i][j] = A->matrix[i][j];
               A12.matrix[i][j] = A->matrix[i][j + newSize];
               A21.matrix[i][j] = A->matrix[i + newSize][j];
               A22.matrix[i][j] = A->matrix[i + newSize][j + newSize];

               B11.matrix[i][j] = B->matrix[i][j];
               B12.matrix[i][j] = B->matrix[i][j + newSize];
               B21.matrix[i][j] = B->matrix[i + newSize][j];
               B22.matrix[i][j] = B->matrix[i + newSize][j + newSize];
          }
     }
     
     // M1 = (A11 + A22) * (B11 + B22)
     add_subtract_matrix(A11, A22, &AResult, 1);
     add_subtract_matrix(B11, B22, &BResult, 1);
     mat_multiply_strassen(&AResult, &BResult, &M1); 
     
     // M2 = (A21 + A22) * B11
     add_subtract_matrix(A21, A22, &AResult, 1);
     mat_multiply_strassen(&AResult, &B11, &M2);

     // M3 = A11 * (B12 - B22)
     add_subtract_matrix(B12, B22, &BResult, 0);
     mat_multiply_strassen(&A11, &BResult, &M3);
     
     // M4 = A22 * (B21 - B11)
     add_subtract_matrix(B21, B11, &BResult, 0);
     mat_multiply_strassen(&A22, &BResult, &M4);

     // M5 = (A11 + A12) * B22
     add_subtract_matrix(A11, A12, &AResult, 1);
     mat_multiply_strassen(&AResult, &B22, &M5);

     // M6 = (A21 - A11) * (B11 + B12)
     add_subtract_matrix(A21, A11, &AResult, 0);
     add_subtract_matrix(B11, B12, &BResult, 1);
     mat_multiply_strassen(&AResult, &BResult, &M6);

     // M7 = (A12 - A22) * (B21 + B22)
     add_subtract_matrix(A12, A22, &AResult, 0);
     add_subtract_matrix(B21, B22, &BResult, 1);
     mat_multiply_strassen(&AResult, &BResult, &M7);
     
     // C11 = M1 + M4 - M5 + M7
     add_subtract_matrix(M1, M4, &AResult, 1);
     add_subtract_matrix(AResult, M5, &BResult, 0);
     add_subtract_matrix(BResult, M7, &C11, 1);

     // C12 = M3 + M5
     add_subtract_matrix(M3, M5, &C12, 1);

     // C21 = M2 + M4
     add_subtract_matrix(M2, M4, &C21, 1);

     // C22 = M1 + M3 - M2 + M6
     add_subtract_matrix(M1, M3, &AResult, 1);
     add_subtract_matrix(AResult, M2, &BResult, 0);
     add_subtract_matrix(BResult, M6, &C22, 1);
     
     for (int i = 0; i < newSize; i++) { //zdruzenie matic
        for (int j = 0; j < newSize; j++) {
            C->matrix[i][j] = C11.matrix[i][j];
            C->matrix[i][j + newSize] = C12.matrix[i][j];
            C->matrix[i + newSize][j] = C21.matrix[i][j];
            C->matrix[i + newSize][j + newSize] = C22.matrix[i][j];
        }
    }
    
    destr(&A11);
    destr(&A12);
    destr(&A21);
    destr(&A22);
    destr(&B11);
    destr(&B12);
    destr(&B21);
    destr(&B22);
    destr(&C11);
    destr(&C12);
    destr(&C21);
    destr(&C22);
    destr(&M1);
    destr(&M2);
    destr(&M3);
    destr(&M4);
    destr(&M5);
    destr(&M6);
    destr(&M7);
    destr(&AResult);
    destr(&BResult);
}

int main(){
     srand(time(0));
     MAT m1,m2,m3;
     int size = 0;

     do{
     printf("napiste rozmer n matic 2^n x 2^n: ");
     scanf("%d", &size);
     } while(size < 1);
     
     constr(&m1,(int)pow(2,size));
     fill(&m1);
     show(m1);
     
     
     constr(&m2,(int)pow(2,size));
     fill(&m2);
     show(m2);
     
     constr(&m3,(int)pow(2,size));
     mat_multiply_strassen(&m1,&m2,&m3);
     
     printf("vysledok nasobenia uvedenych matic:\n");
     show(m3);
     destr(&m1);
     destr(&m2);
     destr(&m3);
}









