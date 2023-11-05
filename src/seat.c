#include <stdio.h>
#include <wayland-client.h>

#include "../include/wlbasic.h"
#include "../include/pointer.h"

static const struct wl_pointer_listener wl_pointer_listener = {
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

void wl_seat_capabilities(
	void *data,
	struct wl_seat *wl_seat,
	uint32_t capabilities
) {
	Wlbasic *state = data;
	bool have_pointer = capabilities & WL_SEAT_CAPABILITY_POINTER;
	if (have_pointer && state->pointer == NULL) {
		state->pointer = wl_seat_get_pointer(state->seat);
		wl_pointer_add_listener(state->pointer,
				&wl_pointer_listener, state);
	} else if (!have_pointer && state->pointer != NULL) {
		wl_pointer_release(state->pointer);
		state->pointer = NULL;
	}
}

void wl_seat_name(
	void *data,
	struct wl_seat *wl_seat,
	const char *name
) {
	printf("seat name: %s\n", name);
}
