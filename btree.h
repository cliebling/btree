#ifndef __BTREE_H
#define __BTREE_H
#include <stdlib.h>
#include <stdint.h>

enum direction {
        LEFT = 0,
        RIGHT = 1,
};

struct leaf {
        void *parent;
        void *left;
        void *right;
        void *data;
};

struct tree {
        struct leaf *root;
};

struct tree* create_tree(void);
int32_t delete_tree(struct tree *tree);
int32_t add_child(struct leaf *leaf, uint8_t direction);
int32_t insert_parent(struct leaf *leaf);
int32_t swap_children(struct leaf *leaf);
int32_t delete_child(struct leaf *leaf);
#endif /*__BTREE_H */
