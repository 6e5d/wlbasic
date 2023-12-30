#include <wayland-client.h>

#include "../include/wlbasic.h"

static void wlbasic(surface_enter)(void*,
	struct wl_surface*, struct wl_output*) {}
static void wlbasic(surface_leave)(void*,
	struct wl_surface*, struct wl_output*) {}
static void preferred_buffer_scale(void*, struct wl_surface*, int32_t) {}
static void preferred_buffer_transform(void*, struct wl_surface*, uint32_t) {}

void wlbasic(surface_default)(struct wl_surface_listener *listener) {
	*listener = (struct wl_surface_listener) {
		.enter = wlbasic(surface_enter),
		.leave = wlbasic(surface_leave),
		.preferred_buffer_scale = preferred_buffer_scale,
		.preferred_buffer_transform = preferred_buffer_transform,
	};
}
