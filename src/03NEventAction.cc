#include "03NEventAction.hh"

namespace N3{

EventAction::EventAction(RunAction* runAction)
: fRunAction(runAction),
  fe(0.0),      //初始化每一个fe
  fx(0.0),
  fy(0.0),
  fx_neutron(0.0),
  fy_neutron(0.0),
  fe_neutron(0.0),
  fHasHit_whole(false),
  fHasHit_neutron(false)
  {}

void EventAction::BeginOfEventAction(const G4Event*){

    fe = 0.0;   //每一个event发射之前先将位置能量归零
    fx = 0.0;
    fy = 0.0;
    fx_neutron = 0.0;
    fy_neutron = 0.0;
    fe_neutron = 0.0;
    fHasHit_whole = false;
    fHasHit_neutron = false;

}

// 这个接口是给SteppingAction的
void EventAction::RecordWholeHit(G4double x, G4double y, G4double energy){
    // 如果非真的话，表明粒子始终没有进入到我认为正确的区域，所以一直不统计，
    // 然后再把hit认为是真的，如果粒子始终没有进入到正确区域，那么if条件就会仅仅运行一遍
    // 如果真了
    // fHasHit_whole = true;
    if(fHasHit_whole){
        fx = x;
        fy = y;
        fe = energy;
    }
};

void EventAction::RecordNeutronHit(G4double x, G4double y, G4double energy){
    // 如果非真的话，表明粒子始终没有进入到我认为正确的区域，所以一直不统计，
    // 然后再把hit认为是真的，如果粒子始终没有进入到正确区域，那么if条件就会仅仅运行一遍
    // 如果真了
    if(fHasHit_neutron){
        fx_neutron = x;
        fy_neutron = y;
        fe_neutron = energy;
    }
};


void EventAction::EndOfEventAction(const G4Event*){
    //应该是如果hasHit是在中子中那就只是RecordNeutron，如果是所有粒子，那就recordWhole
    if(fHasHit_whole){
        fRunAction->RecordWholeData(fx,fy,fe);
    }
    if(fHasHit_neutron){
        fRunAction->RecordNeutronData(fx_neutron,fy_neutron,fe_neutron);
    }
}



}