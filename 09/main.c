#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define CAP 500

typedef struct {
  int x;
  int y;
} Knot;

bool vis[CAP][CAP];
Knot* knots[10];

int dirs[4][2] = {
    {-1, 0},
    {1, 0},
    {0, 1},
    {0, -1},
};

int count_vis() {
  int cnt = 0;

  for (int i = 0; i < CAP; ++i) {
    for (int j = 0; j < CAP; ++j) {
      cnt += vis[i][j];
    }
  }

  return cnt;
}

void dump_vis() {
  for (int i = CAP; i >= 0; --i) {
    for (int j = 0; j < CAP; ++j) {
      if (vis[i][j]) {
        printf("#");
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
  printf("\n");
}

void dump_knots() {
  for (int i = CAP; i >= 0; --i) {
    for (int j = 0; j < CAP; ++j) {
      Knot* knot = NULL;

      int k;
      for (k = 0; k < 10; ++k) {
        if (knots[k]->x == j && knots[k]->y == i) {
          knot = knots[k];
          break;
        }
      }

      if (knot != NULL) {
        printf("%d", k);
      } else {
        if (vis[i][j]) {
          printf("#");
        } else {
          printf(".");
        }
      }
    }
    printf("\n");
  }
  printf("\n");
}

void move_rope(int n_knots, int dir[]) {
  (void)dir;
  for (int i = 1; i < n_knots; ++i) {
    Knot* head = knots[i - 1];
    Knot* tail = knots[i];

    if (abs(head->x - tail->x) > 1 || abs(head->y - tail->y) > 1) {
      tail->x += (head->x - tail->x) / abs(head->x - tail->x);
      tail->y += (head->y - tail->y) / abs(head->y - tail->y);

      if (i == n_knots - 1)
        vis[tail->y][tail->x] = true;
    }
  }
  // dump_knots();
}

Knot* create_knot() {
  Knot* knot = (Knot*)malloc(sizeof(Knot));
  knot->x = CAP / 2;
  knot->y = CAP / 2;
  return knot;
}

void part1() {
  memset(vis, 0, sizeof(vis));

  FILE* fp = fopen(FILENAME, "r");

  char op;
  int cnt;

  Knot* head = create_knot();
  Knot* tail = create_knot();

  knots[0] = head;
  knots[1] = tail;

  vis[tail->y][tail->x] = true;

  while (fscanf(fp, "%c %d\n", &op, &cnt) > 0) {
    if (op == 'R') {
      for (int i = 0; i < cnt; ++i) {
        head->x++;
        move_rope(2, dirs[1]);
      }
    } else if (op == 'L') {
      for (int i = 0; i < cnt; ++i) {
        head->x--;
        move_rope(2, dirs[0]);
      }
    } else if (op == 'U') {
      for (int i = 0; i < cnt; ++i) {
        head->y++;
        move_rope(2, dirs[2]);
      }
    } else if (op == 'D') {
      for (int i = 0; i < cnt; ++i) {
        head->y--;
        move_rope(2, dirs[3]);
      }
    } else {
      assert(0 && "Unknown OP");
    }
  }

  // dump_vis();

  printf("Part 1: %d\n", count_vis());

  fclose(fp);
}

void part2() {
  memset(vis, 0, sizeof(vis));

  for (int i = 0; i < 10; ++i) {
    knots[i] = create_knot();
  }

  FILE* fp = fopen(FILENAME, "r");

  char op;
  int cnt;

  vis[CAP / 2][CAP / 2] = true;

  while (fscanf(fp, "%c %d\n", &op, &cnt) > 0) {
    if (op == 'R') {
      for (int i = 0; i < cnt; ++i) {
        knots[0]->x++;
        move_rope(10, dirs[1]);
      }
    } else if (op == 'L') {
      for (int i = 0; i < cnt; ++i) {
        knots[0]->x--;
        move_rope(10, dirs[0]);
      }
    } else if (op == 'U') {
      for (int i = 0; i < cnt; ++i) {
        knots[0]->y++;
        move_rope(10, dirs[2]);
      }
    } else if (op == 'D') {
      for (int i = 0; i < cnt; ++i) {
        knots[0]->y--;
        move_rope(10, dirs[3]);
      }
    } else {
      assert(0 && "Unknown OP");
    }
    // dump_knots(knots);
  }

  // dump_vis();

  printf("Part 2: %d\n", count_vis());

  fclose(fp);
}

int main(void) {
  part1();
  part2();
  return 0;
}
