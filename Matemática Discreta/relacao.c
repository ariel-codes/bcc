#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
bool checkReflexive(const AdjacencyMatrix*);
bool checkSymmetric(const AdjacencyMatrix*);
bool checkAntiSymmetric(const AdjacencyMatrix*);
bool checkAsymmetric(const AdjacencyMatrix*);
bool checkTransitive(const AdjacencyMatrix*);
bool checkEquivalence(bool, bool, bool);
bool checkPartialOrder(bool, bool, bool);
void generateTransitiveClosure(const AdjacencyMatrix*);

// Input
InputElements readElements();
AdjacencyMatrix readLinks(InputElements);

// Utilidades
AdjacencyMatrix initializeMatrix(m_size, m_size *);
m_size findLabelIndex(const AdjacencyMatrix*, m_size);
unsigned short index2D(m_size, m_size, m_size);
void printPairs(const AdjacencyMatrix*);
void printResult(char *, bool);

// Implementações
int main() {
  const InputElements inputs = readElements();
  const AdjacencyMatrix matrix = readLinks(inputs);
  free(inputs.ids);

  const bool reflexive = checkReflexive(&matrix);
  const bool symmetric = checkSymmetric(&matrix);
  const bool anti_symmetric = checkAntiSymmetric(&matrix);
  checkAsymmetric(&matrix);
  const bool transitive = checkTransitive(&matrix);
  checkEquivalence(reflexive, symmetric, transitive);
  checkPartialOrder(reflexive, transitive, anti_symmetric);
  generateTransitiveClosure(&matrix);

  free(matrix.links);
  free(matrix.index_map);
  return 0;
}

bool checkReflexive(const AdjacencyMatrix *matrix) {
  bool reflexive = true;
  bool irreflexive = true;
  AdjacencyMatrix pairs_present = initializeMatrix(matrix->size, matrix->index_map),
	  pairs_absent = initializeMatrix(matrix->size, matrix->index_map);

  for (m_size i = 0; i < matrix->size; ++i) {
	const unsigned short index = index2D(matrix->size, i, i);

	const bool pair_valid = matrix->links[index];

	if (pair_valid) {
	  irreflexive = false;
	  pairs_present.links[index] = true;
	} else {
	  reflexive = false;
	  pairs_absent.links[index] = true;
	}
  }

  printResult("Reflexiva", reflexive);
  if (!reflexive) printPairs(&pairs_absent);

  printResult("Irreflexiva", irreflexive);
  if (!irreflexive) printPairs(&pairs_present);

  free(pairs_present.links);
  free(pairs_absent.links);

  return reflexive;
}

bool checkSymmetric(const AdjacencyMatrix* matrix) {
  bool symmetric = true;
  AdjacencyMatrix pairs_absent = initializeMatrix(matrix->size, matrix->index_map);

  for (m_size i = 0; i < matrix->size; ++i) {
	for (m_size k = 0; k < i; ++k) {
	  const unsigned short index_top = index2D(matrix->size, i, k),
		  index_bottom = index2D(matrix->size, k, i);

	  if (matrix->links[index_top] == matrix->links[index_bottom]) continue;

	  symmetric = false;
	  if (matrix->links[index_bottom])
		pairs_absent.links[index_top] = true;
	  else
		pairs_absent.links[index_bottom] = true;
	}
  }

  printResult("Simétrica", symmetric);
  if (!symmetric) printPairs(&pairs_absent);

  free(pairs_absent.links);

  return symmetric;
}

