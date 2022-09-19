#include "minirt.h"

static int	check_height(t_cylinder *cy, t_vec p)
{
	t_ray	cray;
	t_plane	cap;

	cray.orig = cy->orig;
	cray.dir = cy->dir;
	cray.t = INFINITY;
	cap.orig = p;
	cap.normal = vec_neg(cy->dir);
	inter_plane((void *)(&cap), &cray);
	if (cray.t <= cy->h / 2)
		return (1);
	cray.dir = vec_neg(cy->dir);
	cray.t = INFINITY;
	cap.normal = cy->dir;
	inter_plane((void *)(&cap), &cray);
	if (cray.t <= cy->h / 2)
		return (1);
	return (0);
}

static int	intersect_caps(t_cylinder *cy, t_ray *ray)
{
	t_plane	cap;
	t_ray	cray;

	cray.orig = ray->orig;
	cray.dir = ray->dir;
	cray.t = INFINITY;
	cap.orig = vec_add(cy->orig, vec_mul(cy->dir, cy->h / 2));
	cap.normal = cy->dir;
	if (inter_plane((void *)(&cap), &cray) && 
		vec_len(vec_sub(vec_add(cray.orig, 
		vec_mul(cray.dir, cray.t)), cap.orig)) <= cy->d / 2)
	{
		ray->t = cray.t;
		return (1);
	}
	cap.orig = vec_sub(cy->orig, vec_mul(cy->dir, cy->h / 2));
	cap.normal = vec_neg(cy->dir);
	if (inter_plane((void *)(&cap), &cray) && vec_len(
			vec_sub(vec_add(cray.orig, vec_mul(cray.dir, cray.t)), cap.orig))
			<= cy->d / 2)
	{
		ray->t = cray.t;
		return (1);
	}
	return (0);
}

t_vec	get_norm_cylinder(t_ray *ray, void *ptr)
{
	t_vec		po;
	t_plane		cap;
	t_ray		cray;
	t_cylinder	*cy = (t_cylinder *)ptr;

	cray.orig = cy->orig;
	cray.dir = cy->dir;
	cray.t = INFINITY;
	cap.orig = ray->phit;
	cap.normal = vec_neg(cy->dir);
	if (inter_plane(((void *)&cap), &cray) && fabs(cray.t - cy->h / 2) < 1e-5)
		return (cy->dir);
	cray.dir = vec_neg(cy->dir);
	cray.t = INFINITY;
	cap.normal = cy->dir;
	if (inter_plane(((void *)&cap), &cray) && fabs(cray.t - cy->h / 2) < 1e-5)
		return (vec_neg(cy->dir));
	po = vec_sub(ray->phit, cy->orig);
	return (vec_norm(vec_sub(po, vec_mul(cy->dir, vec_dot(cy->dir, po)))));
}

int	inter_cylinder(void *ptr, t_ray *ray)
{
	t_cylinder	*cyl = (t_cylinder *)ptr;
	t_vec		cx;
	t_vec		cy;
	double		t;
	double		a;
	double		b;
	double		c;
	double		x1;
	double		x2;
	double		det;

	if (intersect_caps(cyl, ray))
		return (1);
	cx = vec_cross(ray->dir, cyl->dir);
	cy = vec_cross(cyl->dir, vec_sub(cyl->orig, ray->orig));
	a = vec_dot(cx, cx);
	b = 2 * vec_dot(cx, cy);
	c = vec_dot(cy, cy) - (pow(cyl->d / 2, 2) * vec_dot(cyl->dir, cyl->dir));
	if ((det = pow(b, 2) - 4 * a * c) < 0)
		return (0);
	det = sqrt(det);
	x1 = (-b + det) / (2 * a);
	x2 = (-b - det) / (2 * a);
	if (x1 < 0 && x2 < 0)
		return (0);
	t = fmin(x1, x2);
	if (check_height(cyl, vec_add(ray->orig, vec_mul(ray->dir, t))) && (ray->t = t))
		return (1);
	return (0);
}
/*int	inter_cylinder(void *ptr, t_ray *ray)*/
/*{*/
	/*double	a;*/
	/*double	b;*/
	/*double	c;*/
	/*double	delta;*/
	/*double	t1;*/
	/*double	t2;*/
	/*[>[>double	t;<]<]*/
	/*[>[>double	r;<]<]*/
	/*t_vec	c_2_o;*/
	/*[>[>t_ray	new_ray;<]<]*/
	/*t_cylinder	*cy = (t_cylinder *)ptr;*/

	/*[>[>new_ray.orig = ray->orig;<]<]*/
	/*[>[>new_ray.dir = vec_cross(ray->dir, cy->dir);<]<]*/
	/*c_2_o = vec_sub(ray->orig, cy->orig);*/
	/*[>[>a = vec_dot(ray->dir, ray->dir);<]<]*/
	/*a = ray->dir.x * ray->dir.x + ray->dir.z*ray->dir.z;*/
	/*b = 2 *vec_dot(ray->dir, vec_cross(c_2_o, cy->dir));*/
	/*c = vec_dot(vec_cross(c_2_o, cy->dir), vec_cross(c_2_o, cy->dir)) - pow(cy->d/2, 2);*/
	/*delta = b*b - 4*c*a;*/
	/*if (delta < 0)*/
		/*return (0);*/
	/*t1 = (-b - sqrt(delta))/(2*a);*/
	/*t2 = (-b + sqrt(delta))/(2*a);*/
	/*if (t2 < 0 && t1 < 0)*/
		/*return (0);*/
	/*if (t2 > t1)*/
		/*ray->t = t1;*/
	/*else*/
		/*ray->t = t2;*/
	/*return (1);*/
/*}*/

/*int	inter_cylinder(void *ptr, t_ray *ray)*/
/*{*/
	/*t_cylinder	*cy = (t_cylinder *)ptr;*/
	/*double	a;*/
	/*double	b;*/
	/*double	c;*/
	/*double	discr;*/
	/*double	t1;*/
	/*double	t2;*/
	/*double	t;*/

	/*a = ray->dir.x*ray->dir.x + ray->dir.z*ray->dir.z;*/
	/*b = 2*(ray->orig.x*ray->orig.x + ray->orig.z*ray->orig.z);*/
	/*c = ray->orig.x*ray->orig.x + ray->orig.z*ray->orig.z - pow(cy->d/2,2);*/
	/*discr = b*b - 4*a*c;*/
	/*if (discr < 0)*/
		/*return (0);*/
	/*t1 = (-b+sqrt(discr))/(2*a);*/
	/*t2 = (-b-sqrt(discr))/(2*a);*/
	/*if (t1 > t2)*/
		/*t = t2;*/
	/*if (t < 0)*/
		/*t = t1;*/
	/*if (t < 0)*/
		/*return (0);*/
	/*ray->phit = vec_add(ray->orig, vec_mul(ray->dir, t));*/
	/*cy->normal = (t_vec){2*ray->phit.x, 0.f, 2*ray->phit.z};*/
	/*if (ray->phit.y <0 || ray->phit.y > cy->h)*/
		/*return (0);*/
	/*if (ray->dir.y != 0.f)*/
	/*{*/
		/*double x3 = (0 - ray->orig.y)/ray->dir.y;*/
		/*double x4 = (cy->h - ray->orig.y)/ray->dir.y;*/
		/*double x2 = fmin(x3, x4);*/
		/*if (x2 < 0)*/
			/*x2 = fmax(x3,x4);*/
		/*if (x2 >= 0)*/
		/*{*/
			/*t_vec p1 = vec_add(ray->orig, vec_mul(ray->dir, x2));*/
			/*if (p1.x*p1.x + p1.z*p1.z <= pow(cy->d/2, 2)+0.9)*/
			/*{*/
				/*t = fmin(t, x2);*/
				/*if (t == x3)*/
				/*{*/
					/*cy->normal = (t_vec){0, -1, 0};*/
					/*ray->phit = p1;*/
					/*return (1);*/
				/*}*/
				/*else if (t == x4)*/
				/*{*/
					/*cy->normal = (t_vec){0, 1, 0};*/
					/*ray->phit = p1;*/
					/*return (1);*/
				/*}*/
			/*}*/
		/*}*/
	/*}*/
	/*ray->phit = vec_add(ray->orig, vec_mul(ray->dir, t));*/
	/*return (1);*/
/*}*/
