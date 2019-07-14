#include "chapter06.h"
#include <vector>
#include <functional>

namespace EffectiveModernChapter06{
        void init(){
            std::cout << "EffectiveModernChapter06" << std::endl;

            int x = 10;
            auto c1 = [x](int y){
                return x * y > 55;
            };
            auto c2 = c1;
            auto c3 = c2;
            
            using FilterContainer = std::vector<std::function<bool(int)>>;
            FilterContainer filters;

            
            filters.emplace_back([](int value){
                return value % 5 == 0;
            });

        }
}