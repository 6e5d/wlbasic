#include <stdio.h>
#include <assert.h>
#include <wayland-client.h>
#include <string.h>
#include <stdlib.h>

#include "../include/registry.h"
#include "../include/wlbasic.h"
#include "../include/seat.h"
#include "../include/tablet-unstable-v2-client-header.h"
#include "../include/pointer-gestures-unstable-v1-client-header.h"
#include "../include/xdg-decoration-unstable-v1-client-header.h"

void handle_shell_ping(
	void *data,
	struct xdg_wm_base *shell,
	uint32_t serial
) {
	xdg_wm_base_pong(shell, serial);
}

void handle_registry(
	void *data,
	struct wl_registry *registry,
	uint32_t name,
	const char *interface,
	uint32_t version
) {
	Wlbasic *wl = data;
	if (strcmp(interface, wl_compositor_interface.name) == 0) {
		assert((wl->compositor = wl_registry_bind(
			registry,
			name,
			&wl_compositor_interface,
			3
		)));
	} else if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
		assert((wl->shell = wl_registry_bind(
			registry,
			name,
			&xdg_wm_base_interface,
			2
		)));
		xdg_wm_base_add_listener(
			wl->shell, &wl->conf.shell_listener, NULL);
	} else if (strcmp(interface, wl_seat_interface.name) == 0) {
		wl->seat = wl_registry_bind(
			registry, name, &wl_seat_interface, 7);
		wl_seat_add_listener(wl->seat, &wl->conf.seat_listener, wl);
	} else if (!strcmp(interface, "zwp_tablet_manager_v2")) {
		wl->tabman = wl_registry_bind(
			registry, name, &zwp_tablet_manager_v2_interface, 1);
	} else if (!strcmp(interface, "zwp_pointer_gestures_v1")) {
		wl->gesture = wl_registry_bind(
			registry, name, &zwp_pointer_gestures_v1_interface, 1);
	} else if (!strcmp(interface, "zxdg_decoration_manager_v1")) {
		wl->deco_manager = wl_registry_bind(
			registry, name, &zxdg_decoration_manager_v1_interface, 1);
	} else if (!strcmp(interface, "wl_output")) {
		wl->output = wl_registry_bind(
			registry, name, &wl_output_interface, 4);
		wl_output_add_listener(wl->output, &wl->conf.output_listener, wl);
	}
}
