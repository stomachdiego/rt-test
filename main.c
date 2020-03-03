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

int	c(double r, double g, double b)
{
	
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return (((int)r << 16) + ((int)g << 8) + (int)b);
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

/*t_col	color_help(int i, int j, int k)
{
	t_col c;

	c.e[0] = i;
	c.e[1] = j;
	c.e[2] = k;
	return (c);
}*/

/*t_col	color_mult(t_col c, double d)
{
	c.e[0] = c.e[0] * d;
	if (c.e[0] >= 255)
		c.e[0] = 255;
	c.e[1] = c.e[1] * d;
	if (c.e[1] >= 255)
		c.e[1] = 255;
	c.e[2] = c.e[2] * d;
	if (c.e[2] >= 255)
		c.e[2] = 255;
	return (c);
}*/

/*int		raycast(t_sdl *sdl)
{
	int	i;
	int	j;
	t_ray	ray;
	t_sphere	sp;
	t_sphere	light;
	t_col		white;
	t_col		red;

	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			// send a ray through each pixel
			ray = ray_help(setv(i, j, 0), setv(0, 0, 1));
			
			double t = 20000;
			// check for intersections
			
			
			sp = sphere(setv(WIN_W / 2, WIN_H / 2, 50), 50); //init sphere
			light = sphere(setv(0, 0, 50), 1); //init light


			if (sphere_intersect(ray, &t, sp) != 0)
			{
				// point of intersection
				t_vec pi = add(ray.o, mulf(ray.d, t));
				white.col = setv(255, 255, 255);
				red.col = setv(255, 0, 0);
				// color the pixel

				t_vec L = sub(light.c, pi);
				t_vec N = getNormal(pi, sp);
				L = normalize(L);
				N = normalize(N);
				double dt = dot(L, N);
				white.col = mulf(white.col, dt);
				//white.col = mulf(white.col, 1.0);
				//white.col = add(red.col, white.col);
				//white.col = op_del(white.col, 2);
				sdl->img[j * WIN_W + i] = c(white.col.e[0], white.col.e[1], white.col.e[2]);
			}
			

			

			i++;
		}
		j++;
	}
	return (0);
}*/

int		draw(t_sdl *sdl)
{
	int	i;
	int	j;

	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			
			/*if (SDL_SetRenderDrawColor(sdl->ren, sdl->framebuffer[j][i].e[0], sdl->framebuffer[j][i].e[1], sdl->framebuffer[j][i].e[2], 0xff) == -1)
			{
				printf("error");
				return (1);
			}
			if (SDL_RenderDrawPoint(sdl->ren, i, j) == -1)
			{
				printf("error");
				return (1);
			}*/
			i++;
		}
		j++;
	}
	return (0);
}

int		hit(t_xs xs)
{
	int	i;
	int check;
	int	a;
	int	b;

	i = 0;
	check = 0;
	b = 0;
	while (i <= xs.max_obj)
	{
		if (xs.t1[i] >= 0 && xs.count[i] != 0)
		{
			b = 1;
			if (check == 0)
			{
				a = i;
				check++;
			}
			if (xs.t1[i] < xs.t1[a])
			{
				a = i;
			}
		}
		i++;
	}
	if (b == 1)
		return (a);
	else
		return (-1); // значить нет пересечений 
}

void	raycast(t_sdl *sdl)
{
	t_ray	r;
	t_sp	s;
	t_xs	xs;
	int		obj;

	obj = 0;
	r = set_ray(set_v_p(0,0,-5,1), set_v_p(0,0,1,0));
	s = set_sphere(set_v_p(0,0,0,1), 1, c(255,255,255), obj++);
	
	xs = intersect_sp(s, r, scaling(2,2,2));
	
	//s = set_sphere(set_v_p(0,0,1,1), 1, c(255,255,255), obj++);
	//xs = intersect_sp(s, r);
	int hit_obj = hit(xs);
	printf("hit obj = %i\n", hit_obj);
	if (hit_obj != -1)
	{
		int i = 0;
		while (i < obj)
		{
			printf("xs.count = %i\n", xs.count[i]);
			printf("xs[0] = %f\n", xs.t1[i]);
			printf("xs[1] = %f\n", xs.t2[i]);
			printf("obj = %i\n\n", xs.obj[i]);
			i++;
		}
	}
	/*t_ray ray = set_ray(set_v_p(1,2,3,1), set_v_p(0,1,0,0));
	t_matrix m = translation(3, 4, 5);
	t_ray r2 = transform(ray, m);
	printf("o = %f\n", r2.o.c[0]);
	printf("o = %f\n", r2.o.c[1]);
	printf("o = %f\n", r2.o.c[2]);
	printf("o = %f\n", r2.o.c[3]);
	printf("d = %f\n", r2.d.c[0]);
	printf("d = %f\n", r2.d.c[1]);
	printf("d = %f\n", r2.d.c[2]);
	printf("d = %f\n", r2.d.c[3]);*/

}

int		main(void)
{
	t_sdl		sdl;

	if (init(&sdl) != 0)
		quit(&sdl);
	
	sdl.run = 0;
	raycast(&sdl);
	//if (raycast(&sdl) != 0)
	//	sdl.run = 1;
	//if (draw(&sdl) != 0)
	//	sdl.run = 1;
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