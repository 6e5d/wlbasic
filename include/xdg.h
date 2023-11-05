#include <wayland-client.h>

void handle_toplevel_configure(
	void* data,
	struct xdg_toplevel* toplevel,
	int32_t width,
	int32_t height,
	struct wl_array* states
);

void handle_toplevel_close(void* data, struct xdg_toplevel* toplevel);
