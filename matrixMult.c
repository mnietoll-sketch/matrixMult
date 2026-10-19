#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define nThreads 16
#define FOR(i, size) for(size_t i = 0; i < size; i++)
typedef struct matrix Matrix;

Matrix *resultMatrix = NULL;

struct matrix{
	int id;
	size_t size;
	float *matrix;
};

typedef struct parametros{
	Matrix m1;
	Matrix m2;
	size_t step;
	size_t idxLine;
} Parametros;

void initMatrix(Matrix *m, int id, size_t size){
	m->id = id;
	m->size = size;

	m->matrix = (float *)malloc(sizeof(float) * size * size);
	if(m->matrix == NULL){
		perror("Error de asignación de memoria\n");
		exit(1);
	}

	FOR(i, size)
		FOR(j, size)
			m->matrix[i * size + j] = ((float)random() / (float)RAND_MAX) * 1000.0f;
}

void freeMatrix(Matrix *m) {
    if (m != NULL && m->matrix != NULL) {
        free(m->matrix);
        m->matrix = NULL;
    }
}

void initParametros(Parametros* p, size_t size){
	initMatrix(&p->m1, 1, size);
	initMatrix(&p->m2, 2, size);
	p->step = (size_t)(1 + size / nThreads);
	p->idxLine = 0;
}

void freeParametros(Parametros* p){
	freeMatrix(&p->m1);
	freeMatrix(&p->m2);
}

void *multMatrixLine(void *arg){
	Parametros *p;
	p = (Parametros *) arg;

	if(resultMatrix == NULL)
		return NULL;

	Matrix *m1 = &p->m1;
	Matrix *m2 = &p->m2;
	size_t pos = p->i * resultMatrix->size + p->j;
	size_t size = resultMatrix->size;

	FOR(k, size){
		size_t m1Pos = p->i * size + k;
		size_t m2Pos = k*size + p->j;
		resultMatrix->matrix[pos] += m1->matrix[m1Pos] * m2->matrix[m2Pos];
	}

	return NULL;
}
