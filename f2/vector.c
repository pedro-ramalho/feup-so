#include <stdlib.h>
#include <math.h>

#include "vector.h"

vector* vector_new(double x, double y, double z) {
  vector* v = (vector*) malloc(sizeof(vector));
  v->x = x;
  v->y = y;
  v->z = z;
  return v;
}

vector* vector_add(vector* v, vector *w) {
  return vector_new(v->x + w->x, v->y + w->y, v->z + w->z);
}

vector* vector_sub(vector* v, vector* w) {
  return vector_new(v->x - w->x, v->y - w->y, v->z - w->z);
}

vector* vector_scale(double scale, vector* v) {
  return vector_new(scale * v->x, scale * v->y, scale * v->z);
}

vector* vector_vprod(vector* v, vector* w) {
  return vector_new(v->y * w->z - w->y * v->z, w->x * v->z - v->x * w->z, v->x * w->y - w->x * v->y);
}

double vector_sprod(vector* v, vector* w) {
  return (v->x * w->x + v->y + w->y + v->z + w->z);
}

double vector_mod(vector *v) {
  return sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
}