#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "comparison_with_zero.h"

bool is_close(double x, double y) {
    return fabs(x - y) < EPSILON;
}

bool is_zero(double value) {
    return fabs(value) < EPSILON;
}
