#include <wayland-client.h>

#include "../include/wlbasic.h"
#include "../include/xdg.h"

void handle_toplevel_configure(
	void* data,
	struct xdg_toplevel* toplevel,
	int32_t width,
	int32_t height,
	struct wl_array* states
) {
	Wlbasic *wl = data;
	wl_surface_set_buffer_scale(wl->surface, 1);
}

void handle_toplevel_close(void* data, struct xdg_toplevel* toplevel) {}

void wlbasic_topdeco_configure(void *data,
	struct zxdg_toplevel_decoration_v1 *zxdg_toplevel_decoration_v1,
	uint32_t mode) {}

