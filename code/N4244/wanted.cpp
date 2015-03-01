auto f3=[]()resumable{   
    yield from  f1(); 
    yield from  f2(); 
};  

int main(){
    f3(); // primes the resumable lambda    
    for(int i=0;i<4;++i){   
        *f3.wanted<int>()=i;    
        f3(); 
    }
}
