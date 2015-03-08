int main(){
    std::istringstream is("1+1");
    bool done=false;
    char c;
    // access current execution context
    auto m=std::execution_context::current();
    // construct with 'resumable lambda'-like syntax
    // segmented stack grows on demand, initial size 1KB
    auto l=[&is,&m,&done,&c]()resumable(segmented(1024)){
               Parser p(is,
                        // callback, invoked by the parser
                        [&m,&c](char ch){
                           c=ch;
                           // resume main-context
                           m();
                        });
               // start parsing
               p.run();
               // signal termination
               done=true;
           };
    // inversion of control: user-code pulls parsed data from parser
    while(!done){
        // resume parser-context
        l();
        std::cout<<"Parsed: "<<c<<std::endl;
    }
}
