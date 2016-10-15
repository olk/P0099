std::execution_context<void> ctx1([](std::execution_context<void>&& ctx2){
            std::cout << "inside ctx1" << std::endl;
            return std::move(ctx2);
        });
ctx1();

output:
    inside ctx1
