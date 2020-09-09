#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned char size;
  unsigned char *ids;
} InputElements;

typedef struct {
  unsigned char index_map[50];
  unsigned char reverse_map[50];
  bool *links;
} AdjacencyMatrix;

typedef struct RL {
  struct RL *previous;
  struct {
	unsigned char x, y;
  } node;
} ReverseList;

InputElements readElements();
AdjacencyMatrix readLinks(InputElements);

bool checkReflexive(unsigned char, AdjacencyMatrix);

unsigned short index2D(unsigned char, unsigned char, unsigned char);
ReverseList *appendPairs(ReverseList *, unsigned char, unsigned char);
void printPairs(ReverseList *);
void freePairs(ReverseList *);
void printResult(char *, bool);

int main() {
  const InputElements inputs = readElements();
  const AdjacencyMatrix matrix = readLinks(inputs);

  const bool reflexive = checkReflexive(inputs.size, matrix);

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
  unsigned char x, y;
  matrix.links = calloc(elements.size * elements.size, sizeof(bool));

  for (unsigned char i = 0; i < elements.size; ++i) {
	matrix.index_map[elements.ids[i]] = i;
	matrix.reverse_map[i] = elements.ids[i];
  }

  while (scanf("%hhu %hhu", &x, &y) == 2)
	matrix.links[index2D(elements.size, matrix.index_map[x], matrix.index_map[y])] = true;

  return matrix;
}

bool checkReflexive(unsigned char size, AdjacencyMatrix matrix) {
  bool reflexive = true;
  ReverseList *pairs_present = NULL;
  ReverseList *pairs_absent = NULL;

  for (int i = 0; i < size; ++i) {
	bool pair_valid = matrix.links[index2D(size, i, i)];

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

unsigned short index2D(unsigned char size, unsigned char line, unsigned char column) {
  return line * size + column;
}

ReverseList *appendPairs(ReverseList *base, unsigned char x, unsigned char y) {
  ReverseList *new_pair = malloc(sizeof(ReverseList));
  new_pair->node.x = x;
  new_pair->node.y = y;
  new_pair->previous = base;

  return new_pair;
}

void printPairs(ReverseList *list) {
  while (list != NULL) {
	printf("(%hhu,%hhu);", list->node.x, list->node.y);

	if (list->previous != NULL)
	  putchar(' ');

	list = list->previous;
  }
  putchar('\n');
}

void freePairs(ReverseList *list) {
  while (list != NULL) {
	ReverseList *top = list;
	list = list->previous;
	free(top);
  }
}

void printResult(char *property, bool valid) {
  printf("%s: %c\n", property, valid ? 'V' : 'F');
}