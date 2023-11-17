#include <stdio.h>

#include "../include/wlbasic.h"
#include "../include/tablet.h"

void tablet_name(
	void *data, struct zwp_tablet_v2 *zwp_tablet_v2, const char *name) {}
void tablet_id(void* data, struct zwp_tablet_v2 *zwp_tablet_v2,
	uint32_t vid, uint32_t pid) {}
void tablet_path(void* data, struct zwp_tablet_v2 *zwp_tablet_v2,
	const char *path) {}
void tablet_done(void* data, struct zwp_tablet_v2 *zwp_tablet_v2) {}
void tablet_removed(void *data, struct zwp_tablet_v2 *zwp_tablet_v2) {}

void tablet_added(void* data, struct zwp_tablet_seat_v2 *zwp_tablet_seat_v2,
	struct zwp_tablet_v2 *id) {
	Wlbasic *wl = data;
	wl->tablet = id;
	zwp_tablet_v2_add_listener(id, &wl->conf.tablet_listener, wl);
}
void tool_added(void* data, struct zwp_tablet_seat_v2* zwp_tablet_seat_v2,
	struct zwp_tablet_tool_v2 *id) {
	Wlbasic *wl = data;
	wl->tabtool = id;
	zwp_tablet_tool_v2_add_listener(id, &wl->conf.tabtool_listener, wl);
}
void pad_added(void* data, struct zwp_tablet_seat_v2* zwp_tablet_seat_v2,
	struct zwp_tablet_pad_v2 *id) {}

void tabtool_type(void *data, struct zwp_tablet_tool_v2* tool,
	uint32_t tool_type) {}
void tabtool_hardware_serial(void *data, struct zwp_tablet_tool_v2* tool,
	uint32_t hardware_serial_hi, uint32_t hardware_serial_lo) {}
void tabtool_hardware_id_wacom(void *data, struct zwp_tablet_tool_v2* tool,
	uint32_t hardware_id_hi, uint32_t hardware_id_lo) {}
void tabtool_capability(void *data, struct zwp_tablet_tool_v2* tool,
	uint32_t capability) {}
void tabtool_done(void *data, struct zwp_tablet_tool_v2* tool) {}
void tabtool_removed(void *data, struct zwp_tablet_tool_v2* tool) {}
void tabtool_proximity_in(void *data, struct zwp_tablet_tool_v2* tool, uint32_t serial,
	struct zwp_tablet_v2 *tablet, struct wl_surface *surface) {}
void tabtool_proximity_out(void *data, struct zwp_tablet_tool_v2* tool) {}
void tabtool_down(void *data, struct zwp_tablet_tool_v2* tool,
	uint32_t serial) {}
void tabtool_up(void *data, struct zwp_tablet_tool_v2* tool) {}
void tabtool_motion(void *data, struct zwp_tablet_tool_v2* tool,
	wl_fixed_t x, wl_fixed_t y) {
}
void tabtool_pressure(void *data,
	struct zwp_tablet_tool_v2* tool, uint32_t pressure) {}
void tabtool_distance(void *data,
	struct zwp_tablet_tool_v2* tool, uint32_t distance) {}
void tabtool_tilt(void *data, struct zwp_tablet_tool_v2* tool,
	wl_fixed_t tilt_x, wl_fixed_t tilt_y) {}
void tabtool_rotation(void *data, struct zwp_tablet_tool_v2* tool,
	wl_fixed_t degrees) {}
void tabtool_slider(void *data,
	struct zwp_tablet_tool_v2* tool, int32_t position) {}
void tabtool_wheel(void *data, struct zwp_tablet_tool_v2* tool,
	wl_fixed_t degrees, int32_t clicks) {}
void tabtool_button(void *data, struct zwp_tablet_tool_v2* tool,
	uint32_t serial, uint32_t button, uint32_t state) {}
void tabtool_frame(void *data, struct zwp_tablet_tool_v2* tool, uint32_t time) {}
