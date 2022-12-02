#include <stdio.h>

/**
 * A -> Rock <- X     <- lose
 * B -> Paper <- Y    <- draw
 * C -> Scissors <- Z <- win
 */

#if 1
#define FILE_NAME "input.txt"
#else
#define FILE_NAME "sample.txt"
#endif

int calc_points(char op, char me) {
  int points = me - 'X' + 1;
  switch (op) {
    case 'A': {
      if (me == 'Y')
        points += 6;
      else if (me == 'X')
        points += 3;
    } break;
    case 'B': {
      if (me == 'Y')
        points += 3;
      else if (me == 'Z')
        points += 6;
    } break;
    case 'C': {
      if (me == 'Z')
        points += 3;
      else if (me == 'X')
        points += 6;
    } break;
  }

  return points;
}

void part1() {
  FILE *fp = fopen(FILE_NAME, "r");
  char op, me;
  int score = 0;

  while (fscanf(fp, "%c %c\n", &op, &me) == 2) {
    int points = calc_points(op, me);
    score += points;
  }

  printf("Part 1: %d\n", score);

  fclose(fp);
}

void part2() {
  FILE *fp = fopen(FILE_NAME, "r");
  char op, me;
  int score = 0;

  while (fscanf(fp, "%c %c\n", &op, &me) == 2) {
    switch (me) {
      case 'X': {
        if (op == 'A')
          me = 'Z';
        else if (op == 'C')
          me = 'Y';
      } break;
      case 'Y': {
        me = op + 23;
      } break;
      case 'Z': {
        if (op == 'A')
          me = 'Y';
        else if (op == 'C')
          me = 'X';
      } break;
    }

    int points = calc_points(op, me);
    score += points;
  }

  printf("Part 2: %d\n", score);

  fclose(fp);
}

int main(void) {
  part1();
  part2();
  return 0;
}
