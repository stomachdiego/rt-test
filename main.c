/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:33 by sdiego            #+#    #+#             */
/*   Updated: 2020/02/26 14:12:34 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>

int		quit(t_sdl *sdl)
{
	if (sdl->text != NULL)
		SDL_DestroyTexture(sdl->text);
	sdl->text = NULL;
	if (sdl->img != NULL)
		free(sdl->img);
	SDL_DestroyRenderer(sdl->ren);
	SDL_DestroyWindow(sdl->win);
	SDL_Quit();

	return(0);
}

int	clear_map(t_sdl *sdl)
{
	if (SDL_SetRenderDrawColor(sdl->ren, 0x00, 0x00, 0x00, 0x00) == -1)
	{
		printf("error");
		return (1);
	}
	if (SDL_RenderClear(sdl->ren) == -1)
	{
		printf("error");
		return (1);
	}
	return (0);
}

int		init(t_sdl *sdl)
{
	int i;

	i = 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("%s\n", SDL_GetError());
		i = 1;
	}
	sdl->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (sdl->win == NULL)
	{
		printf("%s\n", SDL_GetError());
		i = 1;
	}
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_SOFTWARE);
	if (sdl->ren == NULL)
	{
		printf("%s\n", SDL_GetError());
		i = 1;
	}
	sdl->text = SDL_CreateTexture(sdl->ren, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (sdl->text == NULL)
	{
		printf("%s\n", SDL_GetError());
		i = 1;
	}
	sdl->img = malloc(WIN_W * WIN_H * sizeof(int));
	if (sdl->img == NULL)
	{
		write(1, "Can't create texture\n", 21);
		return (1);
	}
	return(i);
}

int		hit(t_x_t x)
{
	int	i;
	int check;
	int	a;
	int	b;

	i = 0;
	check = 0;
	b = 0;
	while (i < x.max_obj)
	{
		if (x.t[i].count > 0 && x.t[i].t >= 0)
		{
			b = 1;
			if (check == 0)
			{
				a = i;
				check++;
			}
			if (x.t[i].t < x.t[a].t)
			{
				a = i;
			}
		}
		i++;
	}
	if (b == 1)
		return (a);
	else
		return (-1); // значит нет пересечений 
}

void	alg(t_sdl *sdl, t_world w)
{
	int	x;
	int	y;
	double world_y;
	double	world_x;
	double wall_size = 7;
	double wall_z = 10;
	t_vec ray_org = set_v_p(0,0,-5,1);

	y = 0;
	double pixel_size = wall_size / WIN_H;
	double half = wall_size / 2;
	while (y < WIN_H)
	{
		world_y = half - pixel_size * y;
		x = 0;
		while (x < WIN_W)
		{
			world_x = -half + pixel_size * x;
			t_vec pos = set_v_p(world_x, world_y, wall_z, 1);
			t_ray r = set_ray(ray_org, normalize(sub(pos, ray_org)));
			//raycast(sdl, r, x, y, w);
			x++;
		}
		y++;
	}
}

/*void	raycast(t_sdl *sdl, t_ray r, int x, int y, t_world w)
{
	t_color	c;

	c = color_at(w, r);
	sdl->img[y * WIN_W + x] = col_to_int(c);
}*/

//void	raycast(t_sdl *sdl)
/*void	raycast(t_sdl *sdl, t_ray r, int x, int y)
{
	t_sp	s;
	t_sp	s1;
	int		obj;
	t_xs	xs;
	t_color sp = {1, 0, 0};
	t_color l_c = {1, 1, 1};

	obj = 0;
	//t_ray r = set_ray(set_v_p(0,0,-5,1), set_v_p(0,0,1,0));
	s = set_sphere(set_v_p(0,0,0,1), 1, sp, obj);
	s.m.color = color(1, 0.2, 1);
	s.m.ambient = 0;
	t_light light = point_light(l_c, set_v_p(-10, 10, -10, 1));
	//t_matrix m = matrix_mult(scaling(1, 0.5, 1), rotation_z(M_PI / 5));
	//t_matrix m = translation(0,1,0);
	//s.transform = set_transform(s.transform, m);

	//s.transform = set_transform(s.transform,scaling(1,0.5,1));
	xs = intersect_sp(s, r);
	

	int hit_obj = hit(xs);
	
	if (hit_obj != -1)
	{	
		t_vec	point = position(r, xs.t1[hit_obj]);
		t_vec	normal;
		t_color color_l;
		if (normal_at(xs.tr[hit_obj], point, &normal) == 0)
			printf("normal error");
		else
		{
			t_vec	eye = neg(r.d);
			color_l = lighting(xs.m[hit_obj], light, point, eye, normal);
			sdl->img[y * WIN_W + x] = col_to_int(color_l);
		}
		/*int i = 0;
		while (i < obj)
		{
			printf("xs.count = %i\n", xs.count[i]);
			if (xs.count[i] != 0)
			{
				printf("xs[0] = %f\n", xs.t1[i]);
				printf("xs[1] = %f\n", xs.t2[i]);
				printf("obj = %i\n\n", xs.obj[i]);
			}
			i++;
		}*/
	/*}
	else
	{
		t_color black = {0,0,0};
		sdl->img[y * WIN_W + x] = col_to_int(black);
	}
}*/

