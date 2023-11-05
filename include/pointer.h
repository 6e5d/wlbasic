#include <wayland-client.h>

void wl_pointer_enter(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t serial,
	struct wl_surface *surface,
	wl_fixed_t surface_x, wl_fixed_t surface_y
);

void wl_pointer_leave(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t serial,
	struct wl_surface *surface
);

void wl_pointer_motion(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t time,
	wl_fixed_t surface_x,
	wl_fixed_t surface_y
);

void wl_pointer_button(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t serial,
	uint32_t time,
	uint32_t button,
	uint32_t state
);

void wl_pointer_frame(
	void *data,
	struct wl_pointer *wl_pointer
);

void wl_pointer_axis(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t time,
	uint32_t axis,
	wl_fixed_t value
);

void wl_pointer_axis_source(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t axis_source
);

void wl_pointer_axis_stop(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t time,
	uint32_t axis
);

void wl_pointer_axis_discrete(
	void *data,
	struct wl_pointer *wl_pointer,
	uint32_t axis,
	int32_t discrete
);
