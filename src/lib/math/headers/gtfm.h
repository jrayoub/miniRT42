/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtfm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:56 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/01 12:05:46 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTFM_H
# define GTFM_H
# include "../../../headers/types.h"
# include "matrix.h"
# include <stdio.h>
matrix_t	*Set_transform(vector_t *translation, vector_t *rotation,
				vector_t *scal);
ray_t		*Apply_transform(ray_t *input_ray, object_t *this, int dirFlag);
vector_t	*Apply_transform_vector(vector_t *inputVector, int dirFlag,
				object_t *this);
void		set_lineartfm(object_t *this);
vector_t	*get_norm(object_t *this, vector_t *input_vector);
#endif