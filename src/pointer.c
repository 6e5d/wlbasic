#include <wayland-client.h>

#include "../include/wlbasic.h"

static void wl_pointer_enter(void*, struct wl_pointer*,
	uint32_t, struct wl_surface*, wl_fixed_t, wl_fixed_t) {}
static void wl_pointer_leave(void*, struct wl_pointer*,
	uint32_t, struct wl_surface*) {}
static void wl_pointer_motion(void*, struct wl_pointer*,
	uint32_t, wl_fixed_t, wl_fixed_t) {}
static void wl_pointer_button(void*, struct wl_pointer *,
	uint32_t, uint32_t, uint32_t, uint32_t) {}

static void wl_pointer_frame(void*, struct wl_pointer*) {}

static void wl_pointer_axis( void*, struct wl_pointer*,
	uint32_t, uint32_t,
	wl_fixed_t) {}

static void wl_pointer_axis_source(void*, struct wl_pointer*, uint32_t) {}

static void wl_pointer_axis_stop(void*, struct wl_pointer*,
	uint32_t, uint32_t) {}

static void wl_pointer_axis_discrete(void*, struct wl_pointer*,
	uint32_t, int32_t) {}

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
