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
  m_size index_map[50];
  m_size reverse_map[50];
  bool *links;
} AdjacencyMatrix;

typedef struct ListStruct {
  struct ListStruct *previous;
  struct {
	m_size x, y;
  } node;
} List;

// Input
InputElements readElements();
AdjacencyMatrix readLinks(InputElements);

// Verificadores
bool checkReflexive(m_size, AdjacencyMatrix);
bool checkSymmetric(m_size, AdjacencyMatrix);
void checkAsymmetric(bool, bool);

// Utilidades
unsigned short index2D(m_size, m_size, m_size);
List *appendPairs(List *, m_size, m_size);
void printPairs(List *);
void freePairs(List *);
void printResult(char *, bool);

// Implementações
int main() {
  const InputElements inputs = readElements();
  const AdjacencyMatrix matrix = readLinks(inputs);

  const bool reflexive = checkReflexive(inputs.size, matrix);
  const bool symmetric = checkSymmetric(inputs.size, matrix);
  checkAsymmetric(reflexive, symmetric);

  free(inputs.ids);
  free(matrix.links);
  return 0;
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
  AdjacencyMatrix matrix;
  m_size x, y;
  matrix.links = calloc(elements.size * elements.size, sizeof(bool));

  for (m_size i = 0; i < elements.size; ++i) {
	matrix.index_map[elements.ids[i]] = i;
	matrix.reverse_map[i] = elements.ids[i];
  }

  while (scanf("%hhu %hhu", &x, &y) == 2)
	matrix.links[index2D(elements.size, matrix.index_map[x], matrix.index_map[y])] = true;

  return matrix;
}

bool checkReflexive(m_size size, AdjacencyMatrix matrix) {
  bool reflexive = true;
  List *pairs_present = NULL;
  List *pairs_absent = NULL;

  for (int i = 0; i < size; ++i) {
	const bool pair_valid = matrix.links[index2D(size, i, i)];

	reflexive &= pair_valid;

	if (pair_valid) {
	  pairs_present = appendPairs(pairs_present, matrix.reverse_map[i], matrix.reverse_map[i]);
	} else {
	  pairs_absent = appendPairs(pairs_absent, matrix.reverse_map[i], matrix.reverse_map[i]);
	}
  }

  printResult("Reflexiva", reflexive);
  if (!reflexive) printPairs(pairs_absent);

  printResult("Irreflexiva", !reflexive);
  if (reflexive) printPairs(pairs_present);

  freePairs(pairs_present);
  freePairs(pairs_absent);

  return reflexive;
}

bool checkSymmetric(m_size size, AdjacencyMatrix matrix) {
  bool symmetric = true;
  List *pairs_present = NULL;
  List *pairs_absent = NULL;

  for (int i = 0; i < size; ++i) {
	for (int k = 0; k < i; ++k) {
	  const bool pair_valid = matrix.links[index2D(size, i, k)] == matrix.links[index2D(size, k, i)];
	  symmetric &= pair_valid;

	  if (pair_valid && matrix.links[index2D(size, i, k)] && matrix.links[index2D(size, k, i)]) {
		pairs_present = appendPairs(pairs_present, matrix.reverse_map[i], matrix.reverse_map[k]);
		pairs_present = appendPairs(pairs_present, matrix.reverse_map[k], matrix.reverse_map[i]);
	  } else if (matrix.links[index2D(size, i, k)])
		pairs_absent = appendPairs(pairs_absent, matrix.reverse_map[i], matrix.reverse_map[k]);
	  else if (matrix.links[index2D(size, k, i)])
		pairs_absent = appendPairs(pairs_absent, matrix.reverse_map[k], matrix.reverse_map[i]);
	}
  }

  printResult("Simétrica", symmetric);
  if (!symmetric) printPairs(pairs_absent);

  printResult("Anti-simétrica", !symmetric);
  if (symmetric) printPairs(pairs_present);

  freePairs(pairs_present);
  freePairs(pairs_absent);

  return symmetric;
}

void checkAsymmetric(bool is_reflexive, bool is_symmetric) {
  printResult("Assimétrica", !is_reflexive && !is_symmetric);
}

unsigned short index2D(m_size size, m_size line, m_size column) {
  return line * size + column;
}

List *appendPairs(List *base, m_size x, m_size y) {
  List *new_pair = malloc(sizeof(List));
  new_pair->node.x = x;
  new_pair->node.y = y;
  new_pair->previous = base;

  return new_pair;
}

void printPairs(List *list) {
  while (list != NULL) {
	printf("(%hhu,%hhu);", list->node.x, list->node.y);

	if (list->previous != NULL)
	  putchar(' ');

	list = list->previous;
  }
  putchar('\n');
}

void freePairs(List *list) {
  while (list != NULL) {
	List *top = list;
	list = list->previous;
	free(top);
  }
}

void printResult(char *property, bool valid) {
  printf("%s: %c\n", property, valid ? 'V' : 'F');
}