int j=10;
std::asymmetric_coroutine<int>::pull_type source(
    [&](std::asymmetric_coroutine<int>::push_type& sink){
        for(int i=0;i<j;++i){
            sink(i);
        }
    });

auto e(std::end(source));
for(auto i(std::begin(source));i!=e;++i){
    std::cout << *i <<  " ";
}
