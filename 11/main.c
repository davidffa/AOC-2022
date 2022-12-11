#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define NROUNDSP1 20
#define NROUNDSP2 10000
#define mxMONKEYS 10
#define mxITEMS 30

#define ull unsigned long long

typedef enum {
  ADD,
  MULT,
} Op;

typedef struct {
  ull items[mxITEMS];
  int items_cnt;
  Op operation;
  int op_val;
  int test_val;
  int true_monkey;
  int false_monkey;
  int insp_cnt;
} Monkey;

Monkey* monkeys[mxMONKEYS] = {0};
int monkeys_cnt;

void new_monkey() {
  Monkey* monkey = (Monkey*)calloc(1, sizeof(Monkey));

  monkeys[monkeys_cnt++] = monkey;
}

void dump_monkey_data(int monkey_idx) {
  Monkey* m = monkeys[monkey_idx];
  printf("Monkey %d\n", monkey_idx);
  printf("Items: ");

  for (int i = 0; i < m->items_cnt; ++i) {
    printf("%llu ", m->items[i]);
  }

  printf("\n");

  printf("Operation: %d\n", m->operation);
  printf("Test val: %d\n", m->test_val);
  printf("True monkey: %d\n", m->true_monkey);
  printf("False monkey: %d\n", m->false_monkey);
  printf("\n");
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

void read_input() {
  monkeys_cnt = 0;

  FILE* fp = fopen(FILENAME, "r");
  int monkey_i;

  while (fscanf(fp, "Monkey %d:\n", &monkey_i) > 0) {
    new_monkey();
    char buf[64];

    fgets(buf, sizeof(buf), fp);

    char* token = strtok(buf, "Starting items");

    while ((token = strtok(NULL, ", ")) != NULL) {
      monkeys[monkey_i]->items[monkeys[monkey_i]->items_cnt++] = atoi(token);
    }

    fgets(buf, sizeof(buf), fp);

    token = strtok(buf, "Operation: new =");

    while ((token = strtok(NULL, " ")) != NULL) {
      if (token[0] == '+') {
        monkeys[monkey_i]->operation = ADD;
      } else if (token[0] == '*') {
        monkeys[monkey_i]->operation = MULT;
      } else {
        monkeys[monkey_i]->op_val = atoi(token);
      }
    }

    fscanf(fp, "  Test: divisible by %d\n", &monkeys[monkey_i]->test_val);
    fscanf(fp, "    If true: throw to monkey %d\n", &monkeys[monkey_i]->true_monkey);
    fscanf(fp, "    If false: throw to monkey %d\n", &monkeys[monkey_i]->false_monkey);

    // dump_monkey_data(monkeys[monkey_i]);
  }

  fclose(fp);
}

void part1() {
  for (int i = 0; i < NROUNDSP1; ++i) {
    for (int j = 0; j < monkeys_cnt; ++j) {
      Monkey* m = monkeys[j];
      m->insp_cnt += m->items_cnt;
      for (int k = 0; k < m->items_cnt; ++k) {
        if (m->operation == MULT) {
          if (m->op_val == 0) {
            m->items[k] *= m->items[k];
          } else {
            m->items[k] *= m->op_val;
          }
        } else {
          if (m->op_val == 0) {
            m->items[k] += m->items[k];
          } else {
            m->items[k] += m->op_val;
          }
        }

        m->items[k] /= 3;

        if (m->items[k] % m->test_val == 0) {
          monkeys[m->true_monkey]->items[monkeys[m->true_monkey]->items_cnt++] = m->items[k];
        } else {
          monkeys[m->false_monkey]->items[monkeys[m->false_monkey]->items_cnt++] = m->items[k];
        }
      }

      m->items_cnt = 0;
    }
  }

  int max[2] = {
      monkeys[0]->insp_cnt,
      monkeys[1]->insp_cnt,
  };

  sort(max, 2);
  for (int i = 2; i < monkeys_cnt; ++i) {
    if (monkeys[i]->insp_cnt > max[0]) {
      max[0] = monkeys[i]->insp_cnt;
      sort(max, 2);
    }
  }

  printf("Part 1: %d\n", max[0] * max[1]);
}

void part2() {
  ull div = 1;

  for (int i = 0; i < monkeys_cnt; ++i) {
    div *= (ull)monkeys[i]->test_val;
  }

  for (int i = 0; i < NROUNDSP2; ++i) {
    for (int j = 0; j < monkeys_cnt; ++j) {
      Monkey* m = monkeys[j];
      m->insp_cnt += m->items_cnt;
      for (int k = 0; k < m->items_cnt; ++k) {
        if (m->operation == MULT) {
          if (m->op_val == 0) {
            m->items[k] *= m->items[k];
          } else {
            m->items[k] *= m->op_val;
          }
        } else {
          if (m->op_val == 0) {
            m->items[k] += m->items[k];
          } else {
            m->items[k] += m->op_val;
          }
        }

        m->items[k] %= div;

        if (m->items[k] % m->test_val == 0) {
          monkeys[m->true_monkey]->items[monkeys[m->true_monkey]->items_cnt++] = m->items[k];
        } else {
          monkeys[m->false_monkey]->items[monkeys[m->false_monkey]->items_cnt++] = m->items[k];
        }
      }

      m->items_cnt = 0;
    }
  }

  int max[2] = {
      monkeys[0]->insp_cnt,
      monkeys[1]->insp_cnt,
  };

  sort(max, 2);
  for (int i = 2; i < monkeys_cnt; ++i) {
    if (monkeys[i]->insp_cnt > max[0]) {
      max[0] = monkeys[i]->insp_cnt;
      sort(max, 2);
    }
  }

  printf("Part 2: %llu\n", (ull)max[0] * (ull)max[1]);
}

int main(void) {
  read_input();
  part1();
  read_input();
  part2();

  return 0;
}
