/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:54:55 by sdiego            #+#    #+#             */
/*   Updated: 2020/03/11 15:54:57 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_plane set_plane()
{
	t_plane s;

	s.c = set_v_p(0, 0, 0, 1);
	//s.r = 1;
	s.transform = identity_matrix();
	s.m = default_material();
	return (s);
}

int		normal_at_pl(void *v_s, t_vec world_point, t_vec *n)
{
	t_plane *s;
	t_vec   object_point;
	t_vec   object_normal;
	t_vec	world_normal;
	s = (t_plane*)v_s;
	if (matrix_inverse_test(s->transform) == 1)
	{
		object_point = matrix_mult_v_p(matrix_inverse(s->transform), world_point);
		object_normal = set_v_p(0,1,0,0);
		world_normal = matrix_mult_v_p(matrix_transposing(matrix_inverse(s->transform)), object_normal);
		world_normal.c[3] = 0;
		*n = normalize(world_normal);
		return (1);
	}
	printf("error normal_at");
	return(0);
}

t_x_t	intersect_pl(void *v_s, t_ray r, t_x_t x, int obj_n)
{
	double	a;
	double	b;
	double	c;
	t_vec	sp_to_ray;
	double	disc;
	t_ray	ray2;
	t_plane *s;

	s = (t_plane*)v_s;

	if (matrix_inverse_test(s->transform) == 1)
	{
		ray2 = transform(r, matrix_inverse(s->transform));

		if (fabs(ray2.d.c[1]) < EPSILON)
        {
            //x.max_obj = x.max_obj + 1;
            return (x);
        }
        x.t[x.max_obj].t = -ray2.o.c[1] / ray2.d.c[1];
		x.t[x.max_obj].obj = obj_n;
		x.t[x.max_obj].count = 2;
		x.max_obj = x.max_obj + 1;
        return (x);
	}
	printf("matrix_inverse_test error in intersect_sp\n");
	//x.max_obj = x.max_obj + 1;
	return(x);
}

t_color	shade_hit_pl(t_world w, t_comps c)
{
	c.shadow = is_shadow(w, c.over_point);
	t_plane *s;
	s = (t_plane*)w.obj_ar[c.obj].obj;
	return (lighting(s->m, w, c));
	//return (color(0,0,0));
}

t_color	stripe_at_pl(t_pattern p, void *obj, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;
	t_plane	*s;

	s = (t_plane*)obj;
	if (matrix_inverse_test(s->transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(s->transform), wolrd_point);
	else
		printf("matrix s stripe_at_sp error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe_at_sp error\n"); 
	return(stripe_at(p, pattern_point));
}

/*t_color	lighting_pl(t_material m, t_world w, t_comps c)
{
	t_color	effective_color;
	t_vec	light_v;
	t_color ambient;
	double	light_dot_normal;
	t_color	diffuse;
	t_color specular;
	t_vec	reflect_v;
	double	reflect_dot_eye;
	double	factor;

	if (m.pattern == 1)
		m.color = (*m.p.pattern_at)(m.p, w.obj_ar[c.obj].obj, c.point);
	
	effective_color = hadamard_prod(m.color, w.light.intensity);
	light_v = normalize(sub(w.light.pos, c.point));
	ambient = mult_col(effective_color, m.ambient);
	light_dot_normal = dot(light_v, c.normalv);
	if (c.shadow == 0)
	{
		if (light_dot_normal < 0)
		{
			diffuse = color(0,0,0);
			specular = color(0,0,0);
		}
		else
		{
			diffuse = mult_col(mult_col(effective_color, m.diffuse), light_dot_normal);
	
			reflect_v = reflect(neg(light_v), c.normalv);
			reflect_dot_eye = dot(reflect_v, c.eyev);
			if (reflect_dot_eye <= 0)
				specular = color(0,0,0);
			else
			{
				factor = powf(reflect_dot_eye, m.shininess);
				specular = mult_col(mult_col(w.light.intensity, m.specular), factor);
			}
		}
		return (add_col(add_col(ambient, diffuse), specular));
	}
	else
		return(ambient);
}*/