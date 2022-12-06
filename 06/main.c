#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#if 1
#define FILE_NAME "input.txt"
#else
#define FILE_NAME "sample.txt"
#endif

#define CAP 4096

int solve(char *str, int key_len) {
  int l = strlen(str);

  int i, j, k;
  bool ok = false;
  for (i = 0; i < l - key_len && !ok; ++i) {
    ok = true;
    for (j = i; j < i + key_len - 1; ++j) {
      for (k = j + 1; k < i + key_len && ok; ++k) {
        if (str[j] == str[k]) {
          ok = false;
        }
      }
    }
  }

  return i + key_len - 1;
}

void part1() {
  FILE *fp = fopen(FILE_NAME, "r");

  char str[CAP];
  while (fscanf(fp, "%s", str) > 0) {
    printf("Part 1: %d\n", solve(str, 4));
  }

  fclose(fp);
}

void part2() {
  FILE *fp = fopen(FILE_NAME, "r");

  char str[CAP];
  while (fscanf(fp, "%s", str) > 0) {
    printf("Part 2: %d\n", solve(str, 14));
  }

  fclose(fp);
}

int main(void) {
  part1();
  part2();
  return 0;
}
