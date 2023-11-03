#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wayland-client.h>
#include "../include/xdg-shell-client-header.h"

#include "../include/wlbasic.h"

static void chk(bool x) {
	assert(x);
}

static void handle_shell_ping(
	void* data,
	struct xdg_wm_base* shell,
	uint32_t serial
) {
	xdg_wm_base_pong(shell, serial);
}

static const struct xdg_wm_base_listener shell_listener = {
	.ping = handle_shell_ping
};

static void handle_registry(
	void* data,
	struct wl_registry* registry,
	uint32_t name,
	const char* interface,
	uint32_t version
) {
	Wlbasic* wlbasic = data;
	if (strcmp(interface, wl_compositor_interface.name) == 0) {
		chk(wlbasic->compositor = wl_registry_bind(registry, name, &wl_compositor_interface, 1));
	} else if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
		chk(wlbasic->shell = wl_registry_bind(registry, name, &xdg_wm_base_interface, 1));
		xdg_wm_base_add_listener(wlbasic->shell, &shell_listener, NULL);
	}
}

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

static void handle_toplevel_configure(
	void* data,
	struct xdg_toplevel* toplevel,
	int32_t width,
	int32_t height,
	struct wl_array* states
) {
	Wlbasic* wlbasic = data;
	if (width != 0 && height != 0)
	{
		wlbasic->resize = 1;
		wlbasic->width = width;
		wlbasic->height = height;
	}
}

static void handle_toplevel_close(void* data, struct xdg_toplevel* toplevel) {
	Wlbasic* wlbasic = data;
	wlbasic->quit = true;
}

static const struct xdg_toplevel_listener toplevel_listener = {
	.configure = handle_toplevel_configure,
	.close = handle_toplevel_close
};

Wlbasic* wlbasic_init(void) {
	Wlbasic* wlbasic = malloc(sizeof(Wlbasic));
	memset(wlbasic, 0, sizeof(Wlbasic));
	chk(wlbasic->display = wl_display_connect(NULL));
	chk(wlbasic->registry = wl_display_get_registry(wlbasic->display));
	wl_registry_add_listener(wlbasic->registry, &listener, wlbasic);
	wl_display_roundtrip(wlbasic->display);
	chk(wlbasic->surface = wl_compositor_create_surface(wlbasic->compositor));
	chk(wlbasic->shell_surface =
		xdg_wm_base_get_xdg_surface(wlbasic->shell, wlbasic->surface));
	xdg_surface_add_listener(
		wlbasic->shell_surface, &shell_surface_listener, wlbasic);
	chk(wlbasic->toplevel = xdg_surface_get_toplevel(wlbasic->shell_surface));
	xdg_toplevel_add_listener(wlbasic->toplevel, &toplevel_listener, wlbasic);
	xdg_toplevel_set_title(wlbasic->toplevel, "wayland");
	xdg_toplevel_set_app_id(wlbasic->toplevel, "wayland");
	wl_surface_commit(wlbasic->surface);
	wl_display_roundtrip(wlbasic->display);
	wl_surface_commit(wlbasic->surface);
	wlbasic->width = 900;
	wlbasic->height = 600;
	return wlbasic;
}

void wlbasic_deinit(Wlbasic* wlbasic) {
	xdg_toplevel_destroy(wlbasic->toplevel);
	xdg_surface_destroy(wlbasic->shell_surface);
	wl_surface_destroy(wlbasic->surface);
	xdg_wm_base_destroy(wlbasic->shell);
	wl_compositor_destroy(wlbasic->compositor);
	wl_registry_destroy(wlbasic->registry);
	wl_display_disconnect(wlbasic->display);
	free(wlbasic);
}
