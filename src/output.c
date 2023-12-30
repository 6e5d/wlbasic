#include <wayland-client.h>

#include "../include/wlbasic.h"

static void wlbasic(output_geometry)(void*, struct wl_output*,
	int32_t, int32_t, int32_t, int32_t, int32_t,
	const char*, const char*, int32_t) {}
static void wlbasic(output_mode)(void*, struct wl_output*,
	uint32_t, int32_t, int32_t, int32_t) {}
static void wlbasic(output_done)(void*, struct wl_output*) {}
static void wlbasic(output_scale)(void *data, struct wl_output*, int32_t factor)
{
	Wlbasic() *wl = data;
	wl->scale = factor;
}
static void wlbasic(output_name)(void*, struct wl_output*, const char*) {}
static void wlbasic(output_description)(void*,
	struct wl_output*, const char *) {}

void wlbasic(output_default)(struct wl_output_listener *listener) {
	*listener = (struct wl_output_listener) {
		.geometry = wlbasic(output_geometry),
		.mode = wlbasic(output_mode),
		.done = wlbasic(output_done),
		.scale = wlbasic(output_scale),
		.name = wlbasic(output_name),
		.description = wlbasic(output_description),
	};
}
