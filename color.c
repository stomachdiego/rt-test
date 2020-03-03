/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 15:32:12 by sdiego            #+#    #+#             */
/*   Updated: 2020/03/01 15:32:13 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	color(float r, float g, float b)
{
	t_color c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color	add_col(t_color a1, t_color a2)
{
	t_color	b;

	b.r = a1.r + a2.r;
	b.g = a1.g + a2.g;
	b.b = a1.b + a2.b;
	return (b);
}

t_color	sub_col(t_color a1, t_color a2)
{
	t_color	b;

	b.r = a1.r - a2.r;
	b.g = a1.g - a2.g;
	b.b = a1.b - a2.b;
	return (b);
}

t_color	mult_col(t_color a, float b)
{
	a.r = a.r * b;
	a.g = a.g * b;
	a.b = a.b * b;
	return (a);
}

t_color	hadamard_prod(t_color a1, t_color a2)
{
	t_color	b;

	b.r = a1.r * a2.r;
	b.g = a1.g * a2.g;
	b.b = a1.b * a2.b;
	return (b);
}
