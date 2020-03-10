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

# define WIN_W 150
# define WIN_H 150
# define EPSILON 0.00001

typedef struct		s_matrix
{
	float			m[4][4];
}					t_matrix;

typedef struct		s_vec
{
	float			c[4];
}					t_vec;

typedef struct		s_color
{
	float			r;
	float			g;
	float			b;

}					t_color;

typedef struct		s_material
{
	t_color			color;
	float			ambient;
	float			diffuse;
	float			specular;
	float			shininess;

}					t_material;

typedef struct		s_t_h
{
	float			t1;
	float			t2;
	int				obj;
	int				count;

}					t_t_h;

typedef struct		s_t_o
{
	float			t;
	int				obj;
	int				count;

}					t_t_o;

typedef struct		s_camera
{
	int				hsize;
	int				vsize;
	float			fov;
	t_matrix		transform;
	float			half_width;
	float			half_height;
	float			pixel_size;
}					t_camera;

typedef struct		s_x
{
	int				count[20];
	t_t_h			t[20];
	int				max_obj;
}					t_x;

typedef struct		s_x_t
{
	t_t_o			t[40];
	int				max_obj;
}					t_x_t;

typedef struct		s_sp
{
	t_vec			c;
	float			r;
	t_color			color;
	int				obj;
	t_matrix		transform;
	t_material		m;
}					t_sp;

typedef struct		s_i
{
	float			t;
	t_sp			obj;
}					t_i;

typedef struct		s_comps
{
	float			t;
	t_sp			obj;
	t_vec			point;
	t_vec			eyev;
	t_vec			normalv;
	int				inside;
	int				shadow;
	t_vec			over_point;
}					t_comps;

typedef struct		s_light
{
	t_color			intensity;
	t_vec			pos;
}					t_light;

typedef struct		s_ray
{
	t_vec			o;  //Origin
	t_vec			d;	//Direction
}					t_ray;

typedef struct		s_world
{
	t_light			light;
	t_sp			s[10];
	int				max_obj;
}					t_world;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Event		e;
	SDL_Renderer	*ren;
	SDL_Texture		*text;
	int				*img;
	int				run;
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
t_matrix			matrix_nul(t_matrix m);
t_matrix			translation(float x, float y, float z);
t_matrix			scaling(float x, float y, float z);
t_matrix			rotation_x(float r);
t_matrix			rotation_y(float r);
t_matrix			rotation_z(float r);
t_matrix			shearing(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y);

t_ray				set_ray(t_vec or, t_vec di);
t_vec				position(t_ray r, float t);

t_sp	set_sphere(int obj);
t_x	intersect_sp(t_sp s, t_ray r, t_x x);
//t_x	intersect_sp(t_sp s, t_ray r);
//t_xs				intersect_sp(t_sp s, t_ray r);
t_matrix	set_transform(t_matrix s, t_matrix m);

t_ray	transform(t_ray r, t_matrix m);

t_matrix	identity_matrix(void);

void	raycast(t_sdl *sdl, t_ray r, int x, int y, t_world w);
//void	raycast(t_sdl *sdl);

//light
int		normal_at(t_sp obj, t_vec world_point, t_vec *n);
//int		normal_at(t_matrix s, t_vec world_point, t_vec *n);
t_vec				reflect(t_vec in, t_vec normal);
t_light				point_light(t_color color, t_vec pos);
t_material			default_material(void);
t_color	lighting(t_material m, t_light l, t_vec pos, t_vec eye, t_vec norm_v, int shadow);
int					col_to_int(t_color c);
int	c(double r, double g, double b);

//world
void	default_world(t_world *w);
t_x_t	intersect_world(t_world w, t_ray r);
void	bubblesort(t_t_o *num, int size);
t_i	intersection(float t, t_sp obj);
t_comps	prepare_computations(t_i i, t_ray r);
//shade
t_color	shade_hit(t_world w, t_comps c);
t_color	color_at(t_world w, t_ray r, int a, int b);
int		hit(t_x_t x);

//view transform
t_matrix	view_transform(t_vec from, t_vec to, t_vec up);
t_matrix	default_view_transf(void);

//camera
t_camera    camera(float  hsize, float vsize, float fov);
t_ray   ray_for_pixel(t_camera camera, int px, int py);
void    render(t_sdl *sdl, t_camera camera, t_world world);
t_x_t	t_to_h(t_x x, t_x_t x_t);

//shadow
int	is_shadow(t_world w, t_vec	p);


#endif
