#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <sys/mman.h>
#include <wayland-client.h>
#include <xkbcommon/xkbcommon.h>

#include "../include/wlbasic.h"
#include "../include/keyboard.h"

void wl_keyboard_keymap(void *data, struct wl_keyboard *wl_keyboard,
	uint32_t format, int32_t fd, uint32_t size) {}

void wl_keyboard_key(void *data, struct wl_keyboard *wl_keyboard,
	uint32_t serial, uint32_t time, uint32_t key, uint32_t state) {}

void wl_keyboard_enter(void *data, struct wl_keyboard *wl_keyboard,
	uint32_t serial, struct wl_surface *surface, struct wl_array *keys)
{}

void wl_keyboard_leave(void *data, struct wl_keyboard *wl_keyboard,
	uint32_t serial, struct wl_surface *surface) {}

void wl_keyboard_modifiers(void *data, struct wl_keyboard *wl_keyboard,
	uint32_t serial, uint32_t mods_depressed,
	uint32_t mods_latched, uint32_t mods_locked,
	uint32_t group) {}

void wl_keyboard_repeat_info(void *data, struct wl_keyboard *wl_keyboard,
	int32_t rate, int32_t delay)
{}
