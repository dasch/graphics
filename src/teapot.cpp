
#include "draw.h"

int main(int argc, char **argv)
{
    if (1) {
        vrp = vector3_type(0, 0, 1);
        vpn = vector3_type(0, 0, 1);
        vup = vector3_type(0, 1, 0);
        prp = vector3_type(0, 0, 70);

        lower_left = vector2_type( -3.5, -3.5);
        upper_right = vector2_type( 3.5,  3.5);

        front_plane = real_type(3.5);
        back_plane = real_type(-1.0);

        render_pipeline.state().eye_position() = vrp;
    } else {
        vrp = vector3_type(0, 0, 1);
        vpn = vector3_type(0, 0, 1);
        vup = vector3_type(0, 1, 0);
        prp = vector3_type(0, -70, 70);

        lower_left = vector2_type( -5.0, -5.0);
        upper_right = vector2_type( 5.0,  5.0);

        front_plane = real_type(60.0);
        back_plane = real_type(-10.0);

        render_pipeline.state().eye_position() = vrp + prp;
    }

    render_pipeline.state().light_position() = vector3_type(360, 447, 43);

    object_t *object;
    object = object_init();

    parse_data_file("data/teapot.data", object);

    run(object, argc, argv);
}
