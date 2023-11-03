#include <wayland-client.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
	struct wl_display* display;
	struct wl_registry* registry;
	struct wl_compositor* compositor;
	struct wl_surface* surface;
	struct xdg_wm_base* shell;
	struct xdg_surface* shell_surface;
	struct xdg_toplevel* toplevel;
	bool quit;
	bool resize;
	int32_t width;
	int32_t height;
} Wlbasic;

Wlbasic* wlbasic_init(void);
void wlbasic_deinit(Wlbasic* wlbasic);
