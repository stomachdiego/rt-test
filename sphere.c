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

t_sp	set_sphere(t_vec c, float r, int color, int obj)
{
	t_sp	s;

	s.c = c;
	s.r = r;
	s.color = color;
	s.obj = obj;
	s.transform = identity_matrix();
	return (s);
}

t_xs	intersect_sp(t_sp s, t_ray r)
{
	t_xs	xs;
	float	a;
	float	b;
	float	c;
	t_vec	sp_to_ray;
	float	disc;
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
			xs.count[s.obj] = 0;
			return (xs);
		}
		xs.t1[s.obj] = ((-b -sqrt(disc)) / (2 * a));
		xs.t2[s.obj] = ((-b +sqrt(disc)) / (2 * a));
		if (xs.t1[s.obj] > xs.t2[s.obj])
		{
			a = xs.t1[s.obj];
			xs.t1[s.obj] = xs.t2[s.obj];
			xs.t2[s.obj] = a;
		}
		xs.count[s.obj] = 2;
		xs.obj[s.obj] = s.obj;
		xs.max_obj = s.obj;
		xs.color[s.obj] = s.color;
		return (xs);
	}
	xs.count[s.obj] = 0;
	return(xs);
}

/*t_vec		getNormal(t_vec pi, t_sphere sp)
{
	return (op_del(sub(pi, sp.c), sp.r));
}

t_sphere	sphere(t_vec i, double j)
{
	t_sphere	sp;

	sp.c = i;
	sp.r = j;
	return (sp);
}

int		sphere_intersect(t_ray ray, double *t, t_sphere sp)
{
	t_vec	o;
	t_vec	d;
	t_vec	oc;


	o = ray.o;
	d = ray.d;
	oc = sub(o, sp.c);
	double b = 2 * dot(oc, d);
	double c = dot(oc, oc) - sp.r * sp.r;
	double disc = b * b - 4 * c;
	if (disc < 0)
		return (0);
	else
	{
		disc = sqrt(disc);
		double t0 = -b - disc;
		double t1 = -b + disc;
		if (t0 < t1)
			*t = t0;
		else
			*t = t1;
		return (1);
	}

}*/
