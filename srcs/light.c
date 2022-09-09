#include "minirt.h"

static t_vec	reflect(t_vec I, t_vec N)
{
	return (vec_sub(I, vec_mul(vec_cross(N, vec_cross(I, N)), 2.0)));
}

t_color	calc_light(t_object *obj, t_minirt *rt)
{
	double	diff_int;
	double	spec_int;
	t_list	*tmp;
	t_vec	normal;

	/*normal = vec_norm(vec_sub(rt->ray.phit, ((t_sphere *)obj->params)->orig));*/
	normal = obj->get_normal(rt->ray, obj->params);
	tmp = rt->light_lst;
	diff_int = 0;
	spec_int = 0;
	while (tmp)
	{
		diff_int += ((t_light *)tmp->content)->intens * fmax(0.f, vec_dot(normal, \
					vec_norm(vec_sub(rt->ray.phit,((t_light *)tmp->content)->pos))));
		spec_int += pow(fmax(0.f, vec_dot(reflect(vec_norm(vec_sub(rt->ray.phit,((t_light *)tmp->content)->pos)), \
							normal), rt->ray.dir)), obj->mat.spec_exp) * ((t_light *)tmp->content)->intens;
		tmp = tmp->next;
	}
	return (col_add(col_mul(obj->mat.color,diff_int * obj->mat.albedo[0]), \
				col_mul((t_color){1, 1, 1}, spec_int * obj->mat.albedo[1])));
}

void	init_light(t_minirt *minirt)
{
	t_light	*light;
	t_light	*light2;

	light = malloc(sizeof(t_light));
	light2 = malloc(sizeof(t_light));
	light->pos = (t_vec){0, 1, 2};
	light->pos = (t_vec){10, 0, 10};
	light->intens = 1.0;
	light2->intens = 0.5;
	ft_lstadd_back(&(minirt->light_lst), ft_lstnew((void *)light));
	ft_lstadd_back(&(minirt->light_lst), ft_lstnew((void *)light2));
}
