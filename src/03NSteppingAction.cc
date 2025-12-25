#include "03NSteppingAction.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4Neutron.hh"
#include "G4VProcess.hh"

/// 先分辨统计z>4的中子能量和所有能量，然后将中子能量加和，以及所有能量之和，看比例，如果其他的能量不是很多的

namespace N3{

SteppingAction::SteppingAction(EventAction* EventAction)
: fEventAction(EventAction),
  fx(0.0),
  fy(0.0),
  fenergy(0.0)
  {}

void SteppingAction::UserSteppingAction(const G4Step* step){

    G4Track* track = step->GetTrack();

    G4ParticleDefinition* particleDefinition = track->GetDefinition();

    G4double z_pre = step->GetPreStepPoint()->GetPosition().z();
    G4double z_post = step->GetPostStepPoint()->GetPosition().z();

    TrackInfo* info = static_cast<TrackInfo*>(track->GetUserInformation());
    if (!info) {
        info = new TrackInfo();
        track->SetUserInformation(info);
    }
        //如果粒子是中子
    if (particleDefinition == G4Neutron::Definition()){
        //G4cerr<<"neutron"<<G4endl;
        auto process = step -> GetPostStepPoint()->GetProcessDefinedStep();
        if (process && process->GetProcessName()!="Transportation"){
            info->SetCollided(); 
        }
    }

    if (z_pre < 4 * cm && z_post >= 4 * cm){

        fEventAction->SetHasHit_whole(true);
        // 记录所有的Z轴大于4cm的粒子的位置和能量
        G4double energy_MeV = step->GetPostStepPoint()->GetKineticEnergy();
        G4double energy_meV = energy_MeV * (1.0e9);
        G4ThreeVector pos = step ->GetPostStepPoint() -> GetPosition();

        G4double x = pos.x();
        G4double y = pos.y();

        fEventAction->RecordWholeHit(x, y,energy_meV);
        
        // 仅记录中子的
        if(particleDefinition == G4Neutron::Definition() && !info->HasCollided()){
            fEventAction->SetHasHit_neutron(true);
            fEventAction->RecordNeutronHit(x, y,energy_meV);
        }
        track->SetTrackStatus(fStopAndKill);
    }
    


}

}