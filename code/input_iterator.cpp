int j=10;
std::coroutine<int>::pull_type c(
    [&](std::coroutine<int>::push_type& c){
        for(int i=0;i<j;++i){
            c(i);
        }
    });

auto e(std::end(c));
for(auto i(std::begin(c));i!=e;++i){
    std::cout << *i <<  " ";
}
