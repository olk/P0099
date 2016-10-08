std::execution_context<int,int> ctx1(
        [](std::execution_context<int,int> && ctx2,int i,int j){
            std::printf("inside ctx1,i==%d j==%d\n",i,j);
            std::tie(ctx2,i,j)=ctx2(i+j,i-j);
            return std::move(ctx2);
        });
int i=2,j=1;
std::tie(ctx1,i,j)=ctx1(i,j);
std::printf("i==%d j==%d\n",i,j);

output:
    inside ctx1,i==2 j==1
    i==3 j==1
