#include "minirt.h"

t_color	calc_light(t_object *obj, t_minirt *rt)
{
	double	diff_int;
	t_list	*tmp;
	t_vec	normal;

	normal = vec_norm(vec_sub(rt->ray.phit, ((t_sphere *)obj->params)->orig));
	tmp = rt->light_lst;
	diff_int = 0;
	while (tmp)
	{
		diff_int += ((t_light *)tmp->content)->intens * fmax(0.f, vec_dot(normal, vec_norm(vec_sub(rt->ray.phit,((t_light *)tmp->content)->pos))));
		tmp = tmp->next;
	}
	return (col_mul(obj->color,diff_int));
}

void	init_light(t_minirt *minirt)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	light->pos = (t_vec){0, 1, 2};
	light->intens = 1.0;
	ft_lstadd_back(&(minirt->light_lst), ft_lstnew((void *)light));
}
