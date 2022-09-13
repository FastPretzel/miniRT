#include "minirt.h"

static t_vec	reflect(t_vec I, t_vec N)
{
	return (vec_sub(I, vec_mul(vec_cross(N, vec_cross(I, N)), 2.0)));
}

static void	init_shadow_ray(t_light *light, t_minirt *rt, t_ray *L, t_vec *n)
{
	/*L->orig = rt->ray.phit;*/
	L->orig = vec_add(rt->ray.phit, vec_mul(*n, 1e-4));
	/*L->dir = vec_norm(vec_sub(L->orig, light->pos));*/
	L->dir = vec_sub(light->pos, L->orig);
	L->t = vec_len(vec_sub(light->pos, L->orig));
}

static int	is_shaded(t_minirt *rt, t_ray *L, t_vec *normal, t_object *nearest)
{
	t_list		*lst;
	t_object	*obj;
	double		tnear;

	lst = rt->obj_lst;
	(void)nearest;
	(void)normal;
	tnear = L->t;
	/*L->orig = vec_add(L->orig, vec_mul(*normal, 1e-4));*/
	if (vec_dot(vec_norm(L->dir), *normal) < 1e-4)
		return (0);
	while (lst)
	{
		obj = (t_object *)lst->content;
		if (obj->intersect(obj->params, L) && L->t < tnear)
		{
			/*if (nearest->get_normal == &get_norm_plane)*/
				/*printf("%f, %f, %f\n%f %f\n", ((t_material)obj->mat).color.r*255, ((t_material)obj->mat).color.g *255, ((t_material)obj->mat).color.b*255, L->t, tnear);*/
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
	t_ray	L;
	t_color	color;

	normal = obj->get_normal(rt->ray, obj->params);
	tmp = rt->light_lst;
	diff_int = 0;
	spec_int = 0;
	color = col_mul(obj->mat.color, AMBIENT);
	while (tmp)
	{
		init_shadow_ray((t_light *)tmp->content, rt, &L, &normal);
		int vis = !is_shaded(rt, &L, &normal, obj);
		vis = 1;
		diff_int += vis * ((t_light *)tmp->content)->intens * fmax(0.f, vec_dot(normal, \
					vec_norm(vec_sub(rt->ray.phit,((t_light *)tmp->content)->pos))));
		spec_int += vis * pow(fmax(0.f, vec_dot(reflect(vec_norm(vec_sub(rt->ray.phit,((t_light *)tmp->content)->pos)), \
							normal), rt->ray.dir)), obj->mat.spec_exp) * ((t_light *)tmp->content)->intens;
		tmp = tmp->next;
	}
	/*return (col_add(col_mul(obj->mat.color,diff_int * obj->mat.albedo[0]), \*/
				/*col_mul((t_color){1, 1, 1}, spec_int * obj->mat.albedo[1])));*/
	color = col_add(color, col_add(col_mul(obj->mat.color,diff_int * obj->mat.albedo[0]), \
				col_mul((t_color){1, 1, 1}, spec_int * obj->mat.albedo[1])));
	return (color);
}

void	init_light(t_minirt *minirt)
{
	t_light	*light;
	t_light	*light2;

	light = malloc(sizeof(t_light));
	light2 = malloc(sizeof(t_light));
	light->pos = (t_vec){5, 0, 2};
	light2->pos = (t_vec){5, 2, -2};
	light->intens = 1.0;
	light2->intens = 1.0;
	ft_lstadd_back(&(minirt->light_lst), ft_lstnew((void *)light));
	ft_lstadd_back(&(minirt->light_lst), ft_lstnew((void *)light2));
}
