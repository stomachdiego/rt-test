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

t_vec	set_v_p(double a, double b, double c, double d)
{
	t_vec	t;

	t.c[0] = a;
	t.c[1] = b;
	t.c[2] = c;
	t.c[3] = d;
	return (t);
}

int	check_eps(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	return (0);
}
