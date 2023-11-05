#include <wayland-client.h>

#include "../include/xdg-shell-client-header.h"

void handle_shell_ping(
	void* data,
	struct xdg_wm_base* shell,
	uint32_t serial
);

void handle_registry(
	void* data,
	struct wl_registry* registry,
	uint32_t name,
	const char* interface,
	uint32_t version
);
