#include <wayland-client.h>

#include "../include/wlbasic.h"

static void wl_pointer_enter(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t serial,
	struct wl_surface *surface,
	wl_fixed_t surface_x, wl_fixed_t surface_y
) {}

static void wl_pointer_leave(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t serial,
	struct wl_surface *surface
) {}

static void wl_pointer_motion(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t time,
	wl_fixed_t surface_x,
	wl_fixed_t surface_y
) {}

static void wl_pointer_button(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t serial,
	uint32_t time,
	uint32_t button,
	uint32_t state
) {}

static void wl_pointer_frame(void *data, struct wl_pointer *wl_pointer) {}

static void wl_pointer_axis(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t time,
	uint32_t axis,
	wl_fixed_t value
) {}

static void wl_pointer_axis_source(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t axis_source
) {}

static void wl_pointer_axis_stop(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t time,
	uint32_t axis
) {}

static void wl_pointer_axis_discrete(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t axis,
	int32_t discrete
) {}

void wlbasic_pointer_default(struct wl_pointer_listener *listener) {
	*listener = (struct wl_pointer_listener) {
		.enter = wl_pointer_enter,
		.leave = wl_pointer_leave,
		.motion = wl_pointer_motion,
		.button = wl_pointer_button,
		.axis = wl_pointer_axis,
		.frame = wl_pointer_frame,
		.axis_source = wl_pointer_axis_source,
		.axis_stop = wl_pointer_axis_stop,
		.axis_discrete = wl_pointer_axis_discrete,
	};
}
