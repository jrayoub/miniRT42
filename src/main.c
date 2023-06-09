/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:48 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/10 07:29:16 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/image.h"
#include "headers/main.h"
#include "headers/scene.h"
#include "headers/types.h"

#define ESC 53

typedef struct mt
{
	t_image	*image;
	scene_t	*scene;
	void	*mlx;
	void	*mlx_win;
}			mt_t;

int	m_exit(mt_t *m_mt)
{
	deleteScene(m_mt->scene);
	free(m_mt->mlx);
	free(m_mt->mlx_win);
	printf("ESC Clicked \n");
	exit(0);
}

int	key_hook(int keycode, mt_t *mt)
{
	if (keycode == ESC)
		m_exit(mt);
	return (0);
}

int	main(void)
{
	mt_t				m_mt;

	m_mt = (mt_t){.scene = NULL, .image = NULL};
	m_mt.image = NULL;
	m_mt.mlx = mlx_init();
	m_mt.mlx_win = mlx_new_window(m_mt.mlx, WIDTH, HEIGHT, "miniRT");
	m_mt.scene = Scene(m_mt.mlx, m_mt.mlx_win);
	m_mt.image = Render(m_mt.scene, m_mt.mlx, m_mt.mlx_win);
	display(m_mt.mlx, m_mt.mlx_win, m_mt.image);
	mlx_key_hook(m_mt.mlx_win, key_hook, &m_mt);
	mlx_hook(m_mt.mlx_win, 17, 0l, m_exit, &m_mt);
	sleep(1);
	system("leaks miniRT");
	mlx_loop(m_mt.mlx);
}
