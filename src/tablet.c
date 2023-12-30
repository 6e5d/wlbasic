#include "../include/wlbasic.h"

static void tablet_name(void*, struct zwp_tablet_v2*, const char*) {}
static void tablet_id(void*, struct zwp_tablet_v2*, uint32_t, uint32_t) {}
static void tablet_path(void*, struct zwp_tablet_v2*, const char*) {}
static void tablet_done(void*, struct zwp_tablet_v2*) {}
static void tablet_removed(void*, struct zwp_tablet_v2*) {}

static void tablet_added(void* data,
	struct zwp_tablet_seat_v2*,
	struct zwp_tablet_v2 *id
) {
	Wlbasic() *wl = data;
	wl->tablet = id;
	zwp_tablet_v2_add_listener(id, &wl->conf.tablet_listener, wl);
}
static void tool_added(void* data,
	struct zwp_tablet_seat_v2*,
	struct zwp_tablet_tool_v2* id
) {
	Wlbasic() *wl = data;
	wl->tabtool = id;
	zwp_tablet_tool_v2_add_listener(id, &wl->conf.tabtool_listener, wl);
}
static void pad_added(void*,
	struct zwp_tablet_seat_v2*,
	struct zwp_tablet_pad_v2*) {}

static void tabtool_type(void*, struct zwp_tablet_tool_v2*, uint32_t) {}
static void tabtool_hardware_serial(void*,
	struct zwp_tablet_tool_v2*, uint32_t, uint32_t) {}
static void tabtool_hardware_id_wacom(void*,
	struct zwp_tablet_tool_v2*, uint32_t, uint32_t) {}
static void tabtool_capability(void*, struct zwp_tablet_tool_v2*, uint32_t) {}
static void tabtool_done(void*, struct zwp_tablet_tool_v2*) {}
static void tabtool_removed(void*, struct zwp_tablet_tool_v2*) {}
static void tabtool_proximity_in(void*,
	struct zwp_tablet_tool_v2*, uint32_t,
	struct zwp_tablet_v2*, struct wl_surface*) {}
static void tabtool_proximity_out(void*, struct zwp_tablet_tool_v2*) {}
static void tabtool_down(void*, struct zwp_tablet_tool_v2*, uint32_t) {}
static void tabtool_up(void*, struct zwp_tablet_tool_v2*) {}
static void tabtool_motion(void*, struct zwp_tablet_tool_v2*,
	wl_fixed_t, wl_fixed_t) {}
static void tabtool_pressure(void*, struct zwp_tablet_tool_v2*, uint32_t) {}
static void tabtool_distance(void*, struct zwp_tablet_tool_v2*, uint32_t) {}
static void tabtool_tilt(void*, struct zwp_tablet_tool_v2*,
	wl_fixed_t, wl_fixed_t) {}
static void tabtool_rotation(void*, struct zwp_tablet_tool_v2*, wl_fixed_t) {}
static void tabtool_slider(void*,
	struct zwp_tablet_tool_v2*, int32_t) {}
static void tabtool_wheel(void*, struct zwp_tablet_tool_v2*,
	wl_fixed_t, int32_t) {}
static void tabtool_button(void*, struct zwp_tablet_tool_v2*,
	uint32_t, uint32_t, uint32_t) {}
static void tabtool_frame(void*,
	struct zwp_tablet_tool_v2*, uint32_t) {}

void wlbasic(tabtool_default)(struct zwp_tablet_tool_v2_listener *listener) {
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

void wlbasic(tabseat_default)(struct zwp_tablet_seat_v2_listener *listener) {
	*listener = (struct zwp_tablet_seat_v2_listener) {
		.tablet_added = tablet_added,
		.tool_added = tool_added,
		.pad_added = pad_added,
	};
}

void wlbasic(tablet_default)(struct zwp_tablet_v2_listener *listener) {
	*listener = (struct zwp_tablet_v2_listener) {
		.name = tablet_name,
		.id = tablet_id,
		.path = tablet_path,
		.done = tablet_done,
		.removed = tablet_removed,
	};
}
