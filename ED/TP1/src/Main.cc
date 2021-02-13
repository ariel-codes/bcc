
#include <Base.h>

int main(int argc, char *argv[]) {
  Base base(argv[1]);
  base.parseCommands(argv[2]);
  base.printResult();
  return 0;
}

