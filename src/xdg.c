#include <stdio.h>
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
	Wlbasic* wlbasic = data;
	if (width != 0 && height != 0) {
		wlbasic->resize = 1;
		wlbasic->width = (uint32_t)width;
		wlbasic->height = (uint32_t)height;
	}
}

void handle_toplevel_close(void* data, struct xdg_toplevel* toplevel) {
	Wlbasic* wlbasic = data;
	printf("quit requested\n");
	wlbasic->quit = true;
}
