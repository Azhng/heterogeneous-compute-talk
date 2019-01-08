#pragma once

#include <iostream>
#include <chrono>
#include <ctime>

void print_timediff(
    const char* prefix,
    const struct timespec& start,
    const struct timespec& end) {

    double milliseconds = (end.tv_nsec - start.tv_nsec) / 1e6 + (end.tv_sec - start.tv_sec) * 1e3;
    printf("%s: %lf milliseconds\n", prefix, milliseconds);
}
