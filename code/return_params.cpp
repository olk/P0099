std::coroutine<std::tuple<int,int>>::pull_type c(
    [&](std::coroutine<std::tuple<int,int>>::push_type& c){
        c(std::make_tuple(7,11)); // return tuple {7,11}
    });

int x,y;
std::tie(x,y)=c.get();
