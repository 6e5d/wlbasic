#include <stdio.h>
#include <wayland-client.h>

#include "../include/wlbasic.h"
#include "../include/pointer.h"

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
			&wl->conf.wl_pointer_listener,
			wl
		);
	} else if (!have_pointer && wl->pointer != NULL) {
		wl_pointer_release(wl->pointer);
		wl->pointer = NULL;
	}
}

void wl_seat_name(
	void *data,
	struct wl_seat *wl_seat,
	const char *name
) {
	printf("seat name: %s\n", name);
}
