std::vector<int> merge(const std::vector<int>& a,const std::vector<int>& b){
    std::vector<int> c;
    std::size_t idx_a=0,idx_b=0;
    std::symmetric_coroutine<void>::call_type* other_a=0,* other_b=0;

    std::symmetric_coroutine<void>::call_type coro_a(
        [&](std::symmetric_coroutine<void>::yield_type& yield){
            while(idx_a<a.size()){
                if(b[idx_b]<a[idx_a])    // element in b is less than in a
                    yield(*other_b);     // yield to coroutine coro_b
                c.push_back(a[idx_a++]); // add element to final array
            }
            // add remaining elements of array b
            while(idx_b<b.size())
                c.push_back(b[idx_b++]);
        });

    std::symmetric_coroutine<void>::call_type coro_b(
        [&](std::symmetric_coroutine<void>::yield_type& yield){
            while(idx_b<b.size()){
                if(a[idx_a]<b[idx_b])    // element in a is less than in b
                    yield(*other_a);     // yield to coroutine coro_a
                c.push_back(b[idx_b++]); // add element to final array
            }
            // add remaining elements of array a
            while(idx_a<a.size())
                c.push_back(a[idx_a++]);
        });


    other_a=&coro_a;
    other_b=&coro_b;

    coro_a(); // enter coroutine-fn of coro_a

    return c;
}

std::vector<int> a={1,5,6,10};
std::vector<int> b={2,4,7,8,9,13};
std::vector<int> c=merge(a,b);
print(a);
print(b);
print(c);

output:
    a : 1 5 6 10
    b : 2 4 7 8 9 13
    c : 1 2 4 5 6 7 8 9 10 13
