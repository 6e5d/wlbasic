#include <wayland-client.h>

#include "../include/wlbasic.h"

static void wl_seat_capabilities(
	void *data,
	struct wl_seat*,
	uint32_t capabilities
) {
	Wlbasic *wl = data;
	bool have_pointer = capabilities & WL_SEAT_CAPABILITY_POINTER;
	if (have_pointer && wl->pointer == NULL) {
		wl->pointer = wl_seat_get_pointer(wl->seat);
		wl_pointer_add_listener(
			wl->pointer,
			&wl->conf.pointer_listener,
			wl
		);
	} else if (!have_pointer && wl->pointer != NULL) {
		wl_pointer_release(wl->pointer);
		wl->pointer = NULL;
	}

	bool have_keyboard = capabilities & WL_SEAT_CAPABILITY_KEYBOARD;
	if (have_keyboard && wl->keyboard == NULL) {
		wl->keyboard = wl_seat_get_keyboard(wl->seat);
		wl_keyboard_add_listener(wl->keyboard,
			&wl->conf.keyboard_listener, wl);
	} else if (!have_keyboard && wl->keyboard != NULL) {
		wl_keyboard_release(wl->keyboard);
		wl->keyboard = NULL;
	}
}

static void wl_seat_name(void*, struct wl_seat*, const char*) {}

void wlbasic_seat_default(struct wl_seat_listener *listener) {
	*listener = (struct wl_seat_listener) {
		.capabilities = wl_seat_capabilities,
		.name = wl_seat_name,
	};
}
