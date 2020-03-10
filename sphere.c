/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:54:30 by sdiego            #+#    #+#             */
/*   Updated: 2020/02/26 14:54:31 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_sp	set_sphere(int obj)
{
	t_sp	s;

	s.c = set_v_p(0, 0, 0, 1);
	s.r = 1;
	//s.color = color;
	s.obj = obj;
	s.transform = identity_matrix();
	s.m = default_material();
	return (s);
}

t_x	intersect_sp(t_sp s, t_ray r, t_x x)
{
	double	a;
	double	b;
	double	c;
	t_vec	sp_to_ray;
	double	disc;
	t_ray	ray2;

	if (matrix_inverse_test(s.transform) == 1)
	{
		ray2 = transform(r, matrix_inverse(s.transform));

		sp_to_ray = sub(ray2.o, s.c);

		a = dot(ray2.d, ray2.d);
		b = 2 * dot(ray2.d, sp_to_ray);
		c = dot(sp_to_ray, sp_to_ray) - 1;

		disc = (b * b) - 4 * a * c;

		if (disc < 0)
		{
			/*x.t[s.obj].t = 0;
			x.t[s.obj + 1].t = 0;
			x.count[s.obj] = 0;
			x.t[s.obj].obj = s.obj;
			x.t[s.obj].count = 0;
			x.t[s.obj + 1].obj = s.obj;
			x.t[s.obj + 1].count = 0;*/
			//x.max_obj = 0;
			x.max_obj = x.max_obj + 1;
			//printf(" dics < 0");
			return (x);
		}
		else
		{
			x.t[s.obj].t1 = ((-b -sqrt(disc)) / (2 * a));
			x.t[s.obj].obj = s.obj;
			x.t[s.obj].count = 2;
			x.t[s.obj].t2 = ((-b +sqrt(disc)) / (2 * a));
			x.count[s.obj] = 2;
			x.max_obj = x.max_obj + 1;
			if (x.t[s.obj].t1 > x.t[s.obj].t2)
			{
				a = x.t[s.obj].t1;
				x.t[s.obj].t1 = x.t[s.obj].t2;
				x.t[s.obj].t2 = a;
			}
			return (x);
		}
	}
	printf("matrix_inverse_test error in intersect_sp\n");
	//x.count[s.obj] = 0;
	x.max_obj = x.max_obj + 1;
	//x.max_obj = 0;
	return(x);
}

int		normal_at(t_sp obj, t_vec world_point, t_vec *n)
{
	t_vec object_point;
	t_vec object_normal;
	t_vec	world_normal;

	if (matrix_inverse_test(obj.transform) == 1)
	{
		object_point = matrix_mult_v_p(matrix_inverse(obj.transform), world_point);
		object_normal = sub(object_point, set_v_p(0, 0, 0, 1));
		world_normal = matrix_mult_v_p(matrix_transposing(matrix_inverse(obj.transform)), object_normal);
		world_normal.c[3] = 0;
		*n = normalize(world_normal);
		return (1);
	}
	printf("error normal_at");
	return(0);
}

t_vec	reflect(t_vec in, t_vec normal)
{
	t_vec a;
	t_vec b;

	b = mult(normal, (2 * dot(in, normal)));
	a = sub(in, b);
	return(a);
}
