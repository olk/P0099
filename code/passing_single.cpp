std::execution_context<int> ctx1([](std::execution_context<int> && ctx2,int j){
            std::cout << "inside ctx1,j==" << j << std::endl;
            std::tie(ctx2,j)=ctx2(j+1);
            return std::move(ctx2);
        });
int i=1;
std::tie(ctx1,i)=ctx1(i);
std::cout << "i==" << i << std::endl;

output:
    inside ctx1,j==1
    i==2
