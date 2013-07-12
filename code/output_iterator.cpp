std::coroutine<int>::pull_type c(
    [&](std::coroutine<int>::push_type& c){
        int first=1,second=1;
        for (int i=0;i<10;++i){
            int third=first+second;
            first=second;
            second=third;
            c(third);
        }
    });

for (auto i:c)
    std::cout << i << " ";
