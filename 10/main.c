#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

typedef enum {
  NOOP,
  ADDX
} Operation;

typedef struct {
  Operation op;
  int value;
  int cycles;
} Instruction;

Instruction* program[150];
int program_len = 0;

void push_instruction(Operation op, int val) {
  Instruction* inst = (Instruction*)malloc(sizeof(Instruction));

  if (op == NOOP) {
    inst->op = op;
    inst->cycles = 1;
  } else {
    inst->op = op;
    inst->value = val;
    inst->cycles = 2;
  }

  program[program_len++] = inst;
}

void read_input() {
  FILE* fp = fopen(FILENAME, "r");

  char buf[32];
  int val;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    if (strcmp(buf, "noop\n") == 0) {
      push_instruction(NOOP, 0);
    } else {
      sscanf(buf, "addx %d", &val);
      push_instruction(ADDX, val);
    }
  }

  fclose(fp);
}

void part1() {
  int x = 1, ans = 0, cycle = 0;

  while (cycle < 240) {
    int remaining_cycles = 0;
    for (int i = 0; i < program_len; ++i) {
      Instruction* inst = program[i];

      if (remaining_cycles == 0) {
        remaining_cycles = inst->cycles;
      }

      --remaining_cycles;
      ++cycle;

      if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220) {
        ans += cycle * x;
      }

      if (inst->op == ADDX && remaining_cycles == 0) {
        x += inst->value;
      }
      if (cycle == 240) break;
      if (remaining_cycles != 0) --i;
    }
  }

  printf("Part 1: %d\n", ans);
}

void part2() {
  int x = 1, cycle = 0, crt_pos = 0;

  printf("Part 2:\n");

  while (cycle < 240) {
    int remaining_cycles = 0;
    for (int i = 0; i < program_len; ++i) {
      Instruction* inst = program[i];

      if (remaining_cycles == 0) {
        remaining_cycles = inst->cycles;
      }

      --remaining_cycles;
      ++cycle;
      ++crt_pos;

      if (abs(crt_pos - x - 1) <= 1) {
        printf("#");
      } else {
        printf(".");
      }

      if (crt_pos % 40 == 0) {
        crt_pos = 0;
        printf("\n");
      }

      if (inst->op == ADDX && remaining_cycles == 0) {
        x += inst->value;
      }
      if (cycle == 240) break;
      if (remaining_cycles != 0) --i;
    }
  }
}

int main(void) {
  read_input();
  part1();
  part2();
  return 0;
}
