int main(){
    std::istringstream is("1+1");
    bool done=false;
    char c;
    // access current execution context
    auto m=std::execution_context::current();
    // construct from stackful resumable lambda
    // segmented stack grows on demand, initial size 1KB
    auto l=[&is,&m,&done,&c]()resumable(segmented(1024)){
               Parser p(is,
                        // create/pass callback, invoked by the parser
                        [&m,&c](char ch){
                           c=ch;
                           // resume main-context
                           m();
                        });
               p.run();
               done=true;
           };
    // inversion of control: user-code pulls parsed data from parser
    while(!done){
        // resume parser-context
        l();
        printf("Parsed: %c\n",c);
    }
}
