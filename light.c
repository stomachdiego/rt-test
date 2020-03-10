/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:31:01 by sdiego            #+#    #+#             */
/*   Updated: 2020/03/05 16:31:02 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_light	point_light(t_color color, t_vec pos)
{
	t_light l;

	l.intensity = color;
	l.pos = pos;
	return (l);
}

t_material	default_material(void)
{
	t_material	m;
	t_color		c = {1,1,1};

	m.color = c;
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	return (m);
}

t_color	lighting(t_material m, t_light l, t_vec pos, t_vec eye, t_vec norm_v, int shadow)
{
	t_color	effective_color;
	t_vec	light_v;
	t_color ambient;
	double	light_dot_normal;
	t_color	diffuse;
	t_color specular;
	t_vec	reflect_v;
	double	reflect_dot_eye;
	double	factor;

	effective_color = hadamard_prod(m.color, l.intensity);
	light_v = normalize(sub(l.pos, pos));
	ambient = mult_col(effective_color, m.ambient);
	light_dot_normal = dot(light_v, norm_v);
	if (shadow == 0)
	{
		if (light_dot_normal < 0)
		{
			diffuse = color(0,0,0);
			specular = color(0,0,0);
		}
		else
		{
			diffuse = mult_col(mult_col(effective_color, m.diffuse), light_dot_normal);
	
			reflect_v = reflect(neg(light_v), norm_v);
			reflect_dot_eye = dot(reflect_v, eye);
			if (reflect_dot_eye <= 0)
				specular = color(0,0,0);
			else
			{
				factor = powf(reflect_dot_eye, m.shininess);
				specular = mult_col(mult_col(l.intensity, m.specular), factor);
			}
		}
		return (add_col(add_col(ambient, diffuse), specular));
	}
	else
		return(ambient);
}

int	is_shadow(t_world w, t_vec	p)
{
	t_vec	v;
	t_vec	direction;
	double	distance;
	t_ray	r;
	t_x_t	x;
	int		hit_obj;

	v = sub(w.light.pos, p);
	distance = magnitude(v);
	direction = normalize(v);
	r = set_ray(p, direction);
	x = intersect_world(w, r);
	hit_obj = hit(x);
	if (hit_obj != -1 && x.t[hit_obj].t < distance)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}