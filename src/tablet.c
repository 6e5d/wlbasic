#include "../include/wlbasic.h"

static void tablet_name(void *data, struct zwp_tablet_v2 *zwp_tablet_v2,
	const char *name) {}
static void tablet_id(void* data, struct zwp_tablet_v2 *zwp_tablet_v2,
	uint32_t vid, uint32_t pid) {}
static void tablet_path(void* data, struct zwp_tablet_v2 *zwp_tablet_v2,
	const char *path) {}
static void tablet_done(void* data, struct zwp_tablet_v2 *zwp_tablet_v2) {}
static void tablet_removed(void *data, struct zwp_tablet_v2 *zwp_tablet_v2) {}

static void tablet_added(void* data,
	struct zwp_tablet_seat_v2
	*zwp_tablet_seat_v2,
	struct zwp_tablet_v2 *id
) {
	Wlbasic *wl = data;
	wl->tablet = id;
	zwp_tablet_v2_add_listener(id, &wl->conf.tablet_listener, wl);
}
static void tool_added(void* data,
	struct zwp_tablet_seat_v2* zwp_tablet_seat_v2,
	struct zwp_tablet_tool_v2 *id
) {
	Wlbasic *wl = data;
	wl->tabtool = id;
	zwp_tablet_tool_v2_add_listener(id, &wl->conf.tabtool_listener, wl);
}
static void pad_added(void* data,
	struct zwp_tablet_seat_v2* zwp_tablet_seat_v2,
	struct zwp_tablet_pad_v2 *id
) {}

static void tabtool_type(void *data, struct zwp_tablet_tool_v2* tool,
	uint32_t tool_type) {}
static void tabtool_hardware_serial(void *data,
	struct zwp_tablet_tool_v2* tool,
	uint32_t hardware_serial_hi,
	uint32_t hardware_serial_lo) {}
static void tabtool_hardware_id_wacom(void *data,
	struct zwp_tablet_tool_v2* tool,
	uint32_t hardware_id_hi,
	uint32_t hardware_id_lo) {}
static void tabtool_capability(void *data,
	struct zwp_tablet_tool_v2* tool,
	uint32_t capability) {}
static void tabtool_done(void *data, struct zwp_tablet_tool_v2* tool) {}
static void tabtool_removed(void *data, struct zwp_tablet_tool_v2* tool) {}
static void tabtool_proximity_in(void *data,
	struct zwp_tablet_tool_v2* tool, uint32_t serial,
	struct zwp_tablet_v2 *tablet, struct wl_surface *surface) {}
static void tabtool_proximity_out(void *data,
	struct zwp_tablet_tool_v2* tool) {}
static void tabtool_down(void *data, struct zwp_tablet_tool_v2* tool,
	uint32_t serial) {}
static void tabtool_up(void *data, struct zwp_tablet_tool_v2* tool) {}
static void tabtool_motion(void *data, struct zwp_tablet_tool_v2* tool,
	wl_fixed_t x, wl_fixed_t y) {
}
static void tabtool_pressure(void *data,
	struct zwp_tablet_tool_v2* tool, uint32_t pressure) {}
static void tabtool_distance(void *data,
	struct zwp_tablet_tool_v2* tool, uint32_t distance) {}
static void tabtool_tilt(void *data, struct zwp_tablet_tool_v2* tool,
	wl_fixed_t tilt_x, wl_fixed_t tilt_y) {}
static void tabtool_rotation(void *data, struct zwp_tablet_tool_v2* tool,
	wl_fixed_t degrees) {}
static void tabtool_slider(void *data,
	struct zwp_tablet_tool_v2* tool, int32_t position) {}
static void tabtool_wheel(void *data, struct zwp_tablet_tool_v2* tool,
	wl_fixed_t degrees, int32_t clicks) {}
static void tabtool_button(void *data, struct zwp_tablet_tool_v2* tool,
	uint32_t serial, uint32_t button, uint32_t state) {}
static void tabtool_frame(void *data,
	struct zwp_tablet_tool_v2* tool, uint32_t time) {}

void wlbasic_tabtool_default(struct zwp_tablet_tool_v2_listener *listener) {
	*listener = (struct zwp_tablet_tool_v2_listener) {
		.type = tabtool_type,
		.hardware_serial = tabtool_hardware_serial,
		.hardware_id_wacom = tabtool_hardware_id_wacom,
		.capability = tabtool_capability,
		.done = tabtool_done,
		.removed = tabtool_removed,
		.proximity_in = tabtool_proximity_in,
		.proximity_out = tabtool_proximity_out,
		.down = tabtool_down,
		.up = tabtool_up,
		.motion = tabtool_motion,
		.pressure = tabtool_pressure,
		.distance = tabtool_distance,
		.tilt = tabtool_tilt,
		.rotation = tabtool_rotation,
		.slider = tabtool_slider,
		.wheel = tabtool_wheel,
		.button = tabtool_button,
		.frame = tabtool_frame,
	};
}

void wlbasic_tabseat_default(struct zwp_tablet_seat_v2_listener *listener) {
	*listener = (struct zwp_tablet_seat_v2_listener) {
		.tablet_added = tablet_added,
		.tool_added = tool_added,
		.pad_added = pad_added,
	};
}

void wlbasic_tablet_default(struct zwp_tablet_v2_listener *listener) {
	*listener = (struct zwp_tablet_v2_listener) {
		.name = tablet_name,
		.id = tablet_id,
		.path = tablet_path,
		.done = tablet_done,
		.removed = tablet_removed,
	};
}
