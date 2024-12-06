#ifndef NBODY_H
#define NBODY_H    

#include <stddef.h>

float 
nbody_getr2f(const float* const dx);

void 
nbody_stepf(float* const restrict x, 
            float* const restrict v,
            const float* const restrict m, 
            const size_t N, const float dt);

#endif // nbody.h
