#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define MAX 100000
#define TOTAL 70000000
#define NEEDED 30000000

struct Folder {
  struct Folder* parent;
  struct Folder* childs[32];
  size_t size;
  size_t child_cnt;
};

typedef struct Folder Folder;

Folder* create_new_folder(Folder* curr) {
  Folder* f = (Folder*)calloc(1, sizeof(Folder));

  if (curr != NULL) {
    curr->childs[curr->child_cnt++] = f;
    f->parent = curr;
  }

  return f;
}

void update_parent_sizes(Folder* curr, int sz) {
  Folder* f = curr;

  while (f->parent != NULL) {
    f = f->parent;
    f->size += sz;
  }
}

int get_dirs_to_delete_sz(Folder* root) {
  int sz = 0;

  for (size_t i = 0; i < root->child_cnt; ++i) {
    Folder* child = root->childs[i];
    if (child->size <= MAX) {
      sz += child->size;
    }

    sz += get_dirs_to_delete_sz(child);
  }

  return sz;
}

void part1() {
  FILE* fp = fopen(FILENAME, "r");

  char buf[64];

  Folder* root = create_new_folder(NULL);
  Folder* curr = root;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    char arg[16];

    if (sscanf(buf, "$ cd %s", arg) > 0) {
      if (strcmp(arg, "/") != 0) {
        if (strcmp(arg, "..") == 0) {
          curr = curr->parent;
        } else {
          curr = create_new_folder(curr);
        }
      }
    } else {
      int sz = atoi(buf);
      curr->size += sz;
      update_parent_sizes(curr, sz);
    }
  }

  int ans = get_dirs_to_delete_sz(root);

  printf("Part 1: %d\n", ans);

  fclose(fp);
}

size_t get_dir_to_delete_sz(Folder* f, size_t needed_space) {
  size_t candidate = f->size;

  for (size_t i = 0; i < f->child_cnt; ++i) {
    Folder* child = f->childs[i];

    if (child->size >= needed_space) {
      candidate = fmin(candidate, child->size);
    }

    candidate = fmin(candidate, get_dir_to_delete_sz(child, needed_space));
  }

  if (candidate < needed_space) return 100000000;

  return candidate;
}

void part2() {
  FILE* fp = fopen(FILENAME, "r");

  char buf[64];

  Folder* root = create_new_folder(NULL);
  Folder* curr = root;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    char arg[16];

    if (sscanf(buf, "$ cd %s", arg) > 0) {
      if (strcmp(arg, "/") != 0) {
        if (strcmp(arg, "..") == 0) {
          curr = curr->parent;
        } else {
          curr = create_new_folder(curr);
        }
      }
    } else {
      int sz = atoi(buf);
      curr->size += sz;
      update_parent_sizes(curr, sz);
    }
  }

  int ans = get_dir_to_delete_sz(root, NEEDED - (TOTAL - root->size));

  printf("Part 2: %d\n", ans);

  fclose(fp);
}

int main(void) {
  part1();
  part2();
  return 0;
}
