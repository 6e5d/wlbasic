#ifndef _WLBASIC_WLBASICH
#define _WLBASIC_WLBASICH

#include <wayland-client.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
	struct wl_display* display;
	struct wl_registry* registry;
	struct wl_compositor* compositor;
	struct wl_surface* surface;
	struct wl_seat* seat;
	struct wl_pointer *pointer;
	struct xdg_wm_base* shell;
	struct xdg_surface* shell_surface;
	struct xdg_toplevel* toplevel;
	bool quit;
	bool resize;
	uint32_t width;
	uint32_t height;
} Wlbasic;

void wlbasic_init(Wlbasic* wl);
void wlbasic_deinit(Wlbasic* wl);

#endif
