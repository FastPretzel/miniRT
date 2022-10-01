#include "minirt.h"

typedef struct s_vars
{
	double	diff_int;
	double	spec_int;
	t_vec	normal;
	t_color	color;
}	t_vars;

static t_vec	reflect(t_vec I, t_vec N)
{
	return (vec_sub(I, vec_mul(vec_cross(N, vec_cross(I, N)), 2.0)));
}

static void	init_shadow_ray(t_light *light, t_minirt *rt, t_ray *L, t_vec *n)
{
	L->orig = vec_add(rt->ray.phit, vec_mul(*n, 1e-4));
	L->dir = vec_norm(vec_sub(light->pos, L->orig));
	L->t = INFINITY;
}

static int	is_shaded(t_minirt *rt, t_light *light,
		t_vec *normal, t_object *self)
{
	t_list		*lst;
	t_object	*obj;
	double		tnear;
	t_ray		l;

	lst = rt->obj_lst;
	init_shadow_ray(light, rt, &l, normal);
	tnear = vec_len(vec_sub(light->pos, l.orig));
	while (lst)
	{
		obj = (t_object *)lst->content;
		if (obj != self && obj->intersect(obj->params, &l) && l.t < tnear)
			return (1);
		lst = lst->next;
	}
	return (0);
}

static void	calc_vars(t_vars *v, t_light *light, t_minirt *rt, t_object *obj)
{
	t_vec	light_dir;
	int		vis;

	vis = !is_shaded(rt, light, &v->normal, obj);
	light_dir = vec_norm(vec_sub(light->pos, rt->ray.phit));
	v->diff_int = vis * light->intens * \
		fmax(0.f, vec_dot(light_dir, v->normal));
	v->spec_int = vis * pow(fmax(0.f, vec_dot(reflect(light_dir, v->normal),
					vec_neg(rt->ray.dir))), obj->mat.spec_exp) * light->intens;
	v->color = col_add(v->color, col_mul_vec(light->color,
				col_add(col_mul(obj->mat.color, v->diff_int * \
				obj->mat.albedo[0]), col_mul((t_color){1, 1, 1},
						v->spec_int * obj->mat.albedo[1]))));
}

t_color	calc_light(t_object *obj, t_minirt *rt)
{
	t_list	*lst;
	t_vars	vars;

	vars.normal = obj->get_normal(&(rt->ray), obj->params);
	lst = rt->light_lst;
	vars.diff_int = 0;
	vars.spec_int = 0;
	vars.color = col_mul(obj->mat.color, AMBIENT);
	while (lst)
	{
		calc_vars(&vars, (t_light *)lst->content, rt, obj);
		lst = lst->next;
	}
	return (vars.color);
}

void	init_light(t_minirt *minirt)
{
	t_light	*light;
	t_light	*light2;

	light = malloc(sizeof(t_light));
	light2 = malloc(sizeof(t_light));
	light->pos = (t_vec){0, 0, 2};
	light2->pos = (t_vec){4, 2, 2};
	light->color = get_color(255, 255, 255);
	light2->color = get_color(255, 255, 255);
	light->intens = 0.7;
	light2->intens = 1.0;
	/*ft_lstadd_back(&(minirt->light_lst), ft_lstnew((void *)light));*/
	ft_lstadd_back(&(minirt->light_lst), ft_lstnew((void *)light2));
}
