#ifndef RAY_TRACING_HITTABLE_LIST_H
#define RAY_TRACING_HITTABLE_LIST_H

#include "rtweekend.h"

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr; // 'using' tells the compiler that we dont need std:: every time we reference either of the fellowing
using std::make_shared;

class hittable_list: public hittable {
public:
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<hittable> object) { objects.push_back(object); } // push_back will add object to end of the vector objects

    virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const;

public:
    std::vector<shared_ptr<hittable>> objects; // creates a vector of shared pointers of type hittable
};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const { // returns if the ray hits anything and rec will contain record of the nearest hit point
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}


#endif //RAY_TRACING_HITTABLE_LIST_H
