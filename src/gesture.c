#include "../include/wlbasic.h"
#include "../include/pointer-gestures-unstable-v1.external.h"

static void gepinch_begin(void*, struct zwp_pointer_gesture_pinch_v1*,
	uint32_t, uint32_t, struct wl_surface*, uint32_t) {}
static void gepinch_update(void*, struct zwp_pointer_gesture_pinch_v1*,
	uint32_t, wl_fixed_t, wl_fixed_t, wl_fixed_t, wl_fixed_t) {}
static void gepinch_end(void*, struct zwp_pointer_gesture_pinch_v1*,
	uint32_t, uint32_t, int32_t) {}

void wlbasic_gepinch_default(
	struct zwp_pointer_gesture_pinch_v1_listener *listener
) {
	*listener = (struct zwp_pointer_gesture_pinch_v1_listener) {
		.begin = gepinch_begin,
		.update = gepinch_update,
		.end = gepinch_end,
	};
}
