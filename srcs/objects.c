#include "minirt.h"

static void	*init_sphere(t_minirt *minirt, t_vec orig, double r)
{
	t_sphere	*sp;

	(void)minirt;
	sp = malloc(sizeof(t_sphere));
	sp->orig = orig;
	sp->r = r;
	return ((void *)sp);
}

void	init_objs(t_minirt *minirt)
{
	t_object	*obj;
	t_object	*obj2;
	t_object	*obj3;
	t_object	*obj4;

	obj = malloc(sizeof(t_object));
	obj2 = malloc(sizeof(t_object));
	obj3 = malloc(sizeof(t_object));
	obj4 = malloc(sizeof(t_object));
	obj->params = init_sphere(minirt, (t_vec){0, 0, 0}, 0.2);
	obj2->params = init_sphere(minirt, (t_vec){1, 0, 0}, 0.1);
	obj3->params = init_sphere(minirt, (t_vec){0, 1, -3}, 0.4);
	obj4->params = init_sphere(minirt, (t_vec){-1, 0, 1}, 0.5);
	obj->intersect = inter_sphere;
	obj2->intersect = inter_sphere;
	obj3->intersect = inter_sphere;
	obj4->intersect = inter_sphere;
	obj->color = 0xFF0000;
	obj2->color = 0xFF00;
	obj3->color = 0xFF;
	obj4->color = 0xFF0000;
	ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj));
	ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj2));
	ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj3));
	ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj4));
}
