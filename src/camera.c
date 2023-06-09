/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:39 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/03 03:17:58 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/camera.h"

camera_t	*Camera(double horizontal_size, double lenght, double aspect_ration)
{
	camera_t	*camera;

	camera = malloc(sizeof(camera_t));
	camera->position = NULL;
	camera->loockat = NULL;
	camera->up = NULL;
	camera->horizontal_size = horizontal_size;
	camera->lenght = lenght;
	camera->aspect_ration = aspect_ration;
	return (camera);
}

void	SetPosition(camera_t *this, vector_t *position)
{
	this->position = position;
}

void	SetUp(camera_t *this, vector_t *Up)
{
	this->up = Up;
}

void	Setloockat(camera_t *this, vector_t *loockat)
{
	this->loockat = loockat;
}

void	calculat_geometry(camera_t *this)
{
	vector_t	*aligment;

	aligment = minus(this->loockat, this->position);
	normalize(aligment);
	this->screen_u = cross(*aligment, *this->up);
	normalize(this->screen_u);
	this->screen_v = cross(*this->screen_u, *aligment);
	normalize(this->screen_v);
	this->screen_center = ms_addition(this->position,
			ms_num_muliplication(aligment, this->lenght), 1);
	this->screen_u = ms_num_muliplication(this->screen_u,
			this->horizontal_size);
	this->screen_v = ms_num_muliplication(this->screen_v,
			this->horizontal_size / this->aspect_ration);
}

ray_t	*generate_ray(camera_t *this, double screenX, double screenY)
{
	vector_t	*w_part1;
	vector_t	*dst_cords;
	vector_t	*scalled_u;
	vector_t	*scalled_v;

	scalled_u = num_muliplication(this->screen_u,
									screenX);
	scalled_v = num_muliplication(this->screen_v, screenY);
	w_part1 = addition(this->screen_center, scalled_u);
	dst_cords = addition(w_part1, scalled_v);
	free(w_part1);
	free(scalled_v);
	free(scalled_u);
	return (ray(copy_vector(*this->position), dst_cords));
}

void	deleteCamera(camera_t *this)
{
	if (this)
	{
		if (this->position)
			free(this->position);
		if (this->loockat)
			free(this->loockat);
		if (this->up)
			free(this->up);
		if (this->screen_u)
			free(this->screen_u);
		if (this->screen_v)
			free(this->screen_v);
		if (this->screen_center)
			free(this->screen_center);
		free(this);
	}
}