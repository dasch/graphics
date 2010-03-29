
#include "draw.h"

int main(int argc, char **argv)
{
    vrp = vector3_type(5, 5, -1);
    vpn = vector3_type(0, 0, -1);
    vup = vector3_type(0, 1, 0);
    prp = vector3_type(-50, 20, 70);

    lower_left = vector2_type( -12.0, -12.0);
    upper_right = vector2_type( 12.0,  12.0);

    front_plane = real_type(60.0);
    back_plane = real_type(-10.0);

    object_t *object;
    object = object_init();

    parse_data_file("data/patches.data", object);

    run(object, argc, argv);
}
