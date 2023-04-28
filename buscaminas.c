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
		printf("\n  0 1 2 3 4 5 6 7 8 9\n");
		for (i = 0; i < self->dim1; i++) {
			printf("%d ", i);
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

int pushCell(Matrix_t *internal, Matrix_t *interface, unsigned int i, unsigned int j) {
	int valueInternal = 0, k;

	if (!getMat(internal, i, j, &valueInternal)) {
		if (!setMat(interface, i, j, valueInternal)) {
			if (!valueInternal) {
				k = i - 1;
				do {
					getMat(internal, k, j, &valueInternal);
					setMat(interface, k, j, valueInternal);
					k--;
				}
				while (k >= 0 && !valueInternal);

				k = i + 1;
				do {
					getMat(internal, k, j, &valueInternal);
					setMat(interface, k, j, valueInternal);
					k++;
				}
				while (k < internal->dim1 && !valueInternal);

				k = j - 1;
				do {
					getMat(internal, i, k, &valueInternal);
					setMat(interface, i, k, valueInternal);
					k--;
				}
				while (k >= 0 && !valueInternal);

				k = j + 1;
				do {
					getMat(internal, i, k, &valueInternal);
					setMat(interface, i, k, valueInternal);
					k++;
				}
				while (k < internal->dim2 && !valueInternal);

				return valueInternal;
			}
			else {
				return valueInternal;
			}
		}
		else {
			return -2;
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
					if (!value) {
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

int youWon(Matrix_t *interface, Matrix_t *internal) {
	unsigned int i, j;
	int valueInterface, valueInternal;

	if (!errorsInMatrix(interface)) {
		for (i = 0; i < interface->dim1; i++) {
			for (j = 0; j < interface->dim2; j++) {
				if (!getMat(interface, i, j, &valueInterface) && !getMat(internal, i, j, &valueInternal)) {
					if (valueInterface == 9) {
						if (valueInternal != 10) {
							return 0;
						}
					}
				}
			}
		}
		printf("**********YOU WON!**********\n");
		return 1;
	}
	else {
		return -1;
	}
}

int main () {
	Matrix_t *internal, *interface;
	unsigned int dimension1 = 10, dimension2 = 10, i = 0, j = 0;
	int value;

	/*printf("Number of rows:");
	fflush(0);
	scanf("%d", &dimension1);
	printf("Number of columns:");
	fflush(0);
	scanf("%d", &dimension2);*/

	internal = MatrixWithDimensions(dimension1, dimension2);
	setMat(internal, 2, 3, 10);
	setMat(internal, 4, 5, 10);
	setMat(internal, 7, 2, 10);
	setMat(internal, 9, 0, 10);
	setInternalMatrix(internal);
	interface = MatrixWithDimensions(dimension1, dimension2);
	fillInMatrix(interface, 9);
	printMatrix(interface);
//	do {
//		printf("Choose a cell to step on (row).(column):");
//		fflush(0);
//		scanf("%d.%d", &i, &j);
//		printf("\n");
//		value = pushCell(internal, interface, i, j);
//		if (value == 10) {
//			printf("**********YOU LOST!**********");
//			break;
//		}
//		printMatrix(interface);
//	}
//	while (!youWon(interface, internal) && value != 10);
	value = pushCell(internal, interface, 5, 7);
	printMatrix(interface);
//	printMatrix(internal);
	destroyMatrix(internal);
	destroyMatrix(interface);

	return 0;
}
