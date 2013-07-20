std::coroutine<int>::push_type c( // constructor does NOT enter coroutine-function
    [&](std::coroutine<int>::pull_type& c){
        for (int i: c) {
            std::cout << i <<  " ";
        }
    });

std::vector<int> v{1,1,2,3,5,8,13,21,34,55};
for( int i:v){
    c(i); // push {i} to coroutine-function
}
