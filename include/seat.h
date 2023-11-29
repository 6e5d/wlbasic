#ifndef INCLUDEGUARD_WLBASIC_SEATH
#define INCLUDEGUARD_WLBASIC_SEATH

#include <wayland-client.h>
#include <stdint.h>

void wl_seat_capabilities(
	void *data,
	struct wl_seat *wl_seat,
	uint32_t capabilities
);

void wl_seat_name(
	void *data,
	struct wl_seat *wl_seat,
	const char *name
);

#endif
