#include <stdlib.h>
#include <stdio.h>

struct iterable {
  struct iter *(*iter)(const struct iterable *);
  void (*fin)(struct iterable *);
};

struct iter {
  int (*next)(struct iter *);
  int (*has_next)(const struct iter *);
  void (*fin)(struct iter *);
};

int
objective_sum(const struct iterable *data)
{
  int sum = 0;
  struct iter *iter = data->iter(data);
  while (iter->has_next(iter)) {
    sum += iter->next(iter);
  }
  iter->fin(iter);

  return sum;
}

struct array_list {
  struct iterable super;
  int (*get)(const struct array_list *, size_t i);
  size_t (*len)(const struct array_list *);
  int *inner;
  size_t n;
};


struct array_list_iter {
  struct iter super;
  const struct array_list *array;
  size_t i;
};

struct iter *array_list_iter(const struct iterable *);

void array_list_fin(struct iterable *);
int array_list_get(const struct array_list *, size_t);
size_t array_list_len(const struct array_list *);

struct array_list_iter *array_list_iter_new(const struct array_list *);
void array_list_iter_fin(struct iter *);
int array_list_iter_next(struct iter *);
int array_list_iter_has_next(const struct iter *);


struct array_list *
array_list_new(int *inner, size_t n)
{
  struct array_list *array = (struct array_list *)malloc(sizeof(struct array_list));
  if (! array) {
    return array;
  }

  array->super.iter = array_list_iter;
  array->super.fin = array_list_fin;
  array->get = array_list_get;
  array->len = array_list_len;
  array->inner = inner;
  array->n = n;

  return array;
}

void
array_list_fin(struct iterable *super)
{
  struct array_list *self = (struct array_list *) super;
  free(self);
}

struct iter *
array_list_iter(const struct iterable *super)
{
  struct array_list *self = (struct array_list *) super;

  return (struct iter *)array_list_iter_new(self);
}

int
array_list_get(const struct array_list *self, size_t i)
{
  return self->inner[i];
}

size_t
array_list_len(const struct array_list *self)
{
  return self->n;
}

int
array_list_iter_next(struct iter *super)
{
  struct array_list_iter *self = (struct array_list_iter *)super;
  int ret = self->array->get(self->array, self->i);

  self->i++;

  return ret;
}

struct array_list_iter *
array_list_iter_new(const struct array_list *array)
{
  struct array_list_iter *iter = malloc(sizeof(struct array_list_iter));
  if (! iter) {
    return iter;
  }

  iter->array = array;
  iter->i = 0;
  iter->super.fin = array_list_iter_fin;
  iter->super.next = array_list_iter_next;
  iter->super.has_next = array_list_iter_has_next;

  return iter;

}

void
array_list_iter_fin(struct iter *super)
{
  struct array_list_iter *self = (struct array_list_iter *)super;
  free(self);
}

int
main()
{
    return 0;
}