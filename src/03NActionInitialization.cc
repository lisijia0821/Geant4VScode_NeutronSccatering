#include "03NActionInitializtion.hh"


namespace N3{

void ActionInitialization::BuildForMaster() const {

    RunAction* runAction = new RunAction();
    SetUserAction(runAction);
};

void ActionInitialization::Build() const{

    SetUserAction(new PrimaryGeneratorAction);      //实例化的时候需要头文件包含,在申明中包含了也足够
    RunAction* runAction = new RunAction();
    SetUserAction(runAction);

    EventAction* eventAction = new EventAction(runAction);
    SetUserAction(eventAction);

    SteppingAction* steppingAction = new SteppingAction(eventAction);
    SetUserAction(steppingAction);

}

}

