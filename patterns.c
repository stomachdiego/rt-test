/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 14:28:16 by sdiego            #+#    #+#             */
/*   Updated: 2020/03/15 14:28:18 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_pattern   stripe_pattern(t_color a, t_color b)
{
    t_pattern   p;

    p.a = a;
    p.b = b;
    p.transform = identity_matrix();
    return (p);
}

double  realmod(double x, double p)
{
    if (x < 0)
        return (fmod((fmod(x, p) + p), p));
    else
        return (fmod(x, p));
}

t_color stripe_at(t_pattern p, t_vec point)
{
    if ((int)realmod(point.c[0], 2) == 0)
        return (p.a);
    else
        return (p.b);
}
