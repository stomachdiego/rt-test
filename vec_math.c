/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:19:19 by aannara           #+#    #+#             */
/*   Updated: 2019/11/25 14:22:48 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	add(t_vec a1, t_vec a2)
{
	t_vec	b;

	b.c[0] = a1.c[0] + a2.c[0];
	b.c[1] = a1.c[1] + a2.c[1];
	b.c[2] = a1.c[2] + a2.c[2];
	b.c[3] = a1.c[3] + a2.c[3];
	return (b);
}

t_vec	sub(t_vec a1, t_vec a2)
{
	t_vec	b;

	b.c[0] = a1.c[0] - a2.c[0];
	b.c[1] = a1.c[1] - a2.c[1];
	b.c[2] = a1.c[2] - a2.c[2];
	b.c[3] = a1.c[3] - a2.c[3];
	return (b);
}

t_vec	neg(t_vec a)
{
	a.c[0] = -a.c[0];
	a.c[1] = -a.c[1];
	a.c[2] = -a.c[2];
	a.c[3] = -a.c[3];
	return (a);
}

t_vec	mult(t_vec a, float b)
{
	a.c[0] = a.c[0] * b;
	a.c[1] = a.c[1] * b;
	a.c[2] = a.c[2] * b;
	a.c[3] = a.c[3] * b;
	return (a);
}

t_vec	divi(t_vec a, float b)
{
	a.c[0] = a.c[0] / b;
	a.c[1] = a.c[1] / b;
	a.c[2] = a.c[2] / b;
	a.c[3] = a.c[3] / b;
	return (a);
}

float	magnitude(t_vec a)
{
	return (sqrt(a.c[0] * a.c[0] + a.c[1] * a.c[1] + a.c[2] * a.c[2] + a.c[3] * a.c[3]));
}

t_vec	normalize(t_vec v)
{
	float mg = magnitude(v);
	v.c[0] = v.c[0] / mg;
	v.c[1] = v.c[1] / mg;
	v.c[2] = v.c[2] / mg;
	v.c[3] = v.c[3] / mg;
	return (v);
}

float	dot(t_vec a, t_vec b)
{
	return (a.c[0] * b.c[0] + a.c[1] * b.c[1] + a.c[2] * b.c[2] + a.c[3] * b.c[3]);
}

t_vec	cross(t_vec a, t_vec b)
{
	return(set_v_p(a.c[1] * b.c[2] - a.c[2] * b.c[1], a.c[2] * b.c[0] - a.c[0] * b.c[2], a.c[0] * b.c[1] - a.c[1] * b.c[0], 0));
}
/*t_vec	add(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.e[0] = v1.e[0] + v2.e[0];
	v.e[1] = v1.e[1] + v2.e[1];
	v.e[2] = v1.e[2] + v2.e[2];
	return (v);
}

t_vec	sub(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.e[0] = v1.e[0] - v2.e[0];
	v.e[1] = v1.e[1] - v2.e[1];
	v.e[2] = v1.e[2] - v2.e[2];
	return (v);
}

void	suba(t_vec *v1, t_vec *v2)
{
	v1->e[0] -= v2->e[0];
	v1->e[1] -= v2->e[1];
	v1->e[2] -= v2->e[2];
}

t_vec	mulf(t_vec v1, double f)
{
	t_vec	v;

	v.e[0] = v1.e[0] * f;
	v.e[1] = v1.e[1] * f;
	v.e[2] = v1.e[2] * f;
	return (v);
}


t_vec	op_del(t_vec v1, double f)
{
	t_vec	v;

	v.e[0] = v1.e[0] / f;
	v.e[1] = v1.e[1] / f;
	v.e[2] = v1.e[2] / f;
	return (v);
}

void	make_unit_vector(t_vec *v)
{
	double	k;

	k = 1.0 / length(*v);
	*v = mulf(*v, k);
}*/
