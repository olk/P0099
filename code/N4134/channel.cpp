// N4402: stackless resumable function
goroutine pusher(channel<int>& left, channel<int>& right){
    for(;;){
        auto val=await left.pull();
        await right.push(val+1);
    }
}

static const int N = 1000*1000;
std::vector<channel<int>> c(N+1);
for(int i=0;i<N;++i){
    goroutine::go(pusher(c[i],c[i+1]));
}
