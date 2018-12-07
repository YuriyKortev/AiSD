
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define TABLE_HAT1 "adding\n========================================\n||  i  || узел   ||   iter  ||  nsec  ||\n========================================\n"
#define TABLE_HAT2 "deleting\n========================================\n||  i  || узел   ||   iter  ||  nsec  ||\n========================================\n"
#define TABLE1 "========================================\n"
#define TABLE2 "||% 5d||% 5d   || % 5d   ||% 5d   ||\n"
#define f_rec "../rbt_rec.txt"
#define f_iter "../rbe_iter.txt"
#define fworst_rec "../rbt_worst_rec.txt"
#define fworst_iter "../rbt_worst_iter.txt"

typedef struct node{
    int key;
    struct node* left;
    struct node* right;
}Rbt;

void swap(int* ,int* );
void free_rbt(Rbt* );
int height(Rbt* );
void add_iter(Rbt** , int ,int*);
void add_rec(Rbt** ,int ,int* );
void delete_iter(Rbt** ,int ,int* );
void delete_rec(Rbt** , int ,int* );
