/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:08:48 by sdiego            #+#    #+#             */
/*   Updated: 2020/03/08 18:08:49 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_camera    camera(double  hsize, double vsize, double fov)
{
    t_camera    c;
    double       half_view;
    double       aspect;

    c.hsize = hsize;
    c.vsize = vsize;
    c.fov = fov;
    c.transform = identity_matrix();
    half_view = tanf(c.fov / 2);
    aspect = hsize / vsize;
    if (aspect >= 1)
    {
        c.half_width = half_view;
        c.half_height = half_view / aspect;
    }
    else
    {
        c.half_width = half_view * aspect;
        c.half_height = half_view;
    }
    c.pixel_size = (c.half_width * 2) / c.hsize;
    return (c);
}

t_ray   ray_for_pixel(t_camera camera, int px, int py)
{
    double   xoffset;
    double   yoffset;
    double   world_x;
    double   wolrd_y;
    t_vec   pixel;
    t_vec   origin;
    t_vec   direction;

    xoffset = (px + 0.5) * camera.pixel_size;
    yoffset = (py + 0.5) * camera.pixel_size;
    world_x = camera.half_width - xoffset;
    wolrd_y = camera.half_height - yoffset;

    if (matrix_inverse_test(camera.transform) == 1)
    {
        pixel = matrix_mult_v_p(matrix_inverse(camera.transform), set_v_p(world_x, wolrd_y, -1 , 1));
        origin = matrix_mult_v_p(matrix_inverse(camera.transform), set_v_p(0, 0, 0, 1));
        direction = normalize(sub(pixel, origin));
    }
    else
        printf("error ray_for_pixel\n");
    return (set_ray(origin, direction));
}

void    render(t_sdl *sdl, t_camera camera, t_world world)
{
    int     x;
    int     y;
    t_ray   r;
    t_color col;

    y = 0;
    while (y < camera.vsize)
    {
        x = 0;
        while (x < camera.hsize)
        {
            r = ray_for_pixel(camera, x, y);
            col = color_at(world, r, x, y);
            sdl->img[y * camera.hsize + x] = col_to_int(col);
            x++;
        }
        y++;
    }
}
