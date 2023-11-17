#include <assert.h>
#include <wayland-client.h>

#include "../include/wlbasic.h"
#include "../include/pointer.h"
#include "../include/seat.h"

void wl_seat_capabilities(
	void *data,
	struct wl_seat *wl_seat,
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
		assert(wl->gepinch == NULL && wl->gesture != NULL);
		wl->gepinch = zwp_pointer_gestures_v1_get_pinch_gesture(
			wl->gesture,
			wl->pointer);
		zwp_pointer_gesture_pinch_v1_add_listener(wl->gepinch,
			&wl->conf.gepinch_listener, wl);
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

void wl_seat_name(
	void *data,
	struct wl_seat *wl_seat,
	const char *name
) {}
