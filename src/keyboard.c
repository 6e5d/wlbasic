#include <wayland-client.h>

#include "../include/wlbasic.h"

static void wl_keyboard_keymap(void *data, struct wl_keyboard *wl_keyboard,
	uint32_t format, int32_t fd, uint32_t size) {}

static void wl_keyboard_key(void *data, struct wl_keyboard *wl_keyboard,
	uint32_t serial, uint32_t time, uint32_t key, uint32_t state) {}

static void wl_keyboard_enter(void *data, struct wl_keyboard *wl_keyboard,
	uint32_t serial, struct wl_surface *surface, struct wl_array *keys) {}

static void wl_keyboard_leave(void *data, struct wl_keyboard *wl_keyboard,
	uint32_t serial, struct wl_surface *surface) {}

static void wl_keyboard_modifiers(void *data, struct wl_keyboard *wl_keyboard,
	uint32_t serial, uint32_t mods_depressed,
	uint32_t mods_latched, uint32_t mods_locked,
	uint32_t group) {}

static void wl_keyboard_repeat_info(void *data,
	struct wl_keyboard *wl_keyboard,
	int32_t rate, int32_t delay) {}

void wlbasic_keyboard_default(struct wl_keyboard_listener *listener) {
	*listener = (struct wl_keyboard_listener) {
		.keymap = wl_keyboard_keymap,
		.enter = wl_keyboard_enter,
		.leave = wl_keyboard_leave,
		.key = wl_keyboard_key,
		.modifiers = wl_keyboard_modifiers,
		.repeat_info = wl_keyboard_repeat_info,
	};
}
