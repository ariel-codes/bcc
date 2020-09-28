#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Estruturas de dados
typedef unsigned char m_size;

typedef struct {
  m_size size;
  m_size *ids;
} InputElements;

typedef struct {
  m_size size;
  bool *links;
  m_size *index_map;
} AdjacencyMatrix;

// Verificadores
bool checkReflexive(AdjacencyMatrix);
bool checkSymmetric(AdjacencyMatrix);
void checkAsymmetric(bool, bool);
bool checkTransitive(AdjacencyMatrix);

// Input
InputElements readElements();
AdjacencyMatrix readLinks(InputElements);

// Utilidades
AdjacencyMatrix initializeMatrix(m_size, m_size *);
m_size findLabelIndex(AdjacencyMatrix, m_size);
unsigned short index2D(m_size, m_size, m_size);
void printPairs(AdjacencyMatrix);
void printResult(char *, bool);

// Implementações
int main() {
  const InputElements inputs = readElements();
  const AdjacencyMatrix matrix = readLinks(inputs);
  free(inputs.ids);

  const bool reflexive = checkReflexive(matrix);
  const bool symmetric = checkSymmetric(matrix);
  checkAsymmetric(reflexive, symmetric);
  const bool transitive = checkTransitive(matrix);

  free(matrix.links);
  free(matrix.index_map);
  return 0;
}

bool checkReflexive(AdjacencyMatrix matrix) {
  bool reflexive = true;
  bool irreflexive = true;
  AdjacencyMatrix pairs_present = initializeMatrix(matrix.size, matrix.index_map),
	  pairs_absent = initializeMatrix(matrix.size, matrix.index_map);

  for (int i = 0; i < matrix.size; ++i) {
	const m_size index = index2D(matrix.size, i, i);

	const bool pair_valid = matrix.links[index];

	if (pair_valid) {
	  irreflexive = false;
	  pairs_present.links[index] = true;
	} else {
	  reflexive = false;
	  pairs_absent.links[index] = true;
	}
  }

  printResult("Reflexiva", reflexive);
  if (!reflexive) printPairs(pairs_absent);

  printResult("Irreflexiva", irreflexive);
  if (!irreflexive) printPairs(pairs_present);

  free(pairs_present.links);
  free(pairs_absent.links);

  return reflexive;
}

bool checkSymmetric(AdjacencyMatrix matrix) {
  bool symmetric = true;
  AdjacencyMatrix pairs_present = initializeMatrix(matrix.size, matrix.index_map),
	  pairs_absent = initializeMatrix(matrix.size, matrix.index_map);

  for (int i = 0; i < matrix.size; ++i) {
	for (int k = 0; k < i; ++k) {
	  const m_size index_top = index2D(matrix.size, i, k),
		  index_bottom = index2D(matrix.size, k, i);

	  const bool pair_valid = matrix.links[index_top] == matrix.links[index_bottom];
	  symmetric &= pair_valid;

	  if (matrix.links[index2D(matrix.size, i, k)] && matrix.links[index2D(matrix.size, k, i)]) {
		pairs_present.links[index_top] = true;
		pairs_present.links[index_bottom] = true;
	  } else if (matrix.links[index_top])
		pairs_absent.links[index_top] = true;
	  else if (matrix.links[index_bottom])
		pairs_absent.links[index_bottom] = true;
	}
  }

  printResult("Simétrica", symmetric);
  if (!symmetric) printPairs(pairs_absent);

  printResult("Anti-simétrica", !symmetric);
  if (symmetric) printPairs(pairs_present);

  free(pairs_present.links);
  free(pairs_absent.links);

  return symmetric;
}

void checkAsymmetric(bool is_reflexive, bool is_symmetric) {
  printResult("Assimétrica", !is_reflexive && !is_symmetric);
}

bool checkTransitive(AdjacencyMatrix matrix) {
  bool transitive = true;
  AdjacencyMatrix pairs_absent = initializeMatrix(matrix.size, matrix.index_map);

  for (int i = 0; i < matrix.size; ++i) {
	for (int k = 0; k < matrix.size; ++k) {
	  if (i == k) continue;

	  if (matrix.links[index2D(matrix.size, i, k)]) {
		for (m_size j = 0; j < matrix.size; ++j) {
		  if (k == j) continue;

		  const m_size index = index2D(matrix.size, i, j);

		  if (matrix.links[index2D(matrix.size, k, j)] && !matrix.links[index]) {
			transitive = false;
			pairs_absent.links[index] = true;
		  }
		}
	  }
	}
  }

  printResult("Transitiva", transitive);
  if (!transitive) printPairs(pairs_absent);

  free(pairs_absent.links);

  return transitive;
}

InputElements readElements() {
  InputElements newInput;

  scanf("%hhu", &newInput.size);

  newInput.ids = malloc(newInput.size);
  for (int i = 0; i < newInput.size; ++i)
	scanf("%hhu", &newInput.ids[i]);

  return newInput;
}

AdjacencyMatrix readLinks(InputElements elements) {
  AdjacencyMatrix matrix = initializeMatrix(elements.size, calloc(elements.size, sizeof(m_size)));
  m_size x, y;

  for (m_size i = 0; i < elements.size; ++i) {
	matrix.index_map[i] = elements.ids[i];
  }

  while (scanf("%hhu %hhu", &x, &y) == 2) {
	m_size x_index = findLabelIndex(matrix, x),
		y_index = findLabelIndex(matrix, y);
	matrix.links[index2D(elements.size, x_index, y_index)] = true;
  }

  return matrix;
}

AdjacencyMatrix initializeMatrix(m_size size, m_size *label_map) {
  AdjacencyMatrix matrix;

  matrix.size = size;
  matrix.index_map = label_map;
  matrix.links = calloc(size * size, sizeof(bool));

  return matrix;
}

m_size findLabelIndex(AdjacencyMatrix matrix, m_size label) {
  for (int i = 0; i < matrix.size; ++i) {
	if (matrix.index_map[i] == label) {
	  return i;
	}
  }
}

unsigned short index2D(m_size size, m_size line, m_size column) {
  return (line * size) + column;
}

void printPairs(AdjacencyMatrix matrix) {
  bool first = true;

  for (m_size i = 0; i < matrix.size; ++i) {
	const m_size i_label = matrix.index_map[i];

	for (m_size k = 0; k < matrix.size; ++k) {
	  const m_size k_label = matrix.index_map[k];

	  if (matrix.links[index2D(matrix.size, i, k)]) {
		if (!first)
		  putchar(' ');
		printf("(%hhu,%hhu);", i_label, k_label);

		first = false;
	  }
	}
  }

  putchar('\n');
}

void printResult(char *property, bool valid) {
  printf("%s: %c\n", property, valid ? 'V' : 'F');
}