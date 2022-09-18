#include "minirt.h"

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

static int	is_shaded(t_minirt *rt, t_light *light, t_vec *normal, t_object *self)
{
	t_list		*lst;
	t_object	*obj;
	double		tnear;
	t_ray		L;

	lst = rt->obj_lst;
	(void)self;
	init_shadow_ray(light, rt, &L, normal);
	tnear = vec_len(vec_sub(light->pos, L.orig));
	while (lst)
	{
		obj = (t_object *)lst->content;
		if (obj != self && obj->intersect(obj->params, &L) && L.t < tnear)
		{
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

t_color	calc_light(t_object *obj, t_minirt *rt)
{
	double	diff_int;
	double	spec_int;
	t_list	*tmp;
	t_vec	normal;
	t_color	color;

	normal = obj->get_normal(&(rt->ray), obj->params);
	tmp = rt->light_lst;
	diff_int = 0;
	spec_int = 0;
	color = col_mul(obj->mat.color, AMBIENT);
	while (tmp)
	{
		int vis = !is_shaded(rt, (t_light *)tmp->content, &normal, obj);
		/*vis = 1;*/
		t_vec	light_dir = vec_norm(vec_sub(((t_light *)tmp->content)->pos, rt->ray.phit));
		diff_int += vis * ((t_light *)tmp->content)->intens * 
			fmax(0.f, vec_dot(light_dir, normal));
		spec_int += vis * pow(fmax(0.f, vec_dot(reflect(light_dir, normal), 
			vec_neg(rt->ray.dir))), obj->mat.spec_exp) * ((t_light *)tmp->content)->intens;
		tmp = tmp->next;
	}
	color = col_add(color, col_add(col_mul(obj->mat.color,diff_int * 
			obj->mat.albedo[0]), col_mul((t_color){1, 1, 1}, spec_int * obj->mat.albedo[1])));
	return (color);
}

void	init_light(t_minirt *minirt)
{
	t_light	*light;
	t_light	*light2;

	light = malloc(sizeof(t_light));
	light2 = malloc(sizeof(t_light));
	light->pos = (t_vec){0, 0, 2};
	light2->pos = (t_vec){-2, 0, 2};
	light->intens = 0.7;
	light2->intens = 1.0;
	/*ft_lstadd_back(&(minirt->light_lst), ft_lstnew((void *)light));*/
	ft_lstadd_back(&(minirt->light_lst), ft_lstnew((void *)light2));
}
