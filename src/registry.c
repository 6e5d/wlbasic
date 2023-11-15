#include <stdio.h>
#include <assert.h>
#include <wayland-client.h>
#include <string.h>
#include <stdlib.h>

#include "../include/registry.h"
#include "../include/wlbasic.h"
#include "../include/seat.h"
#include "../include/tablet-unstable-v2-client-header.h"

void handle_shell_ping(
	void* data,
	struct xdg_wm_base* shell,
	uint32_t serial
) {
	xdg_wm_base_pong(shell, serial);
}

void handle_registry(
	void* data,
	struct wl_registry* registry,
	uint32_t name,
	const char* interface,
	uint32_t version
) {
	Wlbasic* wl = data;
	if (strcmp(interface, wl_compositor_interface.name) == 0) {
		assert((wl->compositor = wl_registry_bind(
			registry,
			name,
			&wl_compositor_interface,
			1
		)));
	} else if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
		assert((wl->shell = wl_registry_bind(
			registry,
			name,
			&xdg_wm_base_interface,
			1
		)));
		xdg_wm_base_add_listener(wl->shell, &wl->conf.shell_listener, NULL);
	} else if (strcmp(interface, wl_seat_interface.name) == 0) {
		wl->seat = wl_registry_bind(
			registry, name, &wl_seat_interface, 7);
		wl_seat_add_listener(wl->seat, &wl->conf.seat_listener, wl);
	} else if (!strcmp(interface, "zwp_tablet_manager_v2")) {
		wl->tabman = wl_registry_bind(
			registry, name, &zwp_tablet_manager_v2_interface, 1);
	}
	if (wl->tabseat == NULL && wl->tabman != NULL && wl->seat != NULL) {
		// printf("configure tablet\n");
		wl->tabseat = zwp_tablet_manager_v2_get_tablet_seat(
			wl->tabman, wl->seat);
		zwp_tablet_seat_v2_add_listener(
			wl->tabseat,
			&wl->conf.tabseat_listener,
			wl
		);
	}
	// } else if (strcmp(interface, tablet_manager_v2.name)) {
	// 	wl->tabman = wl_registry_bind(
	// 		registry, name, &wl_seat_interface, 7);
	// 	struct zwp_tablet_seat_v2* tablet_seat =
	// 		zwp_tablet_manager_v2_get_tablet_seat(&tman, wl->seat);
	// }
}
