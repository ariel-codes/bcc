#include <Base.h>

int main(__unused int argc, char *argv[]) {
  Base base(argv[1]);
  base.parseCommands(argv[2]);
  base.printResult();
  return 0;
}

