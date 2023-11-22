#include <stdio.h>
#include <wayland-client.h>

#include "../include/surface.h"

void wlbasic_surface_enter(void *data,
	struct wl_surface *wl_surface,
	struct wl_output *output) {}
void wlbasic_surface_leave(void *data,
	struct wl_surface *wl_surface,
	struct wl_output *output) {}
void preferred_buffer_scale(void *data,
	struct wl_surface *wl_surface,
	int32_t factor) {
}
void preferred_buffer_transform(void *data,
	struct wl_surface *wl_surface,
	uint32_t transform) {}
