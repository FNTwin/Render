
#ifndef ray_h
#define ray_h
#include "geometry.h"

template <typename T> struct ray{
    ray() {}
    ray(const vec<3,T> start_point, const vec<3,T> dir){
        origin=start_point;
        direction=dir;
    }
    
    vec<3,T> orig() const  {return origin;}
    vec<3,T> dir() const {return direction;}
    
    template <typename T> vec<3,T> sample_point(float point) const{return (origin + direction * point);}
private:

    vec<3,T> origin,direction;
    
};

#endif /* ray_h */
