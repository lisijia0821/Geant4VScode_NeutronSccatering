/// 这里的能量还需要继续改写，需要准确的函数来生成相应的能量谱

#include "03NPrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <algorithm>


namespace N3{
    PrimaryGeneratorAction ::PrimaryGeneratorAction(){
        fParticleGun = new G4ParticleGun(1);

        G4ParticleDefinition* particletype = G4ParticleTable::GetParticleTable()
                                                        ->FindParticle("neutron");

        //设置粒子类型、方向，发射的位置为平面
        if (!particletype){
            G4cerr<<"Particle can't be found"<<G4endl;
        }else{
            G4cerr<<"Succesfully find particle"<<G4endl;
        }
        fParticleGun->SetParticleDefinition(particletype);
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
    };


    // 构造析构函数

    PrimaryGeneratorAction::~PrimaryGeneratorAction(){
        delete fParticleGun;
    };

    void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event){   
                //设置粒子的发射平面
        G4double x0 = 3.5*(G4UniformRand()-0.5)*cm;
        G4double y0 = 3.5*(G4UniformRand()-0.5)*cm;
        G4double z0 = -4*cm;

        // G4cerr<<"x:"<<x0/cm<<" y:"<<y0/cm<<G4endl;

        fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

        // //设置能量格点
        // energyGrid = {0.786, 4.637, 13.1, 18.56, 81.80, 327.2}; //这里的单位为meV,

        // spectrumPDF = {0.2, 0.8, 1.2, 1.6, 1.5, 1.2};

        // spectrumCDF.resize(spectrumPDF.size());                 //把CPF的元素设置的和PDF一致

        // //构建累积分布CDF
        // double sum = 0.0;
        // for(size_t i=0; i<spectrumPDF.size(); i++){
        //     sum += spectrumPDF[i];
        //     spectrumCDF[i] = sum;
        // }

        // //归一化，这里一定要用引用的格式，因为要对原始数据进行修改，否则修改的仅仅只是副本
        // for (double& v : spectrumCDF) v /= sum;          
        // double r = G4UniformRand();                             //生成一个[0,1)的随机数    

        // //it为不小于r的数，也就是在我的CDF中选一个数出来
        // auto it = std::lower_bound(spectrumCDF.begin(),spectrumCDF.end(),r);

        // //idx为一个整数，表示spectrumCDF.begin()与it之间的数值个数
        // size_t idx = std::distance(spectrumCDF.begin(),it);

        // //millielectronvolt是meV
        // fParticleGun->SetParticleEnergy(energyGrid[idx]*millielectronvolt);  
        fParticleGun->SetParticleEnergy(4.6*millielectronvolt);
        fParticleGun->GeneratePrimaryVertex(event);
    };

}