#include <iostream>
#include <sentry.h>

bool sentry_init() {
    sentry_options_t *options = sentry_options_new();
    sentry_options_set_dsn(options, "https://unknown/0");

    sentry_options_set_database_path(options, ".sentry-native");
    sentry_options_set_release(options, "sentry-example@0.0.1");

    sentry_options_set_debug(options, 1);
    return 0 == sentry_init(options);
}

int main(int, char**) {
    sentry_init();
    return 0;
}
