#include <wayland-client.h>

#include "../include/wlbasic.h"

static void wl_keyboard_keymap(void*, struct wl_keyboard*,
	uint32_t, int32_t, uint32_t) {}

static void wl_keyboard_key(void*, struct wl_keyboard*,
	uint32_t, uint32_t, uint32_t, uint32_t) {}

static void wl_keyboard_enter(void*, struct wl_keyboard*,
	uint32_t, struct wl_surface*, struct wl_array*) {}

static void wl_keyboard_leave(void*, struct wl_keyboard*,
	uint32_t, struct wl_surface*) {}

static void wl_keyboard_modifiers(void*, struct wl_keyboard*,
	uint32_t, uint32_t, uint32_t, uint32_t, uint32_t) {}

static void wl_keyboard_repeat_info(void*, struct wl_keyboard*,
	int32_t, int32_t) {}

void wlbasic(keyboard_default)(struct wl_keyboard_listener *listener) {
	*listener = (struct wl_keyboard_listener) {
		.keymap = wl_keyboard_keymap,
		.enter = wl_keyboard_enter,
		.leave = wl_keyboard_leave,
		.key = wl_keyboard_key,
		.modifiers = wl_keyboard_modifiers,
		.repeat_info = wl_keyboard_repeat_info,
	};
}
