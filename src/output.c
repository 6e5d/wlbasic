#include <wayland-client.h>

#include "../include/wlbasic.h"

static void wlbasic_output_geometry(void*, struct wl_output*,
	int32_t, int32_t, int32_t, int32_t, int32_t,
	const char*, const char*, int32_t) {}
static void wlbasic_output_mode(void*, struct wl_output*,
	uint32_t, int32_t, int32_t, int32_t) {}
static void wlbasic_output_done(void*, struct wl_output*) {}
static void wlbasic_output_scale(void *data, struct wl_output*, int32_t factor)
{
	Wlbasic *wl = data;
	wl->scale = factor;
}
static void wlbasic_output_name(void*, struct wl_output*, const char*) {}
static void wlbasic_output_description(void*,
	struct wl_output*, const char *) {}

void wlbasic_output_default(struct wl_output_listener *listener) {
	*listener = (struct wl_output_listener) {
		.geometry = wlbasic_output_geometry,
		.mode = wlbasic_output_mode,
		.done = wlbasic_output_done,
		.scale = wlbasic_output_scale,
		.name = wlbasic_output_name,
		.description = wlbasic_output_description,
	};
}
