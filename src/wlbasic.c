#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wayland-client.h>
#include "../include/xdg-shell-client-header.h"

#include "../include/wlbasic.h"
#include "../include/registry.h"
#include "../include/xdg.h"

static const struct wl_registry_listener listener = {
	.global = handle_registry
};

static void shell_surface_configure(
	void* data, struct xdg_surface* surface, uint32_t serial
) {
	Wlbasic* wlbasic = data;
	xdg_surface_ack_configure(surface, serial);
	wlbasic->resize = true;
}

static const struct xdg_surface_listener shell_surface_listener = {
	.configure = shell_surface_configure
};

static const struct xdg_toplevel_listener toplevel_listener = {
	.configure = handle_toplevel_configure,
	.close = handle_toplevel_close
};

void wlbasic_init(Wlbasic* wl) {
	assert((wl->display = wl_display_connect(NULL)));
	assert((wl->registry = wl_display_get_registry(wl->display)));
	wl_registry_add_listener(wl->registry, &listener, wl);
	wl_display_roundtrip(wl->display);
	assert((wl->surface = wl_compositor_create_surface(wl->compositor)));
	assert((wl->shell_surface =
		xdg_wm_base_get_xdg_surface(wl->shell, wl->surface)));
	xdg_surface_add_listener(
		wl->shell_surface, &shell_surface_listener, wl);
	assert((wl->toplevel = xdg_surface_get_toplevel(wl->shell_surface)));
	xdg_toplevel_add_listener(wl->toplevel, &toplevel_listener, wl);
	xdg_toplevel_set_title(wl->toplevel, "wlbasic");
	xdg_toplevel_set_app_id(wl->toplevel, "wlbasic");
	wl_surface_commit(wl->surface);
	wl_display_roundtrip(wl->display);
	wl_surface_commit(wl->surface);
	wl->width = 900;
	wl->height = 600;
}

void wlbasic_deinit(Wlbasic* wlbasic) {
	wl_pointer_destroy(wlbasic->pointer);
	xdg_toplevel_destroy(wlbasic->toplevel);
	xdg_surface_destroy(wlbasic->shell_surface);
	wl_surface_destroy(wlbasic->surface);
	xdg_wm_base_destroy(wlbasic->shell);
	wl_compositor_destroy(wlbasic->compositor);
	wl_seat_destroy(wlbasic->seat);
	wl_registry_destroy(wlbasic->registry);
	wl_display_disconnect(wlbasic->display);
}
