#include "item35.h"

namespace item35{

    // class GameCharacter{
    //     virtual int healthValue() const 
    // };

    void init(){
        Penguin p("a111");
        Sparrow s;
        Penguin p2("b222");

        //the argument of bind???
        Foo foo = Foo(std::bind(&Sparrow::fly, &s), std::bind(&Sparrow::run, &s));
        foo.FooFly();
        foo.FooRun();
        Bar bar = Bar(std::bind(&Penguin::run, &p), std::bind(&Penguin::run, &p));
        bar.BarRun();
        bar.BarSwim();
        bar.SwitchImplment(std::bind(&Penguin::run, &p2), std::bind(&Penguin::run, &p2));
        bar.BarRun();
        bar.BarSwim();
    }

}