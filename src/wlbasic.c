#include <wayland-client.h>

#include "../include/wlbasic.h"
#include "../include/xdg-shell-client-header.h"

static void handle_toplevel_configure(
	void* data,
	struct xdg_toplevel* toplevel,
	int32_t width,
	int32_t height,
	struct wl_array* states
) {
	Wlbasic *wl = data;
	wl_surface_set_buffer_scale(wl->surface, 1);
}

static void handle_toplevel_close(void* data, struct xdg_toplevel* toplevel) {}

static void wlbasic_topdeco_configure(void *data,
	struct zxdg_toplevel_decoration_v1 *zxdg_toplevel_decoration_v1,
	uint32_t mode) {}

static void shell_surface_configure(
	void* data, struct xdg_surface* surface, uint32_t serial
) {
	Wlbasic *wl = data;
	xdg_surface_ack_configure(surface, serial);
	wl_surface_set_buffer_scale(wl->surface, wl->scale);
	wl_surface_commit(wl->surface);
}

static void handle_shell_ping(
	void *data,
	struct xdg_wm_base *shell,
	uint32_t serial
) {
	xdg_wm_base_pong(shell, serial);
}

static void handle_registry(
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

void wlbasic_config_default(WlbasicConfig* conf) {
	conf->shell_surface_listener.configure = shell_surface_configure;
	conf->listener.global = handle_registry;
	conf->toplevel_listener.configure = handle_toplevel_configure;
	conf->toplevel_listener.close = handle_toplevel_close;
	conf->topdeco_listener.configure = wlbasic_topdeco_configure;
	conf->shell_listener.ping = handle_shell_ping;

	wlbasic_seat_default(&conf->seat_listener);
	wlbasic_surface_default(&conf->surface_listener);
	wlbasic_output_default(&conf->output_listener);
	wlbasic_keyboard_default(&conf->keyboard_listener);
	wlbasic_pointer_default(&conf->pointer_listener);
	wlbasic_tablet_default(&conf->tablet_listener);
	wlbasic_tabseat_default(&conf->tabseat_listener);
	wlbasic_tabtool_default(&conf->tabtool_listener);
	wlbasic_gepinch_default(&conf->gepinch_listener);
}

static void wlbasic_init2(Wlbasic* wl) {
	if (wl->toplevel != NULL && wl->deco_manager != NULL) {
		wl->topdeco = zxdg_decoration_manager_v1_get_toplevel_decoration(
			wl->deco_manager, wl->toplevel);
		zxdg_toplevel_decoration_v1_set_mode(wl->topdeco,
			ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);
		zxdg_toplevel_decoration_v1_add_listener(wl->topdeco,
			&wl->conf.topdeco_listener, wl);
	}
	if (wl->tabseat == NULL && wl->tabman != NULL && wl->seat != NULL) {
		wl->tabseat = zwp_tablet_manager_v2_get_tablet_seat(
			wl->tabman, wl->seat);
		zwp_tablet_seat_v2_add_listener(
			wl->tabseat,
			&wl->conf.tabseat_listener,
			wl
		);
	}
	if (wl->pointer != NULL && wl->gepinch == NULL && wl->gesture != NULL) {
		wl->gepinch = zwp_pointer_gestures_v1_get_pinch_gesture(
			wl->gesture, wl->pointer);
		zwp_pointer_gesture_pinch_v1_add_listener(wl->gepinch,
			&wl->conf.gepinch_listener, wl);
	}
}

void wlbasic_init(Wlbasic* wl) {
	wl->scale = 1;
	assert((wl->display = wl_display_connect(NULL)));
	assert((wl->registry = wl_display_get_registry(wl->display)));
	wl_registry_add_listener(wl->registry, &wl->conf.listener, wl);
	wl_display_roundtrip(wl->display);
	assert((wl->surface = wl_compositor_create_surface(wl->compositor)));
	wl_surface_add_listener(wl->surface, &wl->conf.surface_listener, wl);
	assert((wl->shell_surface =
		xdg_wm_base_get_xdg_surface(wl->shell, wl->surface)));
	xdg_surface_add_listener(
		wl->shell_surface, &wl->conf.shell_surface_listener, wl);
	assert((wl->toplevel = xdg_surface_get_toplevel(wl->shell_surface)));
	xdg_toplevel_add_listener(
		wl->toplevel, &wl->conf.toplevel_listener, wl);
	wl_surface_commit(wl->surface);
	wl_display_roundtrip(wl->display);
	wlbasic_init2(wl);
	wl_surface_commit(wl->surface);
}

void wlbasic_deinit(Wlbasic* wlbasic) {
	if (wlbasic->tablet) {
		zwp_tablet_v2_destroy(wlbasic->tablet);
	}
	if (wlbasic->tabseat) {
		zwp_tablet_seat_v2_destroy(wlbasic->tabseat);
	}
	if (wlbasic->tabman) {
		zwp_tablet_manager_v2_destroy(wlbasic->tabman);
	}
	if (wlbasic->deco_manager) {
		zxdg_decoration_manager_v1_destroy(wlbasic->deco_manager);
	}
	if (wlbasic->topdeco) {
		zxdg_toplevel_decoration_v1_destroy(wlbasic->topdeco);
	}
	if (wlbasic->gepinch) {
		zwp_pointer_gesture_pinch_v1_destroy(wlbasic->gepinch);
	}
	if (wlbasic->gesture) {
		zwp_pointer_gestures_v1_destroy(wlbasic->gesture);
	}
	xdg_toplevel_destroy(wlbasic->toplevel);
	xdg_surface_destroy(wlbasic->shell_surface);
	xdg_wm_base_destroy(wlbasic->shell);
	wl_pointer_destroy(wlbasic->pointer);
	wl_keyboard_destroy(wlbasic->keyboard);
	wl_surface_destroy(wlbasic->surface);
	wl_compositor_destroy(wlbasic->compositor);
	wl_seat_destroy(wlbasic->seat);
	wl_registry_destroy(wlbasic->registry);
	wl_output_destroy(wlbasic->output);
	wl_display_disconnect(wlbasic->display);
}
