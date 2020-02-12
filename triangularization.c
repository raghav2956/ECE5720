#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdint.h>	

#define BILLION 1E9

//Function for Simple Row by Column Matrix Multiplication
void triangularization( int dim ){
  //Initialize Timespec structs 
  struct timespec start, end;
  
  //Initialize an array of pointers (2D Matrix)
  float* matrix_A[ dim ];
  for(int i = 0; i < dim; i++){
    //For each row, allocate memory of size dim
    matrix_A[i] = malloc( sizeof(float) * dim );
    //Once memory is allocated for a row, populate the columns of that row
    for(int j = 0; j < dim; j++){
      matrix_A[i][j] = drand48();
      printf("Random element is %f\n", matrix_A[i][j]);
    }
  }
  
  float* vector_b = malloc(sizeof(float) * dim);
  for(int i = 0; i < dim; i++){
    vector_b[i] = drand48();
  }
  
  float* vector_x = malloc(sizeof(float) * dim);
  
  for (int i = 0; i < dim; i++){
    float max_el = (matrix_A[i][i]);
    if ( max_el < 0 ){
      max_el = -max_el;
    }
    int max_el_row = i;
    for (int j = i; j < dim; j++){
        float temp = matrix_A[j][i];
        if (temp < 0){
          temp = -temp;
        }
        if (temp > max_el){
          max_el = temp;
          max_el_row = j;
        }
    }
    printf("max_el is %.6f\n", max_el);
    float* temp_row = malloc(sizeof(float) * dim);
    for (int j = 0; j < dim - 1; j++){
      temp_row[j] = matrix_A[i][j];
      matrix_A[i][j] = matrix_A[max_el_row][j]; 
      matrix_A[max_el_row][j] = temp_row[j];
    }
    
    float temp_b = vector_b[i];
    vector_b[i] = vector_b[max_el_row];
    vector_b[max_el_row] = temp_b;
    
    for (int j = i + 1; j < dim; j++){
      printf("matrix_A[j][i] is %f\n", matrix_A[j][i]);
      printf("matrix_A[i][i] is %f\n", matrix_A[i][i]);
      float factor = matrix_A[j][i]/matrix_A[i][i];
      printf("Factor is %f\n", factor);
      for (int k = i; k < dim; k++){
        matrix_A[j][k] = matrix_A[j][k] - factor * matrix_A[i][k];
      }
      vector_b[j] = vector_b[j] - factor * vector_b[i];
    }
  } 
  
  
  
  
  
  
  
  
}
  
  
  
  
  
  
  
//Main function
int main(int argc, char** argv){
  //Set seed
  srand48(2);
  //Take dimension value from command line
  int dim = atoi(argv[2]);
  triangularization(dim);
  return 0;
}  
