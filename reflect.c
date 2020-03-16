/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 16:24:47 by sdiego            #+#    #+#             */
/*   Updated: 2020/03/16 16:24:48 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color reflected_color(t_world w, t_comps c, int remaining)
{
    t_ray reflect_ray;
    t_color col;
    if (remaining <= 0)
    {
        return (color(0,0,0));
    }
    if (w.obj_ar[c.obj].m->reflective > 0 && w.obj_ar[c.obj].m->reflective <= 1)
    {
        reflect_ray = set_ray(c.over_point, c.reflectv);
        col = color_at(w, reflect_ray, remaining - 1);
        return (mult_col(col, w.obj_ar[c.obj].m->reflective));
    }
    else
    {
        return (color(0,0,0));
    }
}
