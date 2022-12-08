#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define CAP 100

int matrix[CAP][CAP];
int rows, cols;

bool is_visible(int r, int c) {
  bool visible = false;
  int val = matrix[r][c];

  for (int i = 0; i < c; ++i) {
    if (matrix[r][i] >= val) {
      visible = false;
      break;
    }
    visible = true;
  }

  if (visible) return true;

  for (int i = c + 1; i < cols; ++i) {
    if (matrix[r][i] >= val) {
      visible = false;
      break;
    }
    visible = true;
  }

  if (visible) return true;

  for (int i = 0; i < r; ++i) {
    if (matrix[i][c] >= val) {
      visible = false;
      break;
    }
    visible = true;
  }

  if (visible) return true;

  for (int i = r + 1; i < rows; ++i) {
    if (matrix[i][c] >= val) {
      visible = false;
      break;
    }
    visible = true;
  }

  return visible;
}

void read_input() {
  rows = 0;
  FILE *fp = fopen(FILENAME, "r");

  memset(matrix, 0, sizeof(matrix));
  char buf[128];

  while (fscanf(fp, "%s\n", buf) > 0) {
    cols = strlen(buf);

    for (int i = 0; i < cols; ++i) {
      matrix[rows][i] = buf[i] - '0';
    }

    rows++;
  }

  fclose(fp);
}

void part1() {
  read_input();

  int ans = 2 * cols + 2 * rows - 4;

  for (int i = 1; i < rows - 1; ++i) {
    for (int j = 1; j < cols - 1; ++j) {
      ans += is_visible(i, j);
    }
  }

  printf("Part 1: %d\n", ans);
}

int scenic_score(int r, int c) {
  int score = 1, view_dist = 0;
  int val = matrix[r][c];

  for (int i = c - 1; i >= 0; --i) {
    ++view_dist;
    if (matrix[r][i] >= val) {
      break;
    }
  }

  score *= view_dist;
  view_dist = 0;

  for (int i = c + 1; i < cols; ++i) {
    ++view_dist;
    if (matrix[r][i] >= val) {
      break;
    }
  }

  score *= view_dist;
  view_dist = 0;

  for (int i = r - 1; i >= 0; --i) {
    ++view_dist;
    if (matrix[i][c] >= val) {
      break;
    }
  }
  score *= view_dist;
  view_dist = 0;

  for (int i = r + 1; i < rows; ++i) {
    ++view_dist;
    if (matrix[i][c] >= val) {
      break;
    }
  }

  return score * view_dist;
}

void part2() {
  read_input();

  int ans = 0;

  for (int i = 1; i < rows - 1; ++i) {
    for (int j = 1; j < cols - 1; ++j) {
      ans = fmax(ans, scenic_score(i, j));
    }
  }

  printf("Part 2: %d\n", ans);
}

int main(void) {
  part1();
  part2();
  return 0;
}
