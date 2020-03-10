/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:38:47 by sdiego            #+#    #+#             */
/*   Updated: 2020/03/03 15:38:49 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	position(t_ray r, double t)
{
	t_vec a;
	t_vec b;

	a = mult(r.d, t);
	b = add(r.o, a);
	return(b);
}

t_ray	set_ray(t_vec or, t_vec di)
{
	t_ray r;

	r.o = or;
	r.d = di;
	return (r);
}
