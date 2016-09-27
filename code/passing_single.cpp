std::execution_context<int> ctx1([](std::execution_context<int> ctx2,int j){
            std::printf("inside ctx1,j==%d\n",j);
            std::tie(ctx2,j)=ctx2(j+1);
            return ctx2;
        });
int i=1;
std::tie(ctx1,i)=ctx1(i);
std::printf("i==%d\n",i);

output:
    inside ctx1,j==1
    i==2
