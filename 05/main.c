#include <stdio.h>
#include <string.h>

#if 1
#define FILE_NAME "input.txt"
#else
#define FILE_NAME "sample.txt"
#endif

typedef struct {
  int len;
  char data[50];
} Stack;

Stack stacks[10];

void dump_stacks() {
  for (int i = 1; i < 10; ++i) {
    Stack stack = stacks[i];

    if (stack.len > 0) {
      for (int j = 0; j < stack.len; ++j) {
        printf("%c ", stack.data[j]);
      }
      printf("\n");
    }
  }
  printf("\n");
}

void reverse_stacks() {
  for (int i = 1; i < 10; ++i) {
    for (int j = 0; j < stacks[i].len / 2; ++j) {
      char tmp = stacks[i].data[j];
      stacks[i].data[j] = stacks[i].data[stacks[i].len - j - 1];
      stacks[i].data[stacks[i].len - j - 1] = tmp;
    }
  }
}

void read_crates(FILE *fp) {
  memset(stacks, 0, sizeof(stacks));
  char *line = NULL;
  size_t line_cap = 0;
  ssize_t len;

  while ((len = getline(&line, &line_cap, fp)) > 1) {
    for (int i = 1, j = 1; i < len; i += 4, ++j) {
      if (line[i] >= 'A') {
        stacks[j].data[stacks[j].len++] = line[i];
      }
    }
  }
}

void part1() {
  FILE *fp = fopen(FILE_NAME, "r");

  read_crates(fp);
  reverse_stacks();

  int qty, from, to;

  while (fscanf(fp, "move %d from %d to %d\n", &qty, &from, &to) > 0) {
    while (qty--) {
      stacks[to].data[stacks[to].len++] = stacks[from].data[--stacks[from].len];
    }
  }

  printf("Part 1: ");

  for (int i = 1; i < 10; ++i) {
    if (stacks[i].len > 0) {
      printf("%c", stacks[i].data[stacks[i].len - 1]);
    }
  }
  printf("\n");

  fclose(fp);
}

void part2() {
  FILE *fp = fopen(FILE_NAME, "r");

  read_crates(fp);
  reverse_stacks();

  int qty, from, to;

  while (fscanf(fp, "move %d from %d to %d\n", &qty, &from, &to) > 0) {
    for (int i = 0; i < qty; ++i) {
      stacks[to].data[stacks[to].len++] = stacks[from].data[stacks[from].len - qty + i];
    }
    stacks[from].len -= qty;
  }

  printf("Part 2: ");

  for (int i = 1; i < 10; ++i) {
    if (stacks[i].len > 0) {
      printf("%c", stacks[i].data[stacks[i].len - 1]);
    }
  }
  printf("\n");

  fclose(fp);
}

int main(void) {
  part1();
  part2();
  return 0;
}
