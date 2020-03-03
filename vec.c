/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:13:49 by aannara           #+#    #+#             */
/*   Updated: 2019/11/25 14:27:52 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	set_v_p(float a, float b, float c, float d)
{
	t_vec	t;

	t.c[0] = a;
	t.c[1] = b;
	t.c[2] = c;
	t.c[3] = d;
	return (t);
}

int	check_eps(float a, float b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	return (0);
}

/*double	length(t_vec v)
{
	return (sqrt(v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]));
}

double	sq_l(t_vec v)
{
	return (v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]);
}

double	dot(t_vec v1, t_vec v2)
{
	return (v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2]);
}

t_vec	reflect(t_vec d, t_vec n)
{
	t_vec	res;
	t_vec	t;
	double	tf;

	tf = dot(d, n);
	t = mulf(n, tf);
	t = mulf(t, 2);
	res = sub(d, t);
	return (res);
}

t_vec	normalize(t_vec a)
{
	double mg;

	mg = sqrt(a.e[0] * a.e[0] + a.e[1] * a.e[1] + a.e[2] * a.e[2]);
	return (op_del(a, mg));
}*/