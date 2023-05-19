/*
 * Minesweeper.c
 *
 *  Created on: 17 may 2023
 *      Author: nakal
 */


#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char value, visible;
}Cell_t;

typedef struct {
	Cell_t **mat;
	unsigned int dim1, dim2, mines;
}Board_t;

Cell_t* Cell_c1(char value, char visible) {

	//Creates a cell, sets its values and returns a pointer to it.

	Cell_t *self;

	self = malloc(sizeof(Cell_t));
	self->value = value;
	self->visible = visible;

	return self;
}

void Cell_d1(Cell_t *self) {

	//Destroys a cell.

	free(self);
}

Board_t* Board_c1(unsigned int dim1, unsigned int dim2, unsigned int mines, int seed) {

	//Creates a board, sets its values to zero, then randomly sets the mines and returns a pointer to the board.

	Board_t *self;
	unsigned int i, j;

	self = (Board_t*)malloc(sizeof(Board_t));
	if (self == NULL) {
		return NULL;
	}

	self->dim1 = dim1;
	self->dim2 = dim2;
	self->mat = malloc(dim1 * sizeof(Cell_t*));
	if (self->mat == NULL) {
		return NULL;
	}

	for (i = 0; i < self->dim1; i++) {
		self->mat[i] = malloc(self->dim2 * sizeof(Cell_t));
		if (self->mat[i] == NULL) {
			for (j = 0; j < i; j++) {
				free(self->mat[j]);
			}
			return NULL;
		}
		for (j = 0; j < self->dim2; j++) {
			self->mat[i][j].value = '0';
			self->mat[i][j].visible = '0';
		}
	}

	for (i = 0; i < mines; i++) {
		srand(i + seed);
		self->mat[rand() % self->dim1][rand() % self->dim2].value = '9';
	}
	//TODO implement the option where there is already a mine on the spot where it decides to plant one.

	return self;

}

void Board_d1(Board_t *self){

	//Destroys a board.

	unsigned int i;

	if (self != NULL) {
		for (i = 0; i < self->dim1; i++) {
			free(self->mat[i]);
		}
		free(self->mat);
	}

	free(self);
}

int errorsInBoard(Board_t *self) {
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

int checkMine(unsigned int i, unsigned int j, Board_t *self) {

	//Check if there is a mine in the selected cell. Return 0 if not, 1 if yes and a negative value if there are any errors.

	if (!errorsInBoard(self)) {
		if (self->mat[i][j].value == '9') {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return -1;
	}
}

void setCell(Board_t *self, unsigned int i, unsigned int j, char value, char visible) {

	//Sets the values of a cell inside a board.

	if (!errorsInBoard(self)) {
		if (i < self->dim1 && j < self->dim2) {
			self->mat[i][j].value = value;
			self->mat[i][j].visible = visible;
		}
	}
}

char getCellValue(Cell_t *self) {

	//Returns cell's value.

	//if (self != NULL) {
		return self->value;

}

char getCellVisible(Cell_t *self) {

	//Return cell's visible' value.

	return self->visible;
}

void printBoard(Board_t *self) {

	//Prints a board.

	unsigned int i, j;

	if (!errorsInBoard(self)) {
		printf("  ");
		for (i = 0; i < self->dim1; i++) {
			printf("%d ", i);
		}
		printf("\n");
		for (i = 0; i < self->dim1; i++) {
			printf("%d ", i);
			for (j = 0; j < self->dim2; j++) {
				printf("%c ", self->mat[i][j].value);
			}
			printf("\n");
		}
	}
}

void setBoard(Board_t *self) {

	//Sets the values of cells which have a mine nearby.

	unsigned int i, j;

	if (!errorsInBoard(self)) {
		for (i = 0; i < self->dim1; i++) {
			for (j = 0; j < self->dim2; j++) {
				if (self->mat[i][j].value == '9') {
					//todo setCell(self, i - 1, j - 1, (char)((self->mat[i - 1][j - 1])
				}

			}
			printf("\n");
		}
	}

}

int main() {

	Board_t *self;

	self = Board_c1(10, 10, 15, -5000);
	printBoard(self);
	Board_d1(self);


	return 0;
}

