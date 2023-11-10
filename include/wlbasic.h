#ifndef _WLBASIC_WLBASICH
#define _WLBASIC_WLBASICH

#include <wayland-client.h>
#include <stdint.h>
#include <stdbool.h>

#include "../include/xdg-shell-client-header.h"

typedef struct {
	struct wl_registry_listener listener;
	struct xdg_surface_listener shell_surface_listener;
	struct xdg_toplevel_listener toplevel_listener;
	struct xdg_wm_base_listener shell_listener;
	struct wl_seat_listener wl_seat_listener;
	struct wl_pointer_listener wl_pointer_listener;
} WlbasicConfig;

typedef struct {
	WlbasicConfig conf;
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
	void* next; // user data
} Wlbasic;

void wlbasic_config_default(WlbasicConfig* conf);
void wlbasic_init(Wlbasic* wl);
void wlbasic_deinit(Wlbasic* wl);

#endif
