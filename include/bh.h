#ifndef NBODY_BH_H
#define NBODY_BH_H

struct nbody_bh_node;

struct nbody_bh_node*
nbody_bh_tree_build(const float* const restrict x,
                    const float* const restrict m,
                    const long int N,
                    const float bb_x_min,
                    const float bb_x_max);

struct nbody_bh_node*
nbody_bh_tree_traverse(struct nbody_bh_node* tree, 
                       const float* const restrict x,
                       const long int i);

struct nbody_bh_node*
nbody_bh_tree_delete(struct nbody_bh_node* tree);

#endif // NBODY_BH_H