bool checkAntiSymmetric(const AdjacencyMatrix* matrix) {
  bool anti_symmetric = true;
  AdjacencyMatrix pairs_present = initializeMatrix(matrix->size, matrix->index_map);

  for (m_size i = 0; i < matrix->size; ++i) {
	for (m_size k = 0; k < i; ++k) {
	  const unsigned short index_top = index2D(matrix->size, i, k),
		  index_bottom = index2D(matrix->size, k, i);

	  if (!(matrix->links[index_top] && matrix->links[index_bottom])) continue;

	  anti_symmetric = false;
	  pairs_present.links[index_top] = true;
	  pairs_present.links[index_bottom] = true;
	}
  }

  printResult("Anti-simétrica", anti_symmetric);
  if (!anti_symmetric) printPairs(&pairs_present);

  free(pairs_present.links);

  return anti_symmetric;
}

bool checkAsymmetric(const AdjacencyMatrix* matrix) {
  bool asymmetric = true;

  for (m_size i = 0; i < matrix->size; ++i) {
	for (m_size k = 0; k < matrix->size; ++k) {
	  asymmetric &= matrix->links[index2D(matrix->size, i, k)] != matrix->links[index2D(matrix->size, k, i)];
	}
  }

  printResult("Assimétrica", asymmetric);

  return asymmetric;
}

bool checkTransitive(const AdjacencyMatrix* matrix) {
  bool transitive = true;
  AdjacencyMatrix pairs_absent = initializeMatrix(matrix->size, matrix->index_map);

  for (m_size i = 0; i < matrix->size; ++i) {
	for (m_size k = 0; k < matrix->size; ++k) {
	  if (i == k) continue;

	  if (matrix->links[index2D(matrix->size, i, k)]) {
		for (m_size j = 0; j < matrix->size; ++j) {
		  if (k == j) continue;

		  const unsigned short index = index2D(matrix->size, i, j);

		  if (matrix->links[index2D(matrix->size, k, j)] && !matrix->links[index]) {
			transitive = false;
			pairs_absent.links[index] = true;
		  }
		}
	  }
	}
  }

  printResult("Transitiva", transitive);
  if (!transitive) printPairs(&pairs_absent);

  free(pairs_absent.links);

  return transitive;
}

bool checkEquivalence(bool reflexive, bool symmetric, bool transitive) {
  const bool equivalent = reflexive && symmetric && transitive;
  printResult("Relação de equivalência", equivalent);
  return equivalent;
}

bool checkPartialOrder(bool reflexive, bool transitive, bool anti_symmetric) {
  const bool partial_ordering = reflexive && anti_symmetric && transitive;
  printResult("Relação de ordem parcial", partial_ordering);
  return partial_ordering;
}

void generateTransitiveClosure(const AdjacencyMatrix* matrix) {
  AdjacencyMatrix closure = initializeMatrix(matrix->size, matrix->index_map);
  memcpy(closure.links, matrix->links, matrix->size * matrix->size * sizeof(bool));

  for (m_size i = 0; i < closure.size; ++i) {
	for (m_size k = 0; k < closure.size; ++k) {
	  for (m_size j = 0; j < closure.size; ++j) {
		const unsigned short index = index2D(closure.size, k, j);
		closure.links[index] = closure.links[index]
			|| (closure.links[index2D(closure.size, k, i)] && closure.links[index2D(closure.size, i, j)]);
	  }
	}
  }

  printf("Fecho transitivo da relação: ");
  printPairs(&closure);

  free(closure.links);
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
	m_size x_index = findLabelIndex(&matrix, x),
		y_index = findLabelIndex(&matrix, y);
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

m_size findLabelIndex(const AdjacencyMatrix* matrix, m_size label) {
  for (m_size i = 0; i < matrix->size; ++i) {
	if (matrix->index_map[i] == label) {
	  return i;
	}
  }
}

unsigned short index2D(m_size size, m_size line, m_size column) {
  return (line * size) + column;
}

void printPairs(const AdjacencyMatrix* matrix) {
  bool first = true;

  for (m_size i = 0; i < matrix->size; ++i) {
	const m_size i_label = matrix->index_map[i];

	for (m_size k = 0; k < matrix->size; ++k) {
	  const m_size k_label = matrix->index_map[k];

	  if (matrix->links[index2D(matrix->size, i, k)]) {
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