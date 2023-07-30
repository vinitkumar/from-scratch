#include <stdlib.h>
#include <string.h>
#include <stdio.h>


static uint8_t MEMORY_POOL[64];
static uint8_t MEMORY_POOL_USED = 0;


struct free_entry {
  void *ptr;
  uint64_t size;
};

typedef struct free_entry free_entry_t;

static free_entry_t FREE_LIST[64] = {
    (free_entry_t) {
      .ptr = MEMORY_POOL,
      .size = 64,
    },
};


static uint64_t FREE_LIST_USED = 1;

void print_free_list() {
  printf("FREE LIST \n");
  for (uint64_t i=0; i < FREE_LIST_USED; i++) {
      free_entry_t *entry;
      entry = &FREE_LIST[i];
      printf("   %p(%llu)\n", entry->ptr, entry->size);
    }
}

free_entry_t *find_free_entry(size_t size) {
  for (uint64_t i=0; i < FREE_LIST_USED; i++) {
    free_entry_t *entry;
    entry = &FREE_LIST[i];
    if (entry->size >= size) {
      return entry;
    }
  }
}


void *malloc(size_t size) {
  size += 8;
  free_entry_t *entry;
  entry = find_free_entry(size);

  void *base_ptr;
  uint64_t *size_ptr;
  void *user_ptr;

  base_ptr = entry->ptr;
  size_ptr = base_ptr;
  user_ptr = base_ptr + 8;

  *size_ptr = size;

  entry->ptr += size;
  entry->size -= size;

  print_free_list();

  return user_ptr;
}

void free(void *pt) {
  free_entry_t *entry;
  entry = &FREE_LIST[FREE_LIST_USED];

}

int main() {
  print_free_list();
  char *a;
  char *b;
  char *c;
  char *d;
  a = malloc(4);
  b = malloc(4);
  c = malloc(4);

  strcpy(a, "foo\0");
  strcpy(b, "bar\0");
  strcpy(c, "baz\0");
  printf("%p\n", a);
  printf("%p\n", b);
  printf("%p\n", c);
  free(b);

  d = malloc(4);
  printf("%p\n", d);
  print_free_list();

}

