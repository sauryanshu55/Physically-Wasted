#include <bh.h>
#include <global.h>
#include <math.h>

// TODO : test tree building !!

#define NBODY_TREE_CHILD_MAX 8 // 2 ^ DIM 

struct nbody_bh_node {

        float bb_center[DIM];
        float bb_size;
 
        float m;
        float cm[DIM];
        
        short int is_leaf;
        long int p_id;  
        long int p_n;
 
        struct nbody_bh_node* parent;
        struct nbody_bh_node* next[8];

};

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

static struct nbody_bh_node*
nbody_bh_node_new(void) {

        struct nbody_bh_node* node = malloc(sizeof(struct nbody_bh_node));
        if (node == NULL) {

                perror("memory allocation error");
                exit(EXIT_FAILURE);

        }

        memset(node, 0, sizeof(struct nbody_bh_node)) ;

        return node;

}

static struct nbody_bh_node*
nbody_bh_tree_new(const float bb_x_min,
                  const float bb_x_max) {

        struct nbody_bh_node* tree = nbody_bh_node_new();

        (*tree).bb_size = (bb_x_max - bb_x_min) / 2.00f;

        for (int i = 0; i < DIM; i++) {

                (*tree).bb_center[i] = (*tree).bb_size;
                (*tree).cm[i] = 0;
                
        }

        (*tree).m = 0;

        (*tree).is_leaf = 1;
        (*tree).p_id = -1;
        (*tree).p_n = 1;
        (*tree).parent = NULL;

        return tree;

}

// TODO : decompose functions !!!
static void
nbody_bh_tree_insert(struct nbody_bh_node* tree,
                     const float* const restrict x, 
                     const float* const restrict m, 
                     const long int i) {

        struct nbody_bh_node* node = tree;
        if (node == NULL) {

                perror("tree parameter NULL");
                exit(EXIT_FAILURE);

        }

        // traverse tree to leaf node where position is located in octant
        while (!(*node).is_leaf) {
                
                long int c_id = 0;
                if (x[DIM * i + 0] > (*node).bb_center[0]) c_id |= 1;
                if (x[DIM * i + 1] > (*node).bb_center[1]) c_id |= 2;
                if (x[DIM * i + 2] > (*node).bb_center[2]) c_id |= 4;

                if ((*node).next[c_id] == NULL) {

                        struct nbody_bh_node* next = nbody_bh_node_new();

                        (*next).bb_size = (*node).bb_size / 2.00f;
                        for (int j = 0; j < DIM; j++) {
                                
                                const float offs = 0.5 * (*next).bb_size *
                                                   ((c_id & (1 << j)) ? 1:-1);

                                (*next).bb_center[0] = (*tree).bb_center[0] 
                                                     + offs;

                        }

                        (*next).is_leaf = 1;
                        (*next).p_id = -1;
                        (*next).parent = node;

                        (*node).next[c_id] = next;

                }

                node = (*node).next[c_id];

        }
        
        // insert if leaf is empty
        if ((*node).p_id == -1) {

                (*node).cm[0] = x[DIM * i + 0];
                (*node).cm[1] = x[DIM * i + 1];
                (*node).cm[2] = x[DIM * i + 2];

                (*node).m = m[i];
                return;

        }
        
        // add mass if position is the same
        float tol = 1e-6;
        if (x[DIM * (*node).p_id + 0] - x[DIM * i + 0] < tol &&
            x[DIM * (*node).p_id + 1] - x[DIM * i + 1] < tol &&
            x[DIM * (*node).p_id + 2] - x[DIM * i + 2] < tol) {

                (*node).m += m[i];

        }

        // subdivide until two points are no longer in the same node and then
        // set position and mass
        while (1) {
        
        // subdivision
        for (int c = 0; c < NBODY_TREE_CHILD_MAX; c++) {
                
                struct nbody_bh_node* next = nbody_bh_node_new();

                next->bb_size = (*node).bb_size / 2.0f;
                (*next).bb_size = (*node).bb_size / 2.00f;
                for (int j = 0; j < DIM; j++) {
                        
                        const float offs = 0.5 * (*next).bb_size *
                                           ((c & (1 << j)) ? 1:-1);

                        (*next).bb_center[0] = (*tree).bb_center[0] + offs;

                }

                (*next).is_leaf = 1;
                (*next).p_id = -1;
                (*next).parent = node;

                (*node).next[c] = next;

        }

        long int c_id_old = 0;
        for (int j = 0; j < DIM; j++) {
                if (x[DIM * (*node).p_id + j] > (*node).bb_center[j]) {

                          c_id_old |= (1 << j);
                }
        }

        struct nbody_bh_node* next_old = (*node).next[c_id_old];
        next_old->p_id = (*node).p_id;
        next_old->m = (*node).m;
        for (int j = 0; j < DIM; j++) {
                next_old->cm[j] = x[DIM * (*node).p_id + j];
        }

        // TODO : WARNING : I am sure this is not correct
        (*node).p_id = -1;
        (*node).m = 0;

        long int c_id_new = 0;
        for (int j = 0; j < DIM; j++) {
                if (x[DIM * i + j] > (*node).bb_center[j]) {
                        c_id_new |= (1 << j);
                }
        }

        if (c_id_new == c_id_old) {
                break;
        }

        struct nbody_bh_node* next_new = (*node).next[c_id_new];
        next_new->p_id = (*node).p_id;
        next_new->m = m[i];
        for (int j = 0; j < DIM; j++) {
                next_new->cm[j] = x[DIM * i + j];
        }

        } // while (1)
        
}

struct nbody_bh_node*
nbody_bh_tree_build(const float* const restrict x,
                    const float* const restrict m,
                    const long int N,
                    const float bb_x_min,
                    const float bb_x_max
                    ) {

        struct nbody_bh_node* tree = nbody_bh_tree_new(bb_x_min, bb_x_max);

        for (int i = 0; i < NBODY_TREE_CHILD_MAX; i++) {

                (*tree).next[i] = NULL;
                
        }
        
        for (long int i = 0; i < N; i++) {

                nbody_bh_tree_insert(tree, x, m, i); 

        }
          
        return tree;

}
struct nbody_bh_node*
nbody_bh_tree_traverse(struct nbody_bh_node* tree, 
                       const float* const restrict x,
                       const long int i) {

        if (tree == NULL) {
                perror("tree parameter NULL");
                return NULL;
        }

        struct nbody_bh_node* node = tree;

        while (!node->is_leaf) {

                long int c_id = 0;
                if (x[DIM * i + 0] > node->bb_center[0]) c_id |= 1;
                if (x[DIM * i + 1] > node->bb_center[1]) c_id |= 2;
                if (x[DIM * i + 2] > node->bb_center[2]) c_id |= 4;

                if (node->next[c_id] == NULL) {
                        return NULL;
                }

                node = node->next[c_id];
        }

        if (node->p_id == i) {
                return node;
        }

        return NULL;
}

struct nbody_bh_node*
nbody_bh_tree_delete(struct nbody_bh_node* tree) {

        if (tree == NULL) {
                return NULL;
        }

        for (int i = 0; i < NBODY_TREE_CHILD_MAX; i++) {
                if (tree->next[i] != NULL) {
                        nbody_bh_tree_delete(tree->next[i]);
                }
        }

        free(tree);

        return NULL;
}

