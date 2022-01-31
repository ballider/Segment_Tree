// segment tree for count min on segment
#include <iostream>
#include <vector>

struct Node{
    int64_t min;    // min on segment 
    int64_t count;  // count element, which is equal to min on segment

    Node(int64_t m, int64_t c): min(m), count(c) {};
};

struct segment_tree{
    int64_t size;
    std::vector<Node> tree;

    void init(const int64_t n){
        size = 1;
        while( size < n ) size *= 2;
        tree.assign(2*size-1, {INT64_MAX, 0});
    }

    void set(const int64_t i, const int64_t v){
        set(i, v, 0, 0, size);
    }

    void set(const int64_t i, const int64_t v, int64_t x, int64_t left, int64_t right){
        if(right-left == 1){
            tree[x].min = v;
            tree[x].count = 1;
            return;
        }

        int64_t m = (left+right)/2;
        if( i < m ) set(i, v, 2*x+1, left, m);
        else set(i, v, 2*x+2, m, right);
        
        if( tree[2*x+1].min < tree[2*x+2].min ){
            tree[x].min = tree[2*x+1].min;
            tree[x].count = tree[2*x+1].count;
        }
        else if( tree[2*x+1].min > tree[2*x+2].min ){
            tree[x].min = tree[2*x+2].min;
            tree[x].count = tree[2*x+2].count;
        }
        else if ( tree[2*x+1].min == tree[2*x+2].min ){
            tree[x].min = tree[2*x+2].min;
            tree[x].count = tree[2*x+1].count + tree[2*x+2].count;
        }
    }

    Node count_min(const int64_t l, const int64_t r){
        return count_min(l, r, 0, 0, size);
    }

    Node count_min(const int64_t L, const int64_t R, int64_t x, int64_t left, int64_t right){
        if(L >= right || R <= left) return {INT64_MAX, 0};
        if(L <= left && R >= right) return tree[x];

        int64_t m = (right+left)/2;
        Node n1 = count_min(L, R, 2*x+1, left, m);
        Node n2 = count_min(L, R, 2*x+2, m, right);
        
        if(n1.min < n2.min) return n1;
        if(n1.min > n2.min) return n2;
        if(n1.min == n2.min) return {n1.min, n1.count+n2.count};
    }

    void print(){
        for(auto it : tree){
            std::cout << "(" << it.min << " " << it.count << ")";
        }
        std::cout << std::endl;
    }
};

int main(){
    int64_t n, m; std::cin >> n >> m;
    segment_tree T; T.init(n);

    for(int64_t i = 0; i < n; i++){
        int64_t x; std::cin >> x;
        T.set(i, x);
    }

    for(int64_t _ = 0; _ < m; _++){
        int64_t a, b, c; std::cin >> a >> b >> c;
        if(a == 1) T.set(b, c);
        if(a == 2){
            Node ans = T.count_min(b, c);
            std::cout << ans.min << " " << ans.count << std::endl;
        }
    }


    return 0;
}
