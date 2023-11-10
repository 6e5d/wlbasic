#include <assert.h>
#include <wayland-client.h>
#include <string.h>
#include <stdlib.h>

#include "../include/registry.h"
#include "../include/wlbasic.h"
#include "../include/seat.h"

void handle_shell_ping(
	void* data,
	struct xdg_wm_base* shell,
	uint32_t serial
) {
	xdg_wm_base_pong(shell, serial);
}

static const struct xdg_wm_base_listener shell_listener = {
	.ping = handle_shell_ping
};

static const struct wl_seat_listener wl_seat_listener = {
	.capabilities = wl_seat_capabilities,
	.name = wl_seat_name,
};

void handle_registry(
	void* data,
	struct wl_registry* registry,
	uint32_t name,
	const char* interface,
	uint32_t version
) {
	Wlbasic* wlbasic = data;
	if (strcmp(interface, wl_compositor_interface.name) == 0) {
		assert((wlbasic->compositor = wl_registry_bind(
			registry,
			name,
			&wl_compositor_interface,
			1
		)));
	} else if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
		assert((wlbasic->shell = wl_registry_bind(
			registry,
			name,
			&xdg_wm_base_interface,
			1
		)));
		xdg_wm_base_add_listener(wlbasic->shell, &shell_listener, NULL);
	} else if (strcmp(interface, wl_seat_interface.name) == 0) {
		wlbasic->seat = wl_registry_bind(
			registry, name, &wl_seat_interface, 7);
		wl_seat_add_listener(wlbasic->seat, &wl_seat_listener, wlbasic);
	}
}
