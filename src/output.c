#include <wayland-client.h>

#include "../include/wlbasic.h"

static void wlbasic_output_geometry(void *data, struct wl_output *wl_output,
	int32_t x, int32_t y,
	int32_t physical_width, int32_t physical_height,
	int32_t subpixel,
	const char *make,
	const char *model,
	int32_t transform) {}
static void wlbasic_output_mode(void *data,
	struct wl_output *wl_output,
	uint32_t flags,
	int32_t width,
	int32_t height,
	int32_t refresh) {}
static void wlbasic_output_done(void *data, struct wl_output *wl_output) {}
static void wlbasic_output_scale(void *data, struct wl_output *wl_output, int32_t factor) {
	Wlbasic *wl = data;
	wl->scale = factor;
}
static void wlbasic_output_name(void *data, struct wl_output *wl_output, const char *name) {}
static void wlbasic_output_description(void *data, struct wl_output *wl_output, const char *description) {}

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
