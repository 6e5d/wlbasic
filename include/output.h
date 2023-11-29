#ifndef INCLUDEGUARD_WLBASIC_OUTPUTH
#define INCLUDEGUARD_WLBASIC_OUTPUTH

#include <stdint.h>
#include <wayland-client.h>

void wlbasic_output_geometry(void *data, struct wl_output *wl_output,
	int32_t x, int32_t y,
	int32_t physical_width, int32_t physical_height,
	int32_t subpixel,
	const char *make,
	const char *model,
	int32_t transform);
void wlbasic_output_mode(void *data,
	struct wl_output *wl_output,
	uint32_t flags,
	int32_t width,
	int32_t height,
	int32_t refresh);
void wlbasic_output_done(void *data, struct wl_output *wl_output);
void wlbasic_output_scale(void *data, struct wl_output *wl_output, int32_t factor);
void wlbasic_output_name(void *data, struct wl_output *wl_output, const char *name);
void wlbasic_output_description(void *data, struct wl_output *wl_output, const char *description);

#endif
