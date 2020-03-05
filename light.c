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

t_color	lighting(t_material m, t_light l, t_vec pos, t_vec eye, t_vec norm_v)
{
	t_color	effective_color;
	t_vec	light_v;
	t_color ambient;
	float	light_dot_normal;
	t_color	diffuse;
	t_color specular;
	t_vec	reflect_v;
	float	reflect_dot_eye;
	float	factor;

	effective_color = hadamard_prod(m.color, l.intensity);
	light_v = normalize(sub(l.pos, pos));
	ambient = mult_col(effective_color, m.ambient);
	light_dot_normal = dot(light_v, norm_v);
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