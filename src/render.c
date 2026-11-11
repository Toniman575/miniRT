/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:22:14 by asadik            #+#    #+#             */
/*   Updated: 2026/11/11 16:09:41 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "vector.h"

t_option	cast_ray(t_state *state, t_ray ray)
{
	t_option	is;
	t_option	c_is;
	uint16_t	i;
	uint16_t	max_objects;
	t_object	*objects;

	objects = (t_object *)(state->objects.buf);
	max_objects = get_idx_from_offset(&state->objects, state->objects.offset);
	is.type = OT_NONE;
	c_is.type = OT_NONE;
	i = 0;
	while (++i < max_objects)
	{
		c_is = xchecker(&objects[i], &ray);
		if (is.type == OT_NONE && c_is.type != OT_NONE)
			is = c_is;
		else if (c_is.type != OT_NONE && is.type != OT_NONE
			&& c_is.value.intersection.t < is.value.intersection.t)
			is = c_is;
	}
	return (is);
}

/// TODO: Optimize: Move rotation to be pre computed in
///					the camerastruct and not at each ray.
t_ray	viewport_ray(t_state *state, t_screen_coord coord)
{
	t_ray		ray;
	double		distance;
	double		half_width;
	double		half_height;
	double		fov_rad;

	fov_rad = state->camera.fov * M_PI / 180.;
	half_width = state->win.dim.width / 2.;
	half_height = state->win.dim.height / 2.;
	distance = half_width / (tan(fov_rad / 2.));
	ray.origin = state->camera.pos;
	ray.dir = vec3_rot(state->camera.rotation,
			vec3_normalize(new_vec3(coord.x - half_width,
					half_height - coord.y, -distance)));
	return (ray);
}

void	put_pixel_to_buffer(t_state *state, t_screen_coord sc, uint32_t color)
{
	size_t	idx;
	size_t	pixels_per_line;

	pixels_per_line = state->img.bytes_per_line * 8
		/ state->img.bits_per_pixel;
	idx = sc.y * pixels_per_line + sc.x;
	((unsigned int *)state->img.buf)[idx] = color;
}

void	face_camera(t_state *state, t_option ray)
{
	t_object	*object;

	if (ray.type == OT_NONE)
		return ;
	object = ray.value.intersection.object;
	if (object->faces_camera)
		return ;
	object->faces_camera = true;
	if (object->type == OBJ_PLANE)
	{
		if (vec3_dot(object->data.plane.dir, vec3_sub(state->camera.pos, object->data.plane.pos)) < -EPSILON)
			object->data.plane.dir = vec3_mult(object->data.plane.dir, -1);
	}
	else if (object->type == OBJ_SPHERE)
	{
		if (vec3_len_pow2(
				vec3_sub(state->camera.pos, object->data.sphere.center))
			< object->data.sphere.radius * object->data.sphere.radius)
			object->data.sphere.cam_pos = CAM_IN;
		else
			object->data.sphere.cam_pos = CAM_OUT;
	}
	else if (object->type == OBJ_CYLINDER)
		;
}

void	render(t_state *state)
{
	t_screen_coord	current;
	t_xcolor		color;
	t_option		ray;
	size_t			i;
	t_object		*objects;

	objects = (t_object *)(state->objects.buf);
	current.y = -1;
	while (++current.y < state->win.dim.height)
	{
		current.x = -1;
		while (++current.x < state->win.dim.width)
		{
			ray = cast_ray(state, viewport_ray(state, current));
			face_camera(state, ray);
			color = get_color_from_ray(state, ray);
			put_pixel_to_buffer(state, current,
				mlx_get_color_value(state->mlx_ptr, color));
		}
	}
	mlx_put_image_to_window(state->mlx_ptr, state->win.ptr,
		state->img.ptr, 0, 0);
	i = get_idx_from_offset(&state->objects, state->objects.offset);
	while (--i > 0)
		objects[i].faces_camera = false;
}
