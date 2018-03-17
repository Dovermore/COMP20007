/*****************************************************************************
 *Author   : Calvin Huang
 *Licence  : None
 *File Name: Top_k_selection_with_cmp.c
 
 *This program is created for the purpose of:
    
 *It's not supposed to be shared without permission of author.
 ****************************************************************************/
#include <stdlib.h>

/*                        <Reused code from p10067>            By  Calvin.H  */
/******************************************************************************
P10067 k selection slight modification.
    Note: It will be better off just using normal linear search instead of top
    k selection, I'm simply testing the reusability of the code from p10067 
******************************************************************************/

/*
This function computes a random integer between [lo, hi)
 */
int random_selection(int lo, int hi) {
    if (hi == lo) {
        return lo;
    }
    int r = lo + rand() % (hi - lo);
    return r;
}


/*
Swap the value of two integers a and b
*/
void swap_int(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


/*
The partition
ary: The array to be partitioned
val: The value selected as the axis (Not index)
left: The left most elements of array to be partitioned
right: The left most elements of array to be partitioned
btm: returning the the index to the first value equal to val after partition
top: returning the the index to the first value larger to val after partition
cmp: comparison function pointer with two int inputs, 
        return negative value if a < b, 
            0 if a==b, positive value if a > b
[oth..., lo1, lo2, lo3...., loi, eq1, eq2, ... eqj, hi1, hi2,.... hik,othk+1..]
          ^                       ^                  ^             ^
          |                       |                  |             |
         left                    btm                top          right
 */
void partition(int *ary, int val, int left, int right, int* btm,
               int* top, (*cmp)(int*, int*)) {
    int lo = left,   /* Index of the first value equal to val
                        in the sorted part */
                     /* ###There is a potential bug here, since at first the
                        first element is assumed to be equal to val ###*/
        hi = right,  /* Index - 1 of the first larger value 
                        in the sorted array(i.e.this is not sorted yet)  */
        cur = left;  /* The current unsearched 
                        index(i.e. This is not sorted) */

    /* While the unsorted index is still less than the sorted part */
    while (cur <= hi) {
        if (cmp(ary+cur, &val) > 0) {
            swap_int(ary+cur, ary+hi);
            hi--;
        } else if (cmp(ary+cur, &val) == 0) {
            cur++;
        } else {
            swap_int(ary+lo, ary+cur);
            cur++;
            lo++;
        }
    }
    *btm = lo;
    *top = cur;
}



/*
Return the top_k *index* of an array
ary: pointer to the array
n:   length of the array (1 based)
k:   The k-th value needed (1 baesd)
cmp: function pointer that return negative value if a < b, 
                        0 if a==b, positive value if a > b
 */
int top_k_selection(int *ary, int n, int k, (*cmp)(int*, int*)) {
    int k_lo = 0,
        k_hi = 0,
        left = 0,
        right = n - 1,
        ind = 0,
        val = 0;
    /* k is 1 based index and k_hi is 0 based index, for example,
       if k == 5, then the element with ary[k - 1] (4) must be in the range,
       since k_hi does not include the k_hi value in it, so the relation must
       be k_lo <= k - 1 <= k_hi - 1. E.g. 4 <= 5 - 1 <= 5 - 1 */
    while (!(k_lo <= k - 1 && k <= k_hi)) {
        if (k < k_lo + 1) {
            right = k_lo - 1;
        } else {
            left = k_hi;
        }
        ind = random_selection(left, right);
        val = ary[ind];
        partition(ary, val, left, right, &k_lo, &k_hi, cmp);
    }
    return k - 1;
}
/*                       </Reused code from p10067>            By  Calvin.H  */