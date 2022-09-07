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
	obj->params = init_sphere(minirt, (t_vec){0, 0, -0.2}, 0.2);
	obj2->params = init_sphere(minirt, (t_vec){0.5, 0, -0.3}, 0.1);//red
	obj3->params = init_sphere(minirt, (t_vec){0, 1, -0.1}, 0.4);
	obj4->params = init_sphere(minirt, (t_vec){-1, -1, -0.2}, 0.5);
	obj->intersect = inter_sphere;
	obj2->intersect = inter_sphere;
	obj3->intersect = inter_sphere;
	obj4->intersect = inter_sphere;
	obj->mat = (t_material){get_color(101, 0, 101),{0.6, 0.3},50.0};
	obj2->mat = (t_material){get_color(85, 205, 140),{0.6, 0.3},50.0};
	obj3->mat = (t_material){get_color(30, 100, 10),{0.9, 0.1},10.0};
	obj4->mat = (t_material){get_color(85, 85, 85),{0.9, 0.1},10.0};
	ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj));
	ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj2));
	ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj3));
	ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj4));
}
