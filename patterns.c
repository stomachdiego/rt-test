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

void   stripe_pattern_pl(t_color a, t_color b, t_plane *pl)
{
    pl->m.p.a = a;
    pl->m.p.b = b;
    pl->m.p.transform = identity_matrix();
    pl->m.pattern = 1;
    pl->m.pattern_at = &stripe_at_pl;
}

void   stripe_pattern_sp(t_color a, t_color b, t_sp *s)
{
    s->m.p.a = a;
    s->m.p.b = b;
    s->m.p.transform = identity_matrix();
    s->m.pattern = 1;
    s->m.pattern_at = &stripe_at_sp;
}

void   gradient_pattern_pl(t_color a, t_color b, t_plane *pl)
{
    pl->m.p.a = a;
    pl->m.p.b = b;
    pl->m.p.transform = identity_matrix();
    pl->m.pattern = 1;
    pl->m.pattern_at = &gradient_at_pl;
}

void   gradient_pattern_sp(t_color a, t_color b, t_sp *s)
{
    s->m.p.a = a;
    s->m.p.b = b;
    s->m.p.transform = identity_matrix();
    s->m.pattern = 1;
    s->m.pattern_at = &gradient_at_sp;
}

void   ring_pattern_pl(t_color a, t_color b, t_plane *pl)
{
    pl->m.p.a = a;
    pl->m.p.b = b;
    pl->m.p.transform = identity_matrix();
    pl->m.pattern = 1;
    pl->m.pattern_at = &ring_at_pl;
}

void   ring_pattern_sp(t_color a, t_color b, t_sp *s)
{
    s->m.p.a = a;
    s->m.p.b = b;
    s->m.p.transform = identity_matrix();
    s->m.pattern = 1;
    s->m.pattern_at = &ring_at_sp;
}

void   checker_pattern_pl(t_color a, t_color b, t_plane *pl)
{
    pl->m.p.a = a;
    pl->m.p.b = b;
    pl->m.p.transform = identity_matrix();
    pl->m.pattern = 1;
    pl->m.pattern_at = &checker_at_pl;
}

void   checker_pattern_sp(t_color a, t_color b, t_sp *s)
{
    s->m.p.a = a;
    s->m.p.b = b;
    s->m.p.transform = identity_matrix();
    s->m.pattern = 1;
    s->m.pattern_at = &checker_at_sp;
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
    if (realmod(floor(point.c[0]), 2) == 0)
        return (p.a);
    else
        return (p.b);
}

t_color gradient_at(t_pattern p, t_vec point)
{
    t_color distance;
    double  fraction;

    distance = sub_col(p.b, p.a);
    fraction = point.c[0] - floor(point.c[0]);
    return (add_col(p.a, mult_col(distance, fraction)));
}

t_color ring_at(t_pattern p, t_vec point)
{
    if (realmod(floor(sqrt((point.c[0] * point.c[0]) + (point.c[2] * point.c[2]))), 2) == 0)
        return (p.a);
    else
        return (p.b);
}

t_color checker_at(t_pattern p, t_vec point)
{
    if ((realmod(floor(point.c[0]) + floor(point.c[1]) + floor(point.c[2]), 2)) == 0)
        return (p.a);
    else
        return (p.b);
}
