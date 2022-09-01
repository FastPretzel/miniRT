#include "minirt.h"

static void	*init_sphere(t_minirt *minirt)
{
	t_sphere	*sp;

	(void)minirt;
	sp = malloc(sizeof(t_sphere));
	sp->orig = (t_vec){0, 0, 0};
	sp->r = 0.2;
	return ((void *)sp);
}

void	init_objs(t_minirt *minirt)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	obj->params = init_sphere(minirt);
	obj->intersect = inter_sphere;
	obj->color = 0xFF0000;
	ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj));
}
