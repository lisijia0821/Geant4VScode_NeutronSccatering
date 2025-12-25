#ifndef N3RunAction_h
#define N3RunAction_h

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <iostream>

namespace N3{

class RunAction : public G4UserRunAction{
    public:
    RunAction();
    ~RunAction() override = default;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

    // 提供给EventAction的接口
    void RecordWholeData(G4double x, G4double y, G4double energy);
    void RecordNeutronData(G4double x, G4double y, G4double energy);
    
    private:
    
    std::vector<G4double> fx;
    std::vector<G4double> fy;
    std::vector<G4double> fenergy;

    std::vector<G4double> fx_neutron;
    std::vector<G4double> fy_neutron;
    std::vector<G4double> fenergy_neutron;

    // std::vector<G4double> fneutronEnergy;

    G4String fOutputFile;
    G4String fOutputFile_neutron;

};


}



#endif