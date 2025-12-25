#ifndef EventAction_h
#define EventAction_h

#include "G4UserEventAction.hh"
#include "03NRunAction.hh"


namespace N3{

class RunAction;

class EventAction: public G4UserEventAction{

    public:
    EventAction(RunAction* runAction);
    ~EventAction() override = default;
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    //给 steppingAction 的接口
    void RecordWholeHit(G4double x, G4double y, G4double energy);
    void RecordNeutronHit(G4double x, G4double y, G4double energy);

    G4bool HasHit_whole() const {return fHasHit_whole;};
    G4bool HasHit_neutron() const {return fHasHit_neutron;};
    void SetHasHit_whole(G4bool v = true) { fHasHit_whole = v; }
    void SetHasHit_neutron(G4bool v = true) { fHasHit_neutron = v; }

    private:

    RunAction* fRunAction;

    G4double fx;
    G4double fy;
    G4double fe;

    G4double fx_neutron;
    G4double fy_neutron;
    G4double fe_neutron;
    G4bool fHasHit_whole;
    G4bool fHasHit_neutron;
};

}



#endif