#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wayland-client.h>
#include <xkbcommon/xkbcommon.h>
#include "../include/xdg-shell-client-header.h"

#include "../include/wlbasic.h"
#include "../include/registry.h"
#include "../include/xdg.h"
#include "../include/seat.h"
#include "../include/pointer.h"
#include "../include/keyboard.h"

static void shell_surface_configure(
	void* data, struct xdg_surface* surface, uint32_t serial
) {
	Wlbasic* wlbasic = data;
	xdg_surface_ack_configure(surface, serial);
}

void wlbasic_config_default(WlbasicConfig* conf) {
	conf->shell_surface_listener.configure = shell_surface_configure;
	conf->listener.global = handle_registry;
	conf->toplevel_listener.configure = handle_toplevel_configure;
	conf->toplevel_listener.close = handle_toplevel_close;

	conf->shell_listener.ping = handle_shell_ping;
	conf->seat_listener.capabilities = wl_seat_capabilities;
	conf->seat_listener.name = wl_seat_name;

	conf->pointer_listener = (struct wl_pointer_listener) {
		.enter = wl_pointer_enter,
		.leave = wl_pointer_leave,
		.motion = wl_pointer_motion,
		.button = wl_pointer_button,
		.axis = wl_pointer_axis,
		.frame = wl_pointer_frame,
		.axis_source = wl_pointer_axis_source,
		.axis_stop = wl_pointer_axis_stop,
		.axis_discrete = wl_pointer_axis_discrete,
	};
	conf->keyboard_listener = (struct wl_keyboard_listener) {
		.keymap = wl_keyboard_keymap,
		.enter = wl_keyboard_enter,
		.leave = wl_keyboard_leave,
		.key = wl_keyboard_key,
		.modifiers = wl_keyboard_modifiers,
		.repeat_info = wl_keyboard_repeat_info,
	};
}

void wlbasic_init(Wlbasic* wl) {
	assert((wl->display = wl_display_connect(NULL)));
	assert((wl->registry = wl_display_get_registry(wl->display)));
	wl_registry_add_listener(wl->registry, &wl->conf.listener, wl);
	wl_display_roundtrip(wl->display);
	assert((wl->surface = wl_compositor_create_surface(wl->compositor)));
	assert((wl->shell_surface =
		xdg_wm_base_get_xdg_surface(wl->shell, wl->surface)));
	xdg_surface_add_listener(
		wl->shell_surface, &wl->conf.shell_surface_listener, wl);
	assert((wl->toplevel = xdg_surface_get_toplevel(wl->shell_surface)));
	xdg_toplevel_add_listener(
		wl->toplevel, &wl->conf.toplevel_listener, wl);
	xdg_toplevel_set_title(wl->toplevel, "wlbasic");
	xdg_toplevel_set_app_id(wl->toplevel, "wlbasic");
	wl_surface_commit(wl->surface);
	wl_display_roundtrip(wl->display);
	wl_surface_commit(wl->surface);
	wl->xkb_context = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
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
