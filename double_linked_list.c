/**
 * @file double_linked_list.c
 * @author b1tg (https://b1tg.github.io)
 * @brief double linked list
 * @version 0.1
 * @date 2022-02-25
 * 
 */
// https://lwn.net/SubscriberLink/885941/01fdc39df2ecc25f/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct list_head {
  struct list_head *next, *prev;
} list_head;

typedef struct foo {
  int fooness;
  struct list_head list;
} tfoo;

int main() {
  list_head root = {.prev = 0, .next = 0};
  list_head head = {.next = 0, .prev = &root};
  tfoo foo = {.fooness = 1, .list = head};
  root.next = &(foo.list);
  tfoo foo1 = {.fooness = 2, .list = {.next = 0, .prev = 0}};
  foo1.list.prev = &(foo.list);
  foo.list.next = &(foo1.list);

  printf("foo %p\n", &foo);
  printf("\t%p, %p\n", &(foo.fooness), &(foo.list));
  printf("\t0x%x\n", sizeof(foo.fooness));
  printf("foo1 %p\n", &foo1);

  list_head *cur_head = root.next;
  while (1) {
    printf("cur_head %p\n", cur_head);
    struct foo *cur = (struct foo *)((char *)cur_head - 8);
    printf("-> %d\n", cur->fooness);
    cur_head = cur_head->next;
    if (cur_head == (list_head *)0) {
      break;
    }
  }
  printf("===\n");
  return 0;
}

// foo 0x7fff62c71850
//	0x7fff62c71850, 0x7fff62c71858
//	0x4
// foo1 0x7fff62c71830
// cur_head 0x7fff62c71858
//-> 1
// cur_head 0x7fff62c71838
//-> 2
//===