int		main(void)
{
	t_sdl		sdl;
	t_world		w;

	if (init(&sdl) != 0)
		quit(&sdl);
	
	sdl.run = 0;


//WORLD
	//floor
	w.s[0] = set_sphere(0);
	w.s[0].transform = scaling(10,0.01,10);
	w.s[0].m.color = color(1, 0.9, 0.9);
	w.s[0].m.specular = 0;
	//left_wall
	w.s[1] = set_sphere(1);
	w.s[1].transform = matrix_mult(translation(0,0,5), rotation_y(-M_PI / 4));
	w.s[1].transform = matrix_mult(w.s[1].transform, rotation_x(M_PI / 2));
	w.s[1].transform = matrix_mult(w.s[1].transform, scaling(10, 0.01, 10));
	w.s[1].m.color = color(1, 0.9, 0.9);
	w.s[1].m.specular = 0;
	//right_wall
	w.s[2] = set_sphere(2);
	w.s[2].transform = matrix_mult(translation(0,0,5), rotation_y(M_PI / 4));
	w.s[2].transform = matrix_mult(w.s[2].transform, rotation_x(M_PI / 2));
	w.s[2].transform = matrix_mult(w.s[2].transform, scaling(10, 0.01, 10));
	w.s[2].m.color = color(1, 0.9, 0.9);
	w.s[2].m.specular = 0;
	//middle
	w.s[3] = set_sphere(3);
	w.s[3].transform = translation(-0.5, 1, 0.5);
	w.s[3].m.color = color(0.1, 1, 0.5);
	w.s[3].m.specular = 0.3;
	w.s[3].m.diffuse = 0.7;
	//right
	w.s[4] = set_sphere(4);
	w.s[4].transform = matrix_mult(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5));
	w.s[4].m.color = color(0.5, 1, 0.1);
	w.s[4].m.specular = 0.3;
	w.s[4].m.diffuse = 0.7;
	//left
	w.s[5] = set_sphere(5);
	w.s[5].transform = matrix_mult(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33));
	w.s[5].m.color = color(1, 0.8, 0.1);
	w.s[5].m.specular = 0.3;
	w.s[5].m.diffuse = 0.7;
	//light
	w.light = point_light(color(1, 1, 1), set_v_p(-10, 10, -10, 1));
	w.max_obj = 6;
//WORLD

	//camera
	t_camera c = camera(WIN_W, WIN_H, M_PI / 3);
	c.transform = view_transform(set_v_p(0, 1.5, -5, 1), set_v_p(0, 1, 0, 1), set_v_p(0, 1, 0, 0));
	render(&sdl, c, w);
	
/*
	w.light = point_light(color(1, 1, 1), set_v_p(0, 0, -10, 1));
	
	w.s[0] = set_sphere(0);
	//w.s[0].transform = scaling(10,0.01,10);
	w.s[0].m.color = color(1, 0.9, 0.9);
	//w.s[0].m.specular = 0;
	
	w.s[1] = set_sphere(1);
	w.s[1].transform = translation(0,0,1);
	//w.s[1].m.color = color(1, 1, 1);
	//w.s[1].m.specular = 0;

	t_ray r = set_ray(set_v_p(0,0,-5,1), set_v_p(0,0,1,0));
	t_i i = intersection(5, w.s[1]);

	t_comps comps = prepare_computations(i, r);

	if (comps.over_point.c[2] < -EPSILON / 2)
	{
		if (comps.point.c[2] > comps.over_point.c[2])
		{
			printf("y\n");
		}
	}

	t_color col = shade_hit(w, comps);

	printf("r %f\n", col.r);
	printf("r %f\n", col.g);
	printf("r %f\n", col.b);
*/
	/*
	default_world(&w);
	w.light = point_light(color(1,1,1), set_v_p(0, 0, -10, 1));
	w.s[1].transform = translation(0,0,1);
	t_ray r = set_ray(set_v_p(0,0,5,1), set_v_p(0,0,1,0));
	t_i i = intersection(4, w.s[1]);
	t_comps comps = prepare_computations(i, r);
	t_color col = shade_hit(w, comps);

	printf("r %f\n", col.r);
	printf("r %f\n", col.g);
	printf("r %f\n", col.b);
	*/
	
	SDL_UpdateTexture(sdl.text, NULL, sdl.img, WIN_W * (sizeof(int)));
	SDL_RenderClear(sdl.ren);
	SDL_RenderCopy(sdl.ren, sdl.text, NULL, NULL);
	SDL_RenderPresent(sdl.ren);
	while (sdl.run == 0)
	{
		while (SDL_PollEvent(&sdl.e) != 0)
		{
			if (sdl.e.type == SDL_QUIT)
				sdl.run = 1;
			/*if (sdl.e.type == SDL_KEYDOWN)
				key_press(&m);
			if (sdl.e.type == SDL_MOUSEMOTION)
				mouse_move(&m);*/
			/*if (clear_map(&sdl) != 0)
				sdl.run = 1;
			if (raycast(&sdl) != 0)
				sdl.run = 1;
			if (draw(&sdl) != 0)
				sdl.run = 1;
			SDL_RenderPresent(sdl.ren);*/
		}

	}
	quit(&sdl);
	return(0);
}