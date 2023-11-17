#include <stdint.h>
#include <stdio.h>

#include "../include/gesture.h"
#include "../include/pointer-gestures-unstable-v1-client-header.h"

void gepinch_begin(void *data,
	struct zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1,
	uint32_t serial,
	uint32_t time,
	struct wl_surface *surface,
	uint32_t fingers) {}
void gepinch_update(void *data,
	struct zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1,
	uint32_t time,
	wl_fixed_t dx,
	wl_fixed_t dy,
	wl_fixed_t scale,
	wl_fixed_t rotation) {}
void gepinch_end(void *data,
	struct zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1,
	uint32_t serial,
	uint32_t time,
	int32_t cancelled) {}
