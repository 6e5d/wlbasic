#ifndef INCLUDEGUARD_WLBASIC
#define INCLUDEGUARD_WLBASIC

#include <wayland-client.h>

#include "../include/tablet-unstable-v2.external.h"
#include "../include/xdg-shell.external.h"
#include "../include/xdg-decoration-unstable-v1.external.h"
#include "../include/pointer-gestures-unstable-v1.external.h"

#define Wlbasic(sym) Com_6e5dWlbasic##sym
#define wlbasic(sym) com_6e5d_wlbasic_##sym

typedef struct {
	struct wl_registry_listener listener;
	struct wl_output_listener output_listener;
	struct wl_surface_listener surface_listener;
	struct xdg_surface_listener shell_surface_listener;
	struct xdg_toplevel_listener toplevel_listener;
	struct xdg_wm_base_listener shell_listener;
	struct wl_seat_listener seat_listener;
	struct wl_pointer_listener pointer_listener;
	struct wl_keyboard_listener keyboard_listener;
	struct zxdg_toplevel_decoration_v1_listener topdeco_listener;
	struct zwp_tablet_seat_v2_listener tabseat_listener;
	struct zwp_tablet_v2_listener tablet_listener;
	struct zwp_tablet_tool_v2_listener tabtool_listener;
	struct zwp_pointer_gesture_pinch_v1_listener gepinch_listener;
} Wlbasic(Config);

typedef struct {
	Wlbasic(Config) conf;
	struct wl_display *display;
	struct wl_registry *registry;
	struct wl_output *output;
	struct wl_compositor *compositor;
	struct wl_surface *surface;
	struct wl_seat *seat;
	struct wl_pointer *pointer;
	struct wl_keyboard *keyboard;
	struct xdg_wm_base *shell;
	struct xdg_surface *shell_surface;
	struct xdg_toplevel *toplevel;
	struct zxdg_decoration_manager_v1 *deco_manager;
	struct zxdg_toplevel_decoration_v1 *topdeco;
	struct zwp_tablet_manager_v2 *tabman;
	struct zwp_tablet_seat_v2 *tabseat;
	struct zwp_tablet_v2 *tablet;
	struct zwp_tablet_tool_v2 *tabtool;
	struct zwp_pointer_gestures_v1 *gesture;
	struct zwp_pointer_gesture_pinch_v1 *gepinch;
	int32_t scale;
	void *next; // user data
} Wlbasic();

void wlbasic(config_default)(Wlbasic(Config) *conf);
void wlbasic(init)(Wlbasic() *wl);
void wlbasic(deinit)(Wlbasic() *wl);

void wlbasic(seat_default)(struct wl_seat_listener *listener);
void wlbasic(surface_default)(struct wl_surface_listener *listener);
void wlbasic(output_default)(struct wl_output_listener *listener);
void wlbasic(keyboard_default)(struct wl_keyboard_listener *listener);
void wlbasic(pointer_default)(struct wl_pointer_listener *listener);
void wlbasic(tablet_default)(struct zwp_tablet_v2_listener *listener);
void wlbasic(tabseat_default)(struct zwp_tablet_seat_v2_listener *listener);
void wlbasic(tabtool_default)(struct zwp_tablet_tool_v2_listener *listener);
void wlbasic(gepinch_default)(struct zwp_pointer_gesture_pinch_v1_listener *listener);

#endif
