std::pull_coroutine<std::tuple<int,int>> c(
    [&](std::push_coroutine<std::tuple<int,int>> & c){
        c(std::make_tuple(7,11)); // return tuple {7,11}
    });

int x,y;
std::tie(x,y)=c.get();
