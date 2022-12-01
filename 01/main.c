#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#if 1
#define FILE_NAME "input.txt"
#else
#define FILE_NAME "sample.txt"
#endif

void part1() {
  FILE* fp = fopen(FILE_NAME, "r");

  int max_cals = 0, cals = 0, cal;

  char* line = NULL;
  size_t len = 0;

  while (getline(&line, &len, fp) != EOF) {
    cal = atoi(line);

    if (cal == 0) {
      max_cals = fmax(max_cals, cals);
      cals = 0;
      continue;
    }

    cals += cal;
  }

  max_cals = fmax(max_cals, cals);

  printf("Part 1: %d\n", max_cals);
}

void sort(int* arr, int sz) {
  for (int i = 1; i < sz; ++i) {
    int x = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > arr[i]) {
      arr[j + 1] = arr[j];
      j--;
    }

    arr[j + 1] = x;
  }
}

void part2() {
  FILE* fp = fopen(FILE_NAME, "r");

  int top[3] = {0};
  int cal, cals = 0;

  char* line = NULL;
  size_t len = 0;

  while (getline(&line, &len, fp) != EOF) {
    cal = atoi(line);

    if (cal == 0) {
      if (cals > top[0]) {
        top[0] = cals;
        sort(top, 3);
      }

      cals = 0;
      continue;
    }

    cals += cal;
  }

  if (cals > top[0]) top[0] = cals;

  printf("Part 2: %d\n", top[0] + top[1] + top[2]);
}

int main(void) {
  part1();
  part2();

  return 0;
}
