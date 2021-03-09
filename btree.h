/*
 * Copyright (C) 2020 Charles R. Liebling
 *
 * btree.c
 * This implements a small binary tree library.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */ 
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
