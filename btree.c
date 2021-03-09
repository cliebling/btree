#include "btree.h"

struct leaf *create_leaf(void)
{
        struct leaf *leaf;
        leaf = malloc(sizeof(struct leaf));
        if(leaf == NULL){
                return NULL;
        }
        leaf->parent = NULL;
        leaf->left = NULL;
        leaf->right = NULL;
        leaf->data = NULL;
        return leaf;
}

struct tree *create_tree(void)
{
        struct tree *tree;
        struct leaf *leaf;
        tree = malloc(sizeof(struct tree));
        if(tree == NULL){ 
                return NULL;
        }
        leaf = malloc(sizeof(struct leaf));
        if(leaf == NULL){
                free((void*)tree);
                return NULL;
        }
        tree->root = (void*)leaf;
        leaf->parent = NULL;
        leaf->left = NULL;
        leaf->right = NULL;
        return tree;
}

void defoliate(struct leaf *leaf)
{
        if(leaf->left != NULL)
                defoliate((struct leaf*)leaf->left);
        if(leaf->right != NULL)
                defoliate((struct leaf*)leaf->right);
        free((void*)leaf);
}

int32_t delete_tree(struct tree *tree)
{
        struct leaf *leaf;
        if(tree == NULL){
                return -1;
        }
        defoliate((struct leaf*)tree->root);
        free((void*)tree);
        return 0;
}

        

int32_t add_child(struct leaf *leaf, uint8_t direction)
{
        struct leaf *new_leaf;
        if(leaf == NULL){
                return -1;
        }
        new_leaf = create_leaf();
        if(new_leaf == NULL){
                return -1;
        }
        switch(direction){
                case LEFT:
                        if(leaf->left != NULL){
                                return -1;
                        }
                        new_leaf->parent = (void*)leaf;
                        leaf->left = (void*)new_leaf;
                        break;
                case RIGHT:
                        if(leaf->right != NULL){
                                return -1;
                        }
                        new_leaf->parent = (void*)leaf;
                        leaf->right = (void*)new_leaf;
                        break;
                default: /* place in first open */
                        if(leaf->left != NULL){
                                if(leaf->right != NULL){
                                        return -1;
                                } else {
                                        new_leaf->parent = (void*)leaf;
                                        leaf->right = (void*)new_leaf;
                                }
                        } else {
                                new_leaf->parent = (void*)leaf;
                                leaf->right = (void*)new_leaf;
                        }
                        break;
        }
        return 0;
}



int32_t insert_parent(struct leaf *leaf)
{
        struct leaf *new_leaf;
        struct leaf *old_parent;
        if(leaf == NULL){
                return -1;
        }
        new_leaf = malloc(sizeof(struct leaf));
        if(new_leaf == NULL){
                return -1;
        }
        /* special case of a new root */
        if(leaf->parent == NULL){
                leaf->parent = (void*)new_leaf;
                new_leaf->left = (void*)leaf;
                new_leaf->parent = NULL;
                return -1;
        }
        
        old_parent = (struct leaf*)leaf->parent;
        new_leaf->parent = (void*)old_parent;
        leaf->parent = (void*)new_leaf;
        if(old_parent->left == leaf){ /* We're left node, make new node left */
                new_leaf->left = (void*)leaf;
        } else {
                new_leaf->right = (void*)leaf;
        }
        return 0;
}

int32_t swap_children(struct leaf *leaf)
{
        if(leaf == NULL){
                return -1;
        }
        leaf->right = (void*)((uint64_t)leaf->right ^ (uint64_t)leaf->left);
        leaf->left = (void*)((uint64_t)leaf-> right ^ (uint64_t)leaf->left);
        leaf->right = (void*)((uint64_t)leaf->right ^ (uint64_t)leaf->left);
        return 0;
}

int32_t delete_child(struct leaf *leaf)
{
	/* Not yet implemented */
	return -1;
}

