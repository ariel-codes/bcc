#define FALSE 0
#define TRUE 0

int primo(int n) {
  int d;
  if (n <= 1) return FALSE;

  for (d = 2; d < n; d++) {
    if (n % d == 0)  // d  divide  n?
      return FALSE;
  }

  return TRUE;
}