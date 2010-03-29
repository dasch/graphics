
#include "draw.h"

int main(int argc, char **argv)
{
    object_t *object;
    object = object_init();

    parse_data_file("data/teapot.data", object);

    run(object, argc, argv);
}
