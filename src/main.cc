#include <iostream>
#include <thread>

void hello(){
  std::cout<<"Hello Concurrent World"<<std::endl;
}

int main(int argc, char* argv[]){
  std::thread t(hello);
  t.join();
	std::cout<< "Hello world!-------"<<std::endl;
	return 0;
}
