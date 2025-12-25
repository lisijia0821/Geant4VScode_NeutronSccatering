#include "03NRunAction.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>

namespace N3{

RunAction::RunAction(){
    fOutputFile = "whole_exit_data.csv";
    fOutputFile_neutron = "neutron_exit_data.csv";
}

void RunAction::BeginOfRunAction(const G4Run*){
    fx.clear();
    fy.clear();
    fenergy.clear();

    fx_neutron.clear();
    fy_neutron.clear();
    fenergy_neutron.clear();
    
    
}

void RunAction::EndOfRunAction(const G4Run*){ 

    std::ofstream ofs1(fOutputFile);
    ofs1<<"x(mm),y(mm),energy(eV)\n";
        for (size_t i = 0; i < fx.size(); i++) {
        ofs1 << fx[i] / mm << ","
            << fy[i] / mm << ","
            << fenergy[i] / eV << "\n";
    }

    ofs1.close();

    G4cout << "===== Neutron Data Saved to: " << fOutputFile << " =====" << G4endl;
    G4cout << "Total recorded : " << fx.size() << G4endl;

    //写中子的
    std::ofstream ofs2(fOutputFile_neutron);
    ofs2<<"x(mm),y(mm),energy(eV)\n";
    G4cerr<<"size:"<<fx_neutron.size()<<G4endl;
        for (size_t i = 0; i < fx_neutron.size(); i++) {
        ofs2 << fx_neutron[i] / mm << ","
            << fy_neutron[i] / mm << ","
            << fenergy_neutron[i] / eV << "\n";
    }

    ofs2.close();

    G4cout << "===== Neutron Data Saved to: " << fOutputFile_neutron << " =====" << G4endl;
    G4cout << "Total recorded neutrons: " << fx_neutron.size() << G4endl;

}

void RunAction::RecordWholeData(G4double x, G4double y, G4double energy){
    fx.push_back(x);
    fy.push_back(y);
    fenergy.push_back(energy);
}

void RunAction::RecordNeutronData(G4double x, G4double y, G4double energy){

    fx_neutron.push_back(x);
    fy_neutron.push_back(y);
    fenergy_neutron.push_back(energy);
}
}
