/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:49:00 by sdiego            #+#    #+#             */
/*   Updated: 2020/03/02 17:49:01 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_matrix	translation(float x, float y, float z)
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[i][j] = 0;
			j++;
		}
		i++;
	}
	m.m[0][0] = 1;
	m.m[1][1] = 1;
	m.m[2][2] = 1;
	m.m[3][3] = 1;
	m.m[0][3] = x;
	m.m[1][3] = y;
	m.m[2][3] = z;
	return (m);
}

t_matrix	scaling(float x, float y, float z)
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[i][j] = 0;
			j++;
		}
		i++;
	}
	m.m[0][0] = x;
	m.m[1][1] = y;
	m.m[2][2] = z;
	m.m[3][3] = 1;
	return (m);
}

t_matrix	rotation_x(float r)
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[i][j] = 0;
			j++;
		}
		i++;
	}
	m.m[0][0] = 1;
	m.m[1][1] = cos(r);
	m.m[1][2] = -sin(r);
	m.m[2][1] = sin(r);
	m.m[2][2] = cos(r);
	m.m[3][3] = 1;
	return (m);
}

t_matrix	rotation_y(float r)
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[i][j] = 0;
			j++;
		}
		i++;
	}
	m.m[0][0] = cos(r);
	m.m[0][2] = sin(r);
	m.m[1][1] = 1;
	m.m[2][0] = -sin(r);
	m.m[2][2] = cos(r);
	m.m[3][3] = 1;
	return (m);
}

t_matrix	rotation_z(float r)
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[i][j] = 0;
			j++;
		}
		i++;
	}
	m.m[0][0] = cos(r);
	m.m[0][1] = -sin(r);
	m.m[1][0] = sin(r);
	m.m[1][1] = cos(r);
	m.m[2][2] = 1;
	m.m[3][3] = 1;
	return (m);
}

t_matrix	shearing(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y)
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[i][j] = 0;
			j++;
		}
		i++;
	}
	m.m[0][0] = 1;
	m.m[1][1] = 1;
	m.m[2][2] = 1;
	m.m[3][3] = 1;
	m.m[0][1] = x_y;
	m.m[0][2] = x_z;
	m.m[1][0] = y_x;
	m.m[1][2] = y_z;
	m.m[2][0] = z_x;
	m.m[2][1] = z_y;
	return (m);
}

t_ray	transform(t_ray r, t_matrix m)
{
	t_ray r2;

	r2.o = matrix_mult_v_p(m, r.o);
	r2.d = matrix_mult_v_p(m, r.d);
	return(r2);
}

t_matrix	set_transform(t_matrix s, t_matrix m)
{
	s = matrix_mult(m, s);

	return (s);
}