#include "Product.h"

int Product::order(int cnt) {
    if(p_count >= cnt) {
        p_count -= cnt;
        return cnt;
    } 
    return 0;
} 