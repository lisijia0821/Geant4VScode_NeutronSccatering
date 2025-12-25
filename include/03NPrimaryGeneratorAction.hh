


#ifndef N3PrimaryGeneratorAction_h
#define N3PrimaryGeneratorAction_h

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"


#include "globals.hh"
#include <iostream>
class G4Event;                                       //因为这个向前声明本身就是全局的

namespace N3{

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction{
    public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction () override;

    void GeneratePrimaries(G4Event* event) override; //这里是设置首发粒子的各项参数，而不是实际的发射粒子

    private:
    G4ParticleGun* fParticleGun;

    std::vector<G4double> energyGrid;                //能量点
    std::vector<G4double> spectrumPDF;               //概率分布
    std::vector<G4double> spectrumCDF;

};
}




#endif