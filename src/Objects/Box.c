/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:32:28 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/04 01:32:28 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Box.h"

object_t	*box(vector_t *translation, vector_t *rotation, vector_t *scal,
		vector_t *color)
{
	object_t	*box;

	box = object_base(translation, rotation, scal, color);
	box->test_inter = box_int_test;
	box->material->shininess_coefficient = 10.f;
	box->material->reflection_coefficient = .2;
	return (box);
}

int	box_int_test(object_t *this, ray_t *camera_ray, propretries_t *prop)
{
	ray_t			*bckray;
	vector_t		k;
	int				index;
	propretries_t	*local_prop;
	t_box_solutions	box_solutions;

	box_solutions = (t_box_solutions){
		(double[]){MAX_V, MAX_V, MAX_V, MAX_V, MAX_V, MAX_V},
		(double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		(double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0}};
	bckray = Apply_transform(camera_ray, this, BCKWRD);
	k = *bckray->m_lab;
	normalize(&k);
	up_down_faces(&k, bckray->point1, &box_solutions);
	left_right_faces(&k, bckray->point1, &box_solutions);
	front_back_faces(&k, bckray->point1, &box_solutions);
	if (!get_nearest_intersection(&box_solutions, &index))
		return (FALSE);
	local_prop = set_box_propreties(this, bckray, &box_solutions, index);
	*prop = *local_prop;
	free(local_prop);
	return (TRUE);
}

propretries_t	*set_box_propreties(object_t *this, ray_t *bckray,
		t_box_solutions *box_solutions, int index)
{
	vector_t		*poi;
	vector_t		*m_normal;
	vector_t		*int_poi;
	propretries_t	*prop;
	vector_t		k;

	k = *bckray->m_lab;
	normalize(&k);
	prop = malloc(sizeof(propretries_t));
	poi = ms_addition(bckray->point1, num_muliplication(&k,
				box_solutions->solutions[index]), 1);
	int_poi = Apply_transform_vector(poi, FRWRD, this);
	m_normal = get_gb_normal(this, index);
	prop->int_point = *int_poi;
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	prop->uv_cords = (t_uv_cords){box_solutions->u_values[index],
									box_solutions->v_values[index]};
	return (prop);
}

vector_t	*get_gb_normal(object_t *this, int index)
{
	vector_t	*normal;
	vector_t	*m_normal;

	normal = get_face_normal(index);
	m_normal = get_norm(this, normal);
	free(normal);
	return (m_normal);
}

int	get_nearest_intersection(t_box_solutions *box_solutions,
								int *index)
{
	int		i;
	int		valide_int;
	double	t;

	*index = 0;
	valide_int = FALSE;
	t = MAX_V;
	i = 0;
	while (i < 6)
	{
		if ((box_solutions->solutions[i] < t
				&& box_solutions->solutions[i] > 0.0)
			&& fabs(box_solutions->u_values[i]) <= 1
			&& fabs(box_solutions->v_values[i]) <= 1)
		{
			valide_int = TRUE;
			*index = i;
			t = box_solutions->solutions[i];
		}
		i++;
	}
	return (valide_int);
}
void	up_down_faces(vector_t *k, vector_t *a, t_box_solutions *box_solutions)
{
	if (!close_enough(k->z, 0.f))
	{
		box_solutions->solutions[0] = (a->z - 1.0) / -k->z;
		box_solutions->solutions[1] = (a->z + 1.0) / -k->z;
		box_solutions->u_values[0] = a->x + k->x * box_solutions->solutions[0];
		box_solutions->v_values[0] = a->y + k->y * box_solutions->solutions[0];
		box_solutions->u_values[1] = a->x + k->x * box_solutions->solutions[1];
		box_solutions->v_values[1] = a->y + k->y * box_solutions->solutions[1];
	}
}
void	left_right_faces(vector_t *k, vector_t *a,
		t_box_solutions *box_solutions)
{
	if (!close_enough(k->y, 0.f))
	{
		box_solutions->solutions[4] = (a->y + 1) / -k->y;
		box_solutions->solutions[5] = (a->y - 1) / -k->y;
		box_solutions->u_values[4] = a->x + k->x * box_solutions->solutions[4];
		box_solutions->v_values[4] = a->z + k->z * box_solutions->solutions[4];
		box_solutions->u_values[5] = a->x + k->x * box_solutions->solutions[5];
		box_solutions->v_values[5] = a->z + k->z * box_solutions->solutions[5];
	}
}
void	front_back_faces(vector_t *k, vector_t *a,
		t_box_solutions *box_solutions)
{
	if (!close_enough(k->x, 0.f))
	{
		box_solutions->solutions[2] = (a->x + 1.0) / -k->x;
		box_solutions->solutions[3] = (a->x - 1.0) / -k->x;
		box_solutions->u_values[2] = a->z + k->z * box_solutions->solutions[2];
		box_solutions->v_values[2] = a->y + k->y * box_solutions->solutions[2];
		box_solutions->u_values[3] = a->z + k->z * box_solutions->solutions[3];
		box_solutions->v_values[3] = a->y + k->y * box_solutions->solutions[3];
	}
}

vector_t	*get_face_normal(int index)
{
	if (index == 0)
		return (vector(0, 0, 1));
	if (index == 1)
		return (vector(0, 0, -1));
	if (index == 2)
		return (vector(-1, 0, 0));
	if (index == 3)
		return (vector(1, 0, 0));
	if (index == 4)
		return (vector(0, -1, 0));
	if (index == 5)
		return (vector(0, 1, 0));
	return (NULL);
}
