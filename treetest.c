/*
 * Copyright (C) 2020 Charles R. Liebling
 *
 * treetest.c
 * This is a little test program for btree.c.
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
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "btree.h"

#define ARRAYLEN 320000U

void populate_tree(struct leaf *leaf, int32_t *value)
{
        if(leaf->data == NULL){
                return;
        }
        if(*(int32_t*)leaf->data > *value){
                if(leaf->left != NULL){
                        populate_tree((struct leaf*)leaf->left, value);
                } else {
                        add_child(leaf, LEFT);
                        ((struct leaf*)leaf->left)->data = (void*)value;
                        return;
                }
        } else if(*(int32_t*)leaf->data <= *value){
                if(leaf->right != NULL){
                        populate_tree((struct leaf*)leaf->right, value);
                } else {
                        add_child(leaf, RIGHT);
                        ((struct leaf*)leaf->right)->data = (void*)value;
                        return;
                }
        }
}

void print_tree(struct leaf *leaf)
{
        if(leaf->left == leaf->right){
                printf("Value: %d\n", *(int32_t*)leaf->data);
                return;
        }
        if(leaf->left != NULL){
                print_tree((struct leaf*)leaf->left);
        } 
        printf("Value: %d\n", *(int32_t*)leaf->data);
        if(leaf->right != NULL){
                print_tree((struct leaf*)leaf->right);
        }
        return;
}

int main(void)
{
        int32_t vars[ARRAYLEN];
        int32_t i;
        time_t t;
        struct tree *tree;
        struct leaf *leaf;
        tree = create_tree();
        srand(time(&t));
        for(i = 0; i < ARRAYLEN; i++){
                vars[i] = rand() % 10000;
        }
        leaf = (struct leaf*)tree->root;
        leaf->data = (void*)(&vars[0]);
        for(i = 1; i < ARRAYLEN; i++){
                populate_tree(leaf, &vars[i]);
        }
        getc(stdin);
        //print_tree(leaf);
        delete_tree(tree);
        return 0;
}


