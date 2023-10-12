/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:09:09 by ngennaro          #+#    #+#             */
/*   Updated: 2023/10/12 17:19:00 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	refresh_img(t_mlx *mlx)
{
	ft_move(mlx);
	mlx->data->img = mlx_new_image(mlx->mlx_init_ptr, WIN_W, WIN_H);
	mlx->data->addr = mlx_get_data_addr(mlx->data->img,
			&mlx->data->bits_per_pixel, &mlx->data->line_length,
			&mlx->data->endian);
	ft_ray (mlx);
	mlx_put_image_to_window(mlx->mlx_init_ptr,
		mlx->mlx_win_ptr, mlx->data->img, 0, 0);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->data->img);
	return (0);
}

int	ft_tex_coo(t_ray ray, t_mlx mlx)
{
	double	wallx;
	double	texx;

	if (ray.side)
		wallx = mlx.player->pos_y + ray.perpwalldist * ray.raydiry;
	else
		wallx = mlx.player->pos_x + ray.perpwalldist * ray.raydirx;
	wallx = -floor(wallx);
	texx = (wallx * mlx.wall->east_height);
	if (ray.side && ray.raydirx > 0)
		texx = mlx.wall->east_height - texx - 1;
	if (!ray.side && ray.diry < 0)
		texx = mlx.wall->east_height - texx - 1;
	return (texx);
}

void	ft_get_color(t_mlx *mlx, t_ray ray, double x, double y)
{
	static double	half = (double)WIN_H / 2;
	int				drawn[2];

	drawn[0] = (double)-ray.lineheight / 2 + half;
	drawn[1] = drawn[0] + ray.lineheight;
	if (ray.side == 1)
	{
		if (ray.raydiry < 0)
			ft_draw_vertical_north(mlx, ray.i, drawn,
				(x - floor(x)) * mlx->wall->north_height);
		else
			ft_draw_vertical_south(mlx, ray.i, drawn,
				(1. - x + floor(x)) * mlx->wall->south_height);
	}
	else
	{
		if (ray.raydirx < 0)
			ft_draw_vertical_east(mlx, ray.i, drawn,
				(1. - y + floor(y)) * mlx->wall->east_height);
		else
			ft_draw_vertical_west(mlx, ray.i, drawn,
				(y - floor(y)) * mlx->wall->west_height);
	}
}

void	ft_ray(t_mlx *mlx)
{
	t_ray	ray;
	double	angle_radiants;
	int		i;
	double	offset_x;
	double	offset_y;

	offset_x = mlx->player->pos_x - (int)mlx->player->pos_x;
	offset_y = mlx->player->pos_y - (int)mlx->player->pos_y;
	ft_prep_floor(mlx);
	angle_radiants = mlx->player->look * M_PI / 180.;
	ray.dirx = cos(angle_radiants);
	ray.diry = sin(angle_radiants);
	ray.planx = -ray.diry;
	ray.plany = ray.dirx;
	i = -1;
	while (++i < WIN_W)
	{
		ray.pos_x = (int)mlx->player->pos_x;
		ray.pos_y = (int)mlx->player->pos_y;
		ray.camerax = 2 * i / (double)WIN_W - 1;
		ray.raydirx = ray.dirx + (ray.planx * ray.camerax);
		ray.raydiry = ray.diry + ray.plany * ray.camerax;
		ray.deltadistx = fabs(1 / ray.raydirx);
		ray.deltadisty = fabs(1 / ray.raydiry);
		ray.hit = 0;
		if (ray.raydirx < 0)
		{
			ray.sidedistx = offset_x * ray.deltadistx;
			ray.stepx = -1;
		}
		else
		{
			ray.sidedistx = (1. - offset_x) * ray.deltadistx;
			ray.stepx = 1;
		}
		if (ray.raydiry < 0)
		{
			ray.sidedisty = offset_y * ray.deltadisty;
			ray.stepy = -1;
		}
		else
		{
			ray.sidedisty = (1. - offset_y) * ray.deltadisty;
			ray.stepy = 1;
		}
		while (ray.hit == 0)
		{
			if (ray.sidedistx < ray.sidedisty)
			{
				ray.sidedistx += ray.deltadistx;
				ray.pos_x += ray.stepx;
				ray.side = 0;
			}
			else
			{
				ray.sidedisty += ray.deltadisty;
				ray.pos_y += ray.stepy;
				ray.side = 1;
			}
			if (!is_valid_move(mlx, ray.pos_x, ray.pos_y))
				ray.hit = 1;
		}
		if (ray.side == 0)
			ray.perpwalldist = ray.sidedistx - ray.deltadistx;
		else
			ray.perpwalldist = ray.sidedisty - ray.deltadisty;
		ray.lineheight = (int)(WIN_H / ray.perpwalldist);
		ray.i = i;
		ft_get_color(mlx, ray, ray.pos_x + ray.perpwalldist
			* ray.raydirx + mlx->player->pos_x, ray.pos_y
			+ ray.perpwalldist * ray.raydiry + mlx->player->pos_y);
	}
}
