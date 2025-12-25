#ifndef N3ActionIntialization_h
#define N3ActionIntialization_h

#include "G4VUserActionInitialization.hh"
#include "03NRunAction.hh"
#include "03NPrimaryGeneratorAction.hh"
#include "03NEventAction.hh"
#include "03NSteppingAction.hh"

namespace N3{

class RunAction;
class EventAction;
class SteppingAction;
class PrimaryGeneratorAction;

class ActionInitialization: public G4VUserActionInitialization{
    public:
    ActionInitialization()=default;
    ~ActionInitialization() override = default;

    void BuildForMaster() const override;
    void Build() const override;

};

}


#endif