/*
 * buscaminas.c
 *
 *  Created on: 21 feb 2023
 *      Author: nakal
 */


#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int **mat;
	unsigned int dim1, dim2;
} Matrix_t;

Matrix_t* Matrix() {
	Matrix_t *self;

	self = (Matrix_t*)malloc(sizeof(Matrix_t));
	if (self == NULL) {
		return NULL;
	}

	self->mat = NULL;
	self->dim1 = 0;
	self->dim2 = 0;

	return self;
}

Matrix_t* MatrixWithDimensions(unsigned int dim1, unsigned int dim2) {
	Matrix_t *self = NULL;
	unsigned int i, j;

	self = Matrix();
	if (self == NULL) {
		return NULL;
	}

	self->dim1 = dim1;
	self->dim2 = dim2;
	self->mat = malloc(dim1 * sizeof(int*));
	if (self->mat == NULL) {
		return NULL;
	}

	for (i = 0; i < self->dim1; i++) {
		self->mat[i] = calloc(self->dim2, sizeof(int));
		if (self->mat[i] == NULL) {
			for (j = 0; j < i; j++) {
				free(self->mat[j]);
			}
			return NULL;
		}
	}

	return self;
}

void destroyMatrix(Matrix_t *self) {
	unsigned int i;

	if (self != NULL) {
		for (i = 0; i < self->dim1; i++) {
			free(self->mat[i]);
		}
		free(self->mat);
	}

	free(self);
}

int errorsInMatrix(Matrix_t *self) {
	unsigned int i;

	if (self == NULL) {
		return -1;
	}
	else {
		if (self->mat == NULL) {
			return -2;
		}
		else {
			for (i = 0; i < self->dim1; i++) {
				if (self->mat[i] == NULL) {
					return -3;
				}
			}
			return 0;
		}
	}
}


void fillInMatrix(Matrix_t *self, int value) {
	unsigned int i, j;

	if (!errorsInMatrix(self)) {
		for (i = 0; i < self->dim1; i++) {
			for (j = 0; j < self->dim2; j++) {
				self->mat[i][j] = value;
			}
		}
	}
}

void printMatrix(Matrix_t *self) {
	unsigned int i, j;

	if (!errorsInMatrix(self)) {
		printf("\n");
		for (i = 0; i < self->dim1; i++) {
			for (j = 0; j < self->dim2; j++) {
				printf("%d ", self->mat[i][j]);
			}
			printf("\n");
		}
	}
}

int setMat(Matrix_t *self, unsigned int i, unsigned int j, int value) {

	if (!errorsInMatrix(self)) {
		if (i < self->dim1 && j < self->dim2) {
			self->mat[i][j] = value;
			return 0;
		}
		else {
			return -1;
		}
	}
	else {
		return -2;
	}
}

int setDim1(Matrix_t *self, unsigned int dim1) {

	if (!errorsInMatrix(self)) {
		self->dim1 = dim1;
		return 0;
	}
	else {
		return -1;
	}
}

int setDim2(Matrix_t *self, unsigned int dim2) {

	if (!errorsInMatrix(self)) {
		self->dim2 = dim2;
		return 0;
	}
	else {
		return -1;
	}
}

int getMat(Matrix_t *self, unsigned int i, unsigned int j, int *value) {

	if (!errorsInMatrix(self)) {
		if (i < self->dim1 && j < self->dim2) {
			*value = self->mat[i][j];
			return 0;
		}
		else {
			return -1;
		}
	}
	else {
		return -2;
	}
}

int getDim1(Matrix_t *self, unsigned int *dim1) {

	if (!errorsInMatrix(self)) {
		*dim1 = self->dim1;
		return 0;
	}
	else {
		return -1;
	}
}

int getDim2(Matrix_t *self, unsigned int *dim2) {

	if (!errorsInMatrix(self)) {
		*dim2 = self->dim2;
		return 0;
	}
	else {
		return -1;
	}
}

int pushCell(Matrix_t *self, unsigned int i, unsigned int j) {
	int value;

	if (!getMat(self, i, j, &value)) {
		if (!value) {
			pushCell(self, i - 1, j);
			pushCell(self, i + 1, j);
			pushCell(self, i, j - 1);
			pushCell(self, i, j + 1);
			return value;
		}
		else {
			return value;
		}
	}
	else {
		return -1;
	}

}

int countSurroundingMines(Matrix_t *self, unsigned int i, unsigned int j) {
	int count = 0, value;

	if (!errorsInMatrix(self)) {
		if (!getMat(self, i - 1, j - 1, &value)) {
			if (value == 10) {
				count++;
			}
		}
		if (!getMat(self, i - 1, j, &value)) {
			if (value == 10) {
				count++;
			}
		}
		if (!getMat(self, i - 1, j + 1, &value)) {
			if (value == 10) {
				count++;
			}
		}
		if (!getMat(self, i, j - 1, &value)) {
			if (value == 10) {
				count++;
			}
		}
		if (!getMat(self, i, j + 1, &value)) {
			if (value == 10) {
				count++;
			}
		}
		if (!getMat(self, i + 1, j - 1, &value)) {
			if (value == 10) {
				count++;
			}
		}
		if (!getMat(self, i + 1, j, &value)) {
			if (value == 10) {
				count++;
			}
		}
		if (!getMat(self, i + 1, j + 1, &value)) {
			if (value == 10) {
				count++;
			}
		}
		return count;
	}
	else {
		return -1;
	}
}

int setInternalMatrix(Matrix_t *self) {
	unsigned int i, j;
	int value;

	if (!errorsInMatrix(self)) {
		for (i = 0; i < self->dim1; i++) {
			for (j = 0; j < self->dim2; j++) {
				if (!getMat(self, i, j, &value)) {
					if (value == 0) {
						self->mat[i][j] = countSurroundingMines(self, i, j);
					}
				}
			}
		}
	return 0;
	}
	else {
		return -1;
	}
}

int main () {
	Matrix_t *self;
	unsigned int dimension1 = 10, dimension2 = 10;

	printf("Number of rows:");
	fflush(0);
	scanf("%d", &dimension1);
	printf("Number of columns:");
	fflush(0);
	scanf("%d", &dimension2);

	self = MatrixWithDimensions(dimension1, dimension2);

	printMatrix(self);
	destroyMatrix(self);

	return 0;
}
