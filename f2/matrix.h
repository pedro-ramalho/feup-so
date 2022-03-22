typedef struct {
  int rows;
  int cols;
  double vals[][];
} matrix;

matrix* matrix_new(int, int); //done
matrix* matrix_add(matrix*, matrix*); //done
matrix* matrix_sub(matrix*, matrix*); // done
matrix* matrix_mul(matrix*, matrix*); //done
matrix* matrix_trans(matrix*); 

double matrix_get(int, int, matrix*);

void matrix_print(matrix*); //done
void matrix_set(int, int, double, matrix*);