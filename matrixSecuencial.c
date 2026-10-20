#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define NTHREADS 12
#define SIDELENGTH 2000
#define MATRIXSIZE ((SIDELENGTH) * (SIDELENGTH))
#define FOR(i, size) for(size_t i = 0; i < size; i++)
#define INDEX(i, j) ((i) * (SIDELENGTH) + (j))
#define MIN(a, b) ((a) < (b)? (a) : (b))

typedef struct matrix Matrix;
typedef struct parametros Parametros;

Matrix m1;
Matrix m2;
Matrix m3; //m1 * m2

struct matrix{
	int id;
	float *matrix;
};

struct parametros{
	size_t fromRow;
	size_t toRow;
};

void initMatrix(Matrix *m, int id){
	m->id = id;

	m->matrix = (float *)malloc(sizeof(float) * MATRIXSIZE);
	if(m->matrix == NULL){
		perror("Error de asignación de memoria\n");
		exit(1);
	}

	FOR(i, SIDELENGTH)
		FOR(j, SIDELENGTH)
			m->matrix[INDEX(i, j)] = ((float)random() / (float)RAND_MAX) * 1000.0f;
}

void freeMatrix(Matrix *m) {
	if (m != NULL && m->matrix != NULL) {
		free(m->matrix);
		m->matrix = NULL;
	}
}

void initParametros(Parametros* p, size_t fromRow, size_t step){
	p->fromRow = fromRow;
	p->toRow = MIN(fromRow + step, SIDELENGTH);
}

void *multMatrixLine(void *arg){
	Parametros *p;
	p = (Parametros *) arg;

	size_t idxRow = p->fromRow;
	size_t limit = p->toRow;

	while(idxRow < limit){
		FOR(idxColumn, SIDELENGTH){
			float sum = 0.0f;
			FOR(k, SIDELENGTH){
				size_t m1Pos = INDEX(idxRow, k);
				size_t m2Pos = INDEX(k, idxColumn);

				sum += m1.matrix[m1Pos] * m2.matrix[m2Pos];
			}
			m3.matrix[INDEX(idxRow, idxColumn)] = sum;
		}
		idxRow++;
	}
	printf("Calculado desde %zu hasta %zu.\n", p->fromRow, p->toRow - 1);
	return NULL;
}

int main(void){
	srandom((unsigned int)time(NULL));
	struct timespec start, finish;
	double elapsed;

	initMatrix(&m1, 1);
	initMatrix(&m2, 2);
	
	m3.id = 3;
	m3.matrix = (float *)malloc(sizeof(float) * MATRIXSIZE);
	if(m3.matrix == NULL){
		perror("Error de asignación de memoria\n");
		exit(1);
	}

	Parametros params = {0, SIDELENGTH};


	printf("Iniciando multiplicación (%dx%d)...\n", SIDELENGTH, SIDELENGTH);

	clock_gettime(CLOCK_MONOTONIC, &start);

	multMatrixLine((void *)(&params));

	clock_gettime(CLOCK_MONOTONIC, &finish);

	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	printf("Tiempo de ejecución: %.6f segundos\n", elapsed);
	freeMatrix(&m1);
	freeMatrix(&m2);
	freeMatrix(&m3);
	return 0;
}
