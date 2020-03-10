/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:09:18 by sdiego            #+#    #+#             */
/*   Updated: 2020/03/06 15:09:19 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	default_world(t_world *w)
{
	w->light = point_light(color(1,1,1), set_v_p(-10,10,-10,1));
	w->s[0] = set_sphere(0);
	w->s[0].m.color = color(0.8, 1, 0.6);
	w->s[0].m.diffuse = 0.7;
	w->s[0].m.specular = 0.2;
	
	w->s[1] = set_sphere(1);
	
	w->s[1].transform = set_transform(w->s[1].transform, scaling(0.5, 0.5, 0.5));
	w->max_obj = 2;
}

t_x_t	intersect_world(t_world w, t_ray r)
{
	t_x		x;
	t_x_t	x_t;
	int		i;
	int		hit_obj;

	i = 0;
	x.max_obj = 0;
	while (i < w.max_obj)
	{
		x.count[i] = 0;
		x.t[i].count = 0;
		x.t[i].t1 = 0;
		x.t[i].t2 = 0;
		x.t[i].obj = 0;
		x = intersect_sp(w.s[i], r, x);
		i++;
	}
	x_t = t_to_h(x, x_t);
	bubblesort(x_t.t, x_t.max_obj);
	return (x_t);
}

t_x_t	t_to_h(t_x x, t_x_t x_t)
{
	int i;
	int	j;

	i = 0;
	while (i < x.max_obj)
	{
		x_t.t[i].t = x.t[i].t1;
		x_t.t[i].count = x.t[i].count;
		x_t.t[i].obj = x.t[i].obj;
		i++;
	}
	j = i;
	i = 0;
	while (j < x.max_obj + x.max_obj)
	{
		x_t.t[j].t = x.t[i].t2;
		x_t.t[j].count = x.t[i].count;
		x_t.t[j].obj = x.t[i].obj;
		i++;
		j++;
	}
	x_t.max_obj = x.max_obj + x.max_obj;
	return (x_t);
}

void	bubblesort(t_t_o *num, int size)
{
	int		i;
	int		j;
	t_t_o	temp;

	i = 0;
	while (i < size - 1)
	{
		j = (size - 1);
		while (j > i)
		{
			if (num[j - 1].t > num[j].t)
			{
				temp = num[j - 1];
				num[j - 1] = num[j];
				num[j] = temp;
			}
			j--;
		}
		i++;
	}
}

t_i	intersection(float t, t_sp obj)
{
	t_i	i;

	i.t = t;
	i.obj = obj;
	return(i);
}

t_comps	prepare_computations(t_i i, t_ray r)
{
	t_comps	c;
	t_vec	normal;

	c.t = i.t;
	c.obj = i.obj;
	c.point = position(r, c.t);
	c.eyev = neg(r.d);
	if (normal_at(c.obj, c.point, &normal) == 0)
			printf("normal error");
	else
		c.normalv = normal;
	if (dot(c.normalv, c.eyev) < 0)
	{
		c.inside = 1;
		c.normalv = neg(c.normalv);
	}
	else
	{
		c.inside = 0;
	}
	c.over_point = add(c.point, mult(c.normalv, EPSILON));
	return(c);
}

t_color	shade_hit(t_world w, t_comps c)
{
	c.shadow = is_shadow(w, c.over_point);
	return (lighting(c.obj.m, w.light, c.point, c.eyev, c.normalv, c.shadow));
}

t_color	color_at(t_world w, t_ray r, int a, int b)
{
	t_x_t	x;
	int hit_obj;
	t_color col;
	t_comps comps;
	t_i i;

	hit_obj = 0;
	x = intersect_world(w, r);
	hit_obj = hit(x);
	if (hit_obj != -1)
	{
		i = intersection(x.t[hit_obj].t, w.s[x.t[hit_obj].obj]);
		comps = prepare_computations(i, r);
		col = shade_hit(w, comps);
	}
	else
	{
		col = color(0,0,0);
	}
	return(col);
}