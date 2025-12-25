#ifndef N3SteppingAction_h
#define N3SteppingAction_h

#include "G4UserSteppingAction.hh"
#include "03NEventAction.hh"
#include "03NTrackInformation.hh"
#include "G4Step.hh"

namespace N3
{

class EventAction;

class SteppingAction : public G4UserSteppingAction{
    public:
    SteppingAction(EventAction* EventAction);
    ~SteppingAction() override = default;

    void UserSteppingAction(const G4Step*) override;

    private:
    
    EventAction* fEventAction;
    G4double fx;
    G4double fy;
    G4double fenergy;

};



} // namespace name




#endif