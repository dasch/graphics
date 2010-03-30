
#include "draw.h"

int main(int argc, char **argv)
{
    vrp = vector3_type(1, 0, 1);
    vpn = vector3_type(0, 0, 1);
    vup = vector3_type(1, 1, 1);
    prp = vector3_type(0, -70, 70);

    lower_left = vector2_type( -2.0, -2.0);
    upper_right = vector2_type( 2.0,  2.0);

    front_plane = real_type(60.0);
    back_plane = real_type(-10.0);

    render_pipeline.state().light_position() = vector3_type(-360, -74, -13);
    render_pipeline.state().eye_position() = vrp + prp;

    object_t *object;
    object = object_init();

    parse_data_file("data/pain.data", object);

    run(object, argc, argv);
}
