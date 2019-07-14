#include <iostream>
#include <thread>
#include "effective_cpp/item35/item35.h"
#include "effective_modern_cpp/chapter06.h"

void hello(){
  std::cout<<"Hello Concurrent World"<<std::endl;
}

int main(int argc, char* argv[]){

  // item35::init();
  EffectiveModernChapter06::init();
	return 0;
}
