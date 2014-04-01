std::asymmetric_coroutine<int>::push_type sink(
    [&](std::asymmetric_coroutine<int>::pull_type& source){
        while(source){
            std::cout << source.get() <<  " ";
            source();
        }
    });

std::vector<int> v{1,1,2,3,5,8,13,21,34,55};
std::copy(std::begin(v),std::end(v),std::begin(sink));
