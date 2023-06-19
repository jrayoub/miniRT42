#include "headers/vectormath.h"

vector_t *vector(float x, float y, float z)
{
	vector_t *vector = malloc(sizeof(vector_t));
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return vector;
}

vector_t *copy_vector(vector_t v)
{
	return vector(v.x, v.y, v.z);
}

float vector_lenght2(vector_t v)
{
	return sqrt(v.x) + sqrt(v.y) + sqrt(v.z);
}

float vector_lenght(vector_t v)
{
	return sqrt(vector_lenght2(v));
}

vector_t *normalized(vector_t *v)
{
	vector_t *n_v = copy_vector(*v);
	normalize(n_v);
	return (n_v);
}

float normalize(vector_t *v)
{
	float l = vector_lenght(*v);
	num_division(v, l);
	return (l);
}

vector_t *equal(vector_t *target, vector_t *v)
{
	vector_t *new = copy_vector(*target);
	new->x = v->x;
	new->y = v->y;
	new->z = v->z;
	return new;
}

vector_t *minus(vector_t *target, vector_t *v)
{
	vector_t *new = copy_vector(*target);
	new->x -= v->x;
	new->y -= v->y;
	new->z -= v->z;
	return new;
}

vector_t *pluse(vector_t *target, vector_t *v)
{
	vector_t *new = copy_vector(*target);
	new->x += v->x;
	new->y += v->y;
	new->z += v->z;
	return new;
}

vector_t *muliplication(vector_t *target, vector_t *v)
{
	vector_t *new = copy_vector(*target);
	new->x *= v->x;
	new->y *= v->y;
	new->z *= v->z;
	return new;
}

vector_t *num_muliplication(vector_t *target, float num)
{
	vector_t *new = copy_vector(*target);
	new->x *= num;
	new->y *= num;
	new->z *= num;
	return new;
}

vector_t *division(vector_t *target, vector_t *v)
{
	vector_t *new = copy_vector(*target);
	new->x /= v->x;
	new->y /= v->y;
	new->z /= v->z;
	return new;
}

vector_t *num_division(vector_t *target, float num)
{
	vector_t *new = copy_vector(*target);
	new->x /= num;
	new->y /= num;
	new->z /= num;
	return new;
}

float dot(vector_t v, vector_t u)
{
	return v.x * u.x + v.y * u.y + v.z * u.z;
}

vector_t *cross(vector_t v, vector_t u)
{
	return vector(v.y * u.z - v.z * u.y, v.z * u.x - v.x * u.z, v.x * u.y - v.y * u.x);
}

vector_t *from_mt_to_vt(matrix_t mt)
{
	if (mt.cols != 3 || mt.rows != 1)
		return (NULL);
	return (vector(mt.matrix[0][0], mt.matrix[0][1], mt.matrix[0][2]));
}