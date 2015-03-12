int main(){
    auto f=[]()resumable{
        int n=yield(int);   
        std::cout<<"received="<<n<<"\n";
        std::string s=yield(std::string);
        std::cout<<"received="<<s<<"\n";
    };

    *f.wanted<int>()=1; // assign parameter
    f(); // context switch
    *f.wanted<std::string>()=s"abc"; // assign parameter
    f(); // context switch
}