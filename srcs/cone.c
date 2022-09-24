#include "minirt.h"

t_vec	get_norm_cone(t_ray *ray, void *ptr)
{
	t_vec	normal;
	t_cone	*cone = (t_cone *)ptr;

	normal = vec_cross(vec_cross(cone->dir, vec_sub(ray->phit, cone->orig)), vec_sub(ray->phit, cone->orig));
	normal = vec_norm(normal);
	return (normal);
	//проекция вектора на ось это скалярное произведение вектора на един вектор
}

int	reject_sh_cone(t_cone *cone, t_ray *ray, double t)
{
	t_vec	p;

	p = vec_add(ray->orig, vec_mul(ray->dir, t));
	if (vec_dot(vec_sub(p, cone->orig), cone->dir) > 0)
		return (ray->t = t);
	return (0);
}
int	inter_cone(void *ptr, t_ray *ray)
{
	t_cone	*cone = (t_cone *)ptr;
	t_vec	w;
	t_vec	v;
	t_vec	h;
	double	m;
	double	a;
	double	b;
	double	c;
	double	dis;
	double	t1;
	double	t2;
	double	t;
	double	alpha;

	v = ray->dir;
	h = cone->dir;
	w = vec_sub(ray->orig, cone->orig);
	m = pow(cone->d/2, 2)/pow(vec_len(h),2);
	a = vec_dot(v,v) - m*pow(vec_dot(v,h),2) - pow(vec_dot(v,h),2);
	b = 2*(vec_dot(v,w) - m*vec_dot(v,h)*vec_dot(w,h) - vec_dot(v,h)*vec_dot(w,h));
	c = vec_dot(w,w) - m*pow(vec_dot(w,h),2) - pow(vec_dot(w,h),2);
	dis = b*b - 4*a*c;
	if (dis > 0)
	{
		t1 = (-b - sqrt(dis)) / (2*a);
		t2 = (-b + sqrt(dis)) / (2*a);
		if (t1 < 0 && t2 < 0)
			return (0);
		t = t1;
		if (t < 0)
			t = t2;
		/*return (ray->t = t);*/
		return (reject_sh_cone(cone, ray, t));
	}
	else if (dis == 0)
	{
		alpha = cone->h / (sqrt(pow(cone->h,2)+pow(cone->d/2,2)));
		if (fabs(vec_dot(v,h)) != alpha)
		{
			t = -b/(2*a);
			/*return (ray->t = t);*/
			return (reject_sh_cone(cone, ray, t));
		}
		else
			return (0);
	}
	return (0);
}
/*int	inter_cone(void *ptr, t_ray *ray)*/
/*{*/
	/*t_cone	*cone = (t_cone *)ptr;*/
	/*double	rad;*/
	/*double	a;*/
	/*double	b;*/
	/*double	c;*/
	/*t_vec	co;*/
	/*double	discr;*/
	/*double	t1;*/
	/*double	t2;*/
	/*double	t;*/
	
	/*[>rad = atan((cone->d/2.0)/ cone->h);<]*/
	/*rad = deg2rad(30.0);*/
	/*co = vec_sub(cone->orig, ray->orig);*/
	/*a = pow(vec_dot(ray->dir, cone->dir), 2) - pow(cos(rad), 2);*/
	/*b = 2*(vec_dot(ray->dir, cone->dir)*vec_dot(co, cone->dir) -*/
			/*vec_dot(ray->dir, co)*pow(cos(rad), 2));*/
	/*c = pow(vec_dot(co, cone->dir), 2) - vec_dot(co,co)*pow(cos(rad), 2);*/
	/*discr = pow(b, 2) - 4*a*c;*/
	/*if (discr < 0)*/
		/*return (0);*/
	/*if (discr == 0)*/
	/*{*/
		/*t = -b/(2*a);*/
		/*if (t > 0 && t < ray->t)*/
		/*{*/
			/*t_vec p = vec_add(ray->orig, vec_mul(ray->dir, t));*/
			/*if (vec_dot(vec_sub(p, cone->orig), cone->dir) > 0)*/
				/*return (t = ray->t);*/
		/*}*/
	/*}*/
	/*else*/
	/*{*/
		/*t1 = (-b - sqrt(discr))/(2*a);*/
		/*t2 = (-b + sqrt(discr))/(2*a);*/
		/*t = fmin(t1, t2);*/
		/*if (t < 0)*/
			/*t = t2;*/
		/*if (t > 0 && t < ray->t)*/
		/*{*/
			/*t_vec p = vec_add(ray->orig, vec_mul(ray->dir, t));*/
			/*if (vec_dot(vec_sub(p, cone->orig), cone->dir) > 0)*/
				/*return (t = ray->t);*/
		/*}*/
	/*}*/
	/*return (0);*/
/*}*/
