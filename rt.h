/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:41 by sdiego            #+#    #+#             */
/*   Updated: 2020/02/26 14:12:43 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <unistd.h>
# include <SDL.h>
# include <math.h>

# define WIN_W 900
# define WIN_H 550
# define EPSILON 0.00001

typedef struct		s_matrix
{
	float			m[4][4];
}					t_matrix;

typedef struct		s_vec
{
	float			c[4];
}					t_vec;

typedef struct		s_xs
{
	int				count[100];
	float			t1[100];
	float			t2[100];
	int				obj[100];
	int				max_obj;
}					t_xs;

typedef struct		s_sp
{
	t_vec			c;
	float			r;
	int				color;
	int				obj;
}					t_sp;

typedef struct		s_color
{
	float			r;
	float			g;
	float			b;

}					t_color;

typedef struct		s_ray
{
	t_vec			o;  //Origin
	t_vec			d;	//Direction
}					t_ray;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Event		e;
	SDL_Renderer	*ren;
	SDL_Texture		*text;
	int				*img;
	int				run;
	t_color			canvas[WIN_W][WIN_H];
}					t_sdl;

int					check_eps(float a, float b);
t_vec				add(t_vec a1, t_vec a2);
t_vec				set_v_p(float a, float b, float c, float d);
t_vec				sub(t_vec a1, t_vec a2);
t_vec				neg(t_vec a);
t_vec				mult(t_vec a, float b);
t_vec				divi(t_vec a, float b);
float				magnitude(t_vec a);
t_vec				normalize(t_vec v);
float				dot(t_vec a, t_vec b);
t_vec				cross(t_vec a, t_vec b);
t_color				color(float r, float g, float b);
t_color				add_col(t_color a1, t_color a2);
t_color				sub_col(t_color a1, t_color a2);
t_color				mult_col(t_color a, float b);
t_color				hadamard_prod(t_color a1, t_color a2);
int					identic_m_4(t_matrix a, t_matrix b);
t_matrix			matrix_mult(t_matrix a, t_matrix b);
t_vec				matrix_mult_v_p(t_matrix a, t_vec b);
t_matrix			matrix_identity(t_matrix a);
t_vec				matrix_identity_v_p(t_vec a);
t_matrix			matrix_transposing(t_matrix a);
float				matrix_determinant_2(t_matrix a);
t_matrix			matrix_submatrix(t_matrix m, int a, int b, int size);
float				matrix_minor(t_matrix m, int a, int b, int size);
float				matrix_cofactor(t_matrix m, int a, int b, int size);
float				matrix_determinant_3(t_matrix m);
float				matrix_determinant_4(t_matrix m);
int					matrix_inverse_test(t_matrix m);
t_matrix			matrix_inverse(t_matrix m);
t_matrix			translation(float x, float y, float z);
t_matrix			scaling(float x, float y, float z);
t_matrix			rotation_x(float r);
t_matrix			rotation_y(float r);
t_matrix			rotation_z(float r);
t_matrix			shearing(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y);

t_ray				set_ray(t_vec or, t_vec di);
t_vec				position(t_ray r, float t);

t_sp				set_sphere(t_vec c, float r, int color, int obj);
t_xs				intersect_sp(t_sp s, t_ray r, t_matrix m);
t_sp				set_transform_sp(t_sp s, t_matrix m);

t_ray	transform(t_ray r, t_matrix m);

#endif
