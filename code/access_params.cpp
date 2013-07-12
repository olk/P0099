std::coroutine<std::tuple<int,int>>::push_type c(
    [&](std::coroutine<std::tuple<int,int>>::pull_type& c){
        // access tuple {7,11}; x==7 y==1
        int x,y;
        std::tie(x,y)=c.get();
    });

c(std::make_tuple(7,11));
