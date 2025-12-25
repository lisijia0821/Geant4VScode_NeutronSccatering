#include "03NDetectorConstruction.hh"
#include "03NPrimaryGeneratorAction.hh"
#include "03NRunAction.hh"
#include "03NEventAction.hh"
#include "03NSteppingAction.hh"
#include "03NActionInitializtion.hh"

#include "G4UIExecutive.hh"
#include "QGSP_BIC_HP.hh"
#include "G4RunManager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

using namespace N3;

int main(int argc, char** argv){
    G4UIExecutive* ui = nullptr;
    if (argc == 1){
        ui = new G4UIExecutive(argc, argv);
    }

    // The firsr thing main() must do is create an instance of the G4RunManager class.
    // This is the only manager class in the Geant4 kernel which should be explicitly 
    // constructed in the user's main()
    G4RunManager* runManager = new G4RunManager();
    G4VModularPhysicsList* physicsList = new QGSP_BIC_HP;
    DetectorConstruction* detectorConstrution = new DetectorConstruction();
    ActionInitialization* actionInitialization = new ActionInitialization();

    runManager -> SetUserInitialization(physicsList);
    runManager -> SetUserInitialization(detectorConstrution);
    runManager -> SetUserInitialization(actionInitialization);

    // 读取mac文件的指针
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    G4UImanager* UImanager = G4UImanager::GetUIpointer();//已经验证UIManager是存在的

    if( ! ui){
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }
    else{
        
        UImanager->ApplyCommand("/control/execute test.mac");
        
        ui->SessionStart();
        delete ui;
    }
    delete visManager;
    delete runManager;
}
