
#include "graphics/graphics.h"
#include "solution/linear_interpolator.h"
#include "solution/point_rasterizer.h"
#include "solution/line_rasterizer.h"
#include "solution/triangle_rasterizer.h"
#include "solution/math_types.h"
#include "solution/camera.h"
#include "solution/vertex_program.h"
#include "solution/fragment_program.h"
#include "solution/parser.h"


int
main(int argc, char **argv)
{
    parse_data_file("data/patches.data");
    return 0;
}