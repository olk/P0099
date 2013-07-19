std::coroutine<int>::push_type c(
    [&](std::coroutine<int>::pull_type& c){
        while(c){
            std::cout << c.get() <<  " ";
            c();
        }
    });

std::vector<int> v{1,1,2,3,5,8,13,21,34,55};
std::copy(std::begin(v),std::end(v),std::begin(c));
