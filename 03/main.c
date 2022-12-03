#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#if 1
#define FILE_NAME "input.txt"
#else
#define FILE_NAME "sample.txt"
#endif

#define CAP 50

// Sadly there are no sets in C

void part1() {
  FILE *fp = fopen(FILE_NAME, "r");

  char str[CAP];

  int sum = 0;

  while (fscanf(fp, "%s", str) > 0) {
    size_t l = strlen(str);
    char used_chars[CAP / 2];
    size_t used_chars_l = 0;
    memset(used_chars, 0, sizeof(used_chars));

    for (size_t i = 0; i < l / 2; ++i) {
      size_t j;
      bool used = false;

      for (j = 0; j < used_chars_l && !used; ++j) {
        if (str[i] == used_chars[j]) used = true;
      }

      if (used) continue;

      for (j = l / 2; j < l; ++j) {
        if (str[i] == str[j]) {
          used_chars[used_chars_l++] = str[i];

          if (str[i] >= 'a') {
            sum += str[i] - 'a' + 1;
          } else {
            sum += str[i] - 'A' + 27;
          }
          break;
        }
      }
    }
  }

  printf("Part 1: %d\n", sum);

  fclose(fp);
}

void part2() {
  FILE *fp = fopen(FILE_NAME, "r");

  char elf1[CAP];
  char elf2[CAP];
  char elf3[CAP];

  size_t i, j, k;

  int sum = 0;

  while (fscanf(fp, "%s\n%s\n%s", elf1, elf2, elf3) > 0) {
    size_t elf1_l = strlen(elf1), elf2_l = strlen(elf2), elf3_l = strlen(elf3);

    bool found = false;

    for (i = 0; i < elf1_l && !found; ++i) {
      for (j = 0; j < elf2_l && !found; ++j) {
        if (elf1[i] == elf2[j]) {
          for (k = 0; k < elf3_l && !found; ++k) {
            if (elf1[i] == elf3[k]) {
              found = true;

              if (elf1[i] >= 'a') {
                sum += elf1[i] - 'a' + 1;
              } else {
                sum += elf1[i] - 'A' + 27;
              }
            }
          }
        }
      }
    }
  }

  printf("Part 2: %d\n", sum);

  fclose(fp);
}

int main(void) {
  part1();
  part2();
  return 0;
}
