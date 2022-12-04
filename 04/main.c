#include <stdio.h>

#if 1
#define FILE_NAME "input.txt"
#else
#define FILE_NAME "sample.txt"
#endif

void part1() {
  FILE *fp = fopen(FILE_NAME, "r");

  int x1, x2, y1, y2, ans = 0;

  while (fscanf(fp, "%d-%d,%d-%d", &x1, &x2, &y1, &y2) == 4) {
    ans += (x1 >= y1 && x2 <= y2) || (y1 >= x1 && y2 <= x2);
  }

  printf("Part 1: %d\n", ans);

  fclose(fp);
}

void part2() {
  FILE *fp = fopen(FILE_NAME, "r");

  int x1, x2, y1, y2, ans = 0;

  while (fscanf(fp, "%d-%d,%d-%d", &x1, &x2, &y1, &y2) == 4) {
    ans += (x1 >= y1 && x1 <= y2) || (y1 >= x1 && y1 <= x2);
  }

  printf("Part 2: %d\n", ans);

  fclose(fp);
}

int main(void) {
  part1();
  part2();
  return 0;
}
