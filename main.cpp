#include <iostream>
#include "color.h"
#include "vec3.h"
#include "ray.h"

bool hit_sphere(const point3& center, double radius, const ray& r) {
    // uses quadratic formula to figure whether the ray r passes through the sphere
    vec3 oc = r.origin() - center;
    double a = dot(r.direction(),r.direction());
    double b = 2.0 * dot(r.direction(),oc);
    double c = dot(oc,oc) - pow(radius, 2);
    double determinant = pow(b,2) - 4*a*c;
    if (determinant>=0) { return true; }
    else { return false; }
}

color ray_color(const ray& r) {
    if (hit_sphere(point3(0,0,-1), 0.5, r)) {
        return color(1,0,0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0); // scaling t so that when y = 1, t=1 and when y = -1, t=0
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0); // linear belend of color from white-to-blue
}
int main() {
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 384;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1); // u iterates from 1 to 0
            auto v = double(j) / (image_height-1); // v iterates from 1 to 0
            // u*horizontal and v*vertical converts the lengths to local coordinates on viewpoint from the bottom left.
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin); // create ray passing through origin and u and v on the viewport plane
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}