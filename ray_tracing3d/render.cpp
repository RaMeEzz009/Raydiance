#include "rtweekend.h"

#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include <cmath>

int main() {
    hittable_list world;

    // ---------- Checkerboard Ground ----------
    auto white = make_shared<lambertian>(color(0.9, 0.9, 0.9));
    auto black = make_shared<lambertian>(color(0.1, 0.1, 0.1));

    // Make 8x8 checkerboard squares as flat spheres (huge radius below ground)
    int tiles = 8;
    double tile_size = 2.0;
    for (int x = -tiles; x < tiles; x++) {
        for (int z = -tiles; z < tiles; z++) {
            auto mat = ((x + z) % 2 == 0) ? white : black;
            point3 center(x * tile_size, -1000.0, z * tile_size);
            // giant underground sphere for flat tile illusion
            world.add(make_shared<sphere>(center, 1000.0, mat));
        }
    }

    // ---------- Feature Spheres ----------
    auto glass_ball   = make_shared<dielectric>(1.5);
    auto red_diffuse  = make_shared<lambertian>(color(0.8, 0.1, 0.1));
    auto blue_diffuse = make_shared<lambertian>(color(0.1, 0.2, 0.8));
    auto gold_metal   = make_shared<metal>(color(1.0, 0.85, 0.4), 0.05);
    auto rough_metal  = make_shared<metal>(color(0.7, 0.7, 0.7), 0.4);

    world.add(make_shared<sphere>(point3(-3, 1, -2), 1.0, red_diffuse));
    world.add(make_shared<sphere>(point3( 3, 1, -2), 1.0, blue_diffuse));
    world.add(make_shared<sphere>(point3( 0, 1,  0), 1.0, glass_ball));
    world.add(make_shared<sphere>(point3(-2, 0.6,  3), 0.6, gold_metal));
    world.add(make_shared<sphere>(point3( 2, 0.6,  3), 0.6, rough_metal));

    // ---------- Floating glass orbs ----------
    for (int i = 0; i < 4; i++) {
        auto orb = make_shared<dielectric>(1.5);
        world.add(make_shared<sphere>(
            point3(random_double(-3,3), random_double(2,3), random_double(-3,3)),
            0.3, orb));
    }

    // ---------- Camera ----------
    camera cam;
    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 50;
    cam.max_depth         = 10;

    cam.vfov      = 30;
    cam.lookfrom  = point3(8, 4, 6);
    cam.lookat    = point3(0, 1, 0);
    cam.vup       = vec3(0, 1, 0);

    cam.defocus_angle = 0.4;  // blur (set 0 to disable)
    cam.focus_dist    = 10.0;

    cam.render(world);
}
