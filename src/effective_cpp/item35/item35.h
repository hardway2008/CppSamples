#pragma once
#include <functional>
#include <iostream>
#include <string>

namespace item35{

    class GameCharacter{
        virtual int healthValue() const; 
    };

    class GameCharacter2{
    public:
        typedef std::function<int (const GameCharacter2&)> HealthCalcFunc;

    private:
        HealthCalcFunc health_func_;
    };

    //the design based on interface:
    //interface implement
    class Penguin{
    public:
        Penguin(const std::string name){
            name_ = name;
        }
        void run(){
            std::cout << name_ << std::endl;
            std::cout << "Penguin run!" << std::endl;
        }
        void swim(){
            std::cout << "Penguin swim!" << std::endl;
        }
        std::string Name(){
            return name_;
        }
    private:
        std::string name_;
    };

    class Sparrow{
    public:
        void run(){
            std::cout << "Sparrow run!" << std::endl;
        }
        void fly(){
            std::cout << "Sparrow fly!" << std::endl;
        }
    };

    //define separate interface
    using FlyCallback = std::function<void()>;
    using RunCallback = std::function<void()>;
    using SwimCallback = std::function<void()>;

    //application: interface user
    class Foo{
    public:
        Foo(FlyCallback fly, RunCallback run): fly_cb_(fly), run_cb_(run){

        }
        void SwitchImplment(FlyCallback fly, RunCallback run){
            fly_cb_ = fly;
            run_cb_ = run;
        }
        void FooFly(){
            fly_cb_();
        }
        void FooRun(){
            run_cb_();
        }        
    private:
        FlyCallback fly_cb_;
        RunCallback run_cb_;
    };

    class Bar{
    public:
        Bar(RunCallback run, SwimCallback swim):run_cb_(run), swim_cb_(swim){

        }
        void SwitchImplment(SwimCallback swim, RunCallback run){
            swim_cb_ = swim;
            run_cb_ = run;
        }
        void BarSwim(){
            swim_cb_();
        }
        void BarRun(){
            run_cb_();
        } 
    private:
        RunCallback run_cb_;
        SwimCallback swim_cb_;
    };

    void init();

}