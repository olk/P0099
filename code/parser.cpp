// grammar:
//   P ---> E '\0'
//   E ---> T {('+'|'-') T}
//   T ---> S {('*'|'/') S}
//   S ---> digit | '(' E ')'
class Parser{
   int level;
   char next;
   istream& is;
   function<void(char)> cb;

   char pull(){
        return char_traits<char>::to_char_type(is.get());
   }

   void scan(){
       do{
           next=pull();
       }
       while(isspace(next));
   }

public:
   Parser(istream& is_,function<void(char)> cb_) :
      level(0),next(),is(is_),cb(cb_)
    {}

   void run() {
      scan();
      E();
   }

private:
   void E(){
      T();
      while (next=='+'||next=='-'){
         cb(next); // callback; signal new symbol
         scan();
         T();
      }
   }

   void T(){
      S();
      while (next=='*'||next=='/'){
         cb(next); // callback; signal new symbol
         scan();
         S();
      }
   }

   void S(){
      if (isdigit(next)){
         cb(next); // callback; signal new symbol
         scan();
      }
      else if(next=='('){
         cb(next); // callback; signal new symbol
         scan();
         E();
         if (next==')'){
             cb(next); // callback; signal new symbol
             scan();
         }else{
             throw std::runtime_error("parsing failed");
         }
      }
      else{
          throw std::runtime_error("parsing failed");
      }
   }
};

int main(){
    std::istringstream is("1+1");
    bool done=false;
    char c;
    std::exception_ptr except;
    // access current execution context
    auto m=std::execution_context::current();
    // use of linked stack (grows on demand) with initial size of 1KB
    std::execution_context l(
    auto l=[&is,&m,&done,&except,&c]()resumable(segmented(1024)){
            Parser p(is,
                     // callback, used to signal new symbol
                     [&m,&c](char ch){
                        c=ch;
                        m(); // resume main-context
                     });
            try{
                p.run(); // start parsing
            }catch(...){
                // store other exceptions in exception-pointer
                except=std::current_exception();
            }
            done=true; // signal termination
            m(); // resume main-context
        });
    try{
        // inversion of control: user-code pulls parsed data from parser
        l(); // resume parser-context
        if(except){
            std::rethrow_exception(except);
        }
        while(!done){
            std::cout<<"Parsed: "<<c<<std::endl;
            l(); // resume parser-context
            if(except){
                std::rethrow_exception(except);
            }
        }
    }catch(const std::exception& e){
        std::cerr<<"exception: "<<e.what()<<std::endl;
    }
}
