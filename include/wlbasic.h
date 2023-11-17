#ifndef INCLUDEGUARD_WLBASIC_WLBASICH
#define INCLUDEGUARD_WLBASIC_WLBASICH

#include <wayland-client.h>
#include <stdint.h>
#include <stdbool.h>

#include "../include/xdg-shell-client-header.h"
#include "../include/tablet-unstable-v2-client-header.h"
#include "../include/pointer-gestures-unstable-v1-client-header.h"

typedef struct {
	struct wl_registry_listener listener;
	struct xdg_surface_listener shell_surface_listener;
	struct xdg_toplevel_listener toplevel_listener;
	struct xdg_wm_base_listener shell_listener;
	struct wl_seat_listener seat_listener;
	struct wl_pointer_listener pointer_listener;
	struct wl_keyboard_listener keyboard_listener;
	struct zwp_tablet_seat_v2_listener tabseat_listener;
	struct zwp_tablet_v2_listener tablet_listener;
	struct zwp_tablet_tool_v2_listener tabtool_listener;
	struct zwp_pointer_gesture_pinch_v1_listener gepinch_listener;
} WlbasicConfig;

typedef struct {
	WlbasicConfig conf;
	struct wl_display *display;
	struct wl_registry *registry;
	struct wl_compositor *compositor;
	struct wl_surface *surface;
	struct wl_seat *seat;
	struct wl_pointer *pointer;
	struct wl_keyboard *keyboard;
	struct xdg_wm_base *shell;
	struct xdg_surface *shell_surface;
	struct xdg_toplevel *toplevel;
	struct zwp_tablet_manager_v2 *tabman;
	struct zwp_tablet_seat_v2 *tabseat;
	struct zwp_tablet_v2 *tablet;
	struct zwp_tablet_tool_v2 *tabtool;
	struct zwp_pointer_gestures_v1 *gesture;
	struct zwp_pointer_gesture_pinch_v1 *gepinch;
	void *next; // user data
} Wlbasic;

void wlbasic_config_default(WlbasicConfig *conf);
void wlbasic_init(Wlbasic *wl);
void wlbasic_deinit(Wlbasic *wl);

#endif
