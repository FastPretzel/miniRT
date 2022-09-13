#include "minirt.h"

static void	*init_sphere(t_vec orig, double r)
{
	t_sphere	*sp;

	sp = malloc(sizeof(t_sphere));
	sp->orig = orig;
	sp->r = r;
	return ((void *)sp);
}

static void	*init_plane(t_vec orig, t_vec normal)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	pl->orig = orig;
	pl->normal = normal;
	return ((void *)pl);
}

void	init_objs(t_minirt *minirt)
{
	//spheres
	t_object	*obj;
	/*t_object	*obj2;*/
	/*t_object	*obj3;*/
	/*t_object	*obj4;*/
	//planes
	t_object	*obj5;
	t_object	*obj6;
	t_object	*obj7;
	t_object	*obj8;

	obj = malloc(sizeof(t_object));
	/*obj2 = malloc(sizeof(t_object));*/
	/*obj3 = malloc(sizeof(t_object));*/
	/*obj4 = malloc(sizeof(t_object));*/
	obj5 = malloc(sizeof(t_object));
	obj6 = malloc(sizeof(t_object));
	obj7 = malloc(sizeof(t_object));
	obj8 = malloc(sizeof(t_object));

	obj->params = init_sphere((t_vec){0, 0, -2}, 2);
	/*obj2->params = init_sphere((t_vec){0.5, 0, -3}, 0.1);//red*/
	/*obj3->params = init_sphere((t_vec){0, 0.5, -1}, 0.2);*/
	/*obj4->params = init_sphere((t_vec){-0.2, -0.2, -3}, 0.5);*/

	obj5->params = init_plane((t_vec){2, 0, 0}, (t_vec){1,0,0});
	obj6->params = init_plane((t_vec){0, -2, 0}, (t_vec){0,-1,0});
	obj7->params = init_plane((t_vec){-3, 0, 0}, (t_vec){-1,0,0});
	obj8->params = init_plane((t_vec){0, 0, -4}, (t_vec){0,0,-1});
	
	obj->intersect = inter_sphere;
	/*obj2->intersect = inter_sphere;*/
	/*obj3->intersect = inter_sphere;*/
	/*obj4->intersect = inter_sphere;*/

	obj5->intersect = inter_plane;
	obj6->intersect = inter_plane;
	obj7->intersect = inter_plane;
	obj8->intersect = inter_plane;

	obj->get_normal = get_norm_sphere;
	/*obj2->get_normal = get_norm_sphere;*/
	/*obj3->get_normal = get_norm_sphere;*/
	/*obj4->get_normal = get_norm_sphere;*/

	obj5->get_normal = get_norm_plane;
	obj6->get_normal = get_norm_plane;
	obj7->get_normal = get_norm_plane;
	obj8->get_normal = get_norm_plane;

	obj->mat = (t_material){get_color(101, 0, 101),{0.6, 0.4},50.0};//purple sp
	/*obj2->mat = (t_material){get_color(85, 205, 140),{0.6, 0.0},50.0};*/
	/*obj3->mat = (t_material){get_color(30, 100, 10),{0.9, 0.3},10.0};//green sp*/
	/*obj4->mat = (t_material){get_color(85, 85, 85),{0.9, 0.1},10.0};//grey sp*/
	
	obj5->mat = (t_material){get_color(255, 0, 0),{0.9, 0.1},20.0};//red plane
	obj6->mat = (t_material){get_color(100, 0, 200),{0.9, 0.1},20.0};//purple plane
	obj7->mat = (t_material){get_color(0, 150, 200),{0.9, 0.1},20.0};
	obj8->mat = (t_material){get_color(50, 150, 20),{0.9, 0.1},20.0};

	/*ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj));*/
	/*ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj2));*/
	/*ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj3));*/
	/*ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj4));*/
	ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj5));
	/*ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj6));*/
	/*ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj7));*/
	/*ft_lstadd_back(&(minirt->obj_lst), ft_lstnew((void *)obj8));*/
}
