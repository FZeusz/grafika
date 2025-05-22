#include "app.h"

#include <stdio.h>

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    App app;

    init_app(&app, 1280, 768);
    while (app.is_running) {
        handle_app_events(&app); //billentyűzet és egér
        update_app(&app); //játéklogika
        render_app(&app); //
    }
    destroy_app(&app);

    return 0;
}
