#include "03NDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"

namespace N3{

G4Material* Goethite_material(){
    // 可以不用自己创建元素，直接从Geant4的库中获取，但要是有一些同位素，就可以自己创建
    // G4double H = 1;
    // G4double O = 8;
    // G4double Fe = 26;

    // G4double aeff_H = 1.01 * g/mole;
    // G4double aeff_O = 16.00 * g/mole;
    // G4double aeff_Fe = 55.84 * g/mole;
    G4NistManager* nist = G4NistManager::Instance();
    G4Element* ele_H = nist -> FindOrBuildElement("H");
    G4Element* ele_O = nist -> FindOrBuildElement("O");
    G4Element* ele_Fe = nist -> FindOrBuildElement("Fe");

    G4Material* goethite = new G4Material("goethite", 4.26 * g/cm3, 3); 

    goethite->AddElement(ele_H,0.25);
    goethite->AddElement(ele_O,0.5);
    goethite->AddElement(ele_Fe,0.25);

    return goethite;
}

G4Material* Magnetite_material(){
    G4NistManager* nist = G4NistManager::Instance();

    G4Element* ele_O = nist -> FindOrBuildElement("O");
    G4Element* ele_Fe = nist -> FindOrBuildElement("Fe");

    G4Material* magnetite = new G4Material("magnetite", 5.18 * g/cm3, 2); 


    magnetite->AddElement(ele_O,0.57143);
    magnetite->AddElement(ele_Fe,0.42857);

    return magnetite;
}

G4VPhysicalVolume* separetedModel(G4double length_X,
                                G4double height_Y, 
                                G4double width_Z,
                                G4double centerX,
                                G4double centerY,
                                G4double centerZ,
                                G4Material* goethite_material, 
                                G4LogicalVolume* mother_logicWorld,
                                G4bool checkOverlaps
                                ){
    //target1
    const auto solid_target1 = new G4Box("Target1",
                                    length_X,
                                    height_Y,
                                    width_Z);
    auto logic_target1 = new G4LogicalVolume(solid_target1,
                                    goethite_material,
                                    "Target1");
    auto phys_target1 = new G4PVPlacement(0,
                                    G4ThreeVector(centerX,centerY,centerZ),
                                    logic_target1,
                                    "Target1",
                                    mother_logicWorld,
                                    false,
                                    0,
                                    checkOverlaps
                                    );
    return phys_target1;
}
DetectorConstruction::DetectorConstruction(){}

G4VPhysicalVolume* DetectorConstruction::Construct(){

    G4bool   checkOverlaps = true;
    G4double world_sizeXY = 0.05 * m;
    G4double world_sizeZ = 0.1 * m;

    G4int TargetNumber = 2;
    G4double length_X = 1 * cm / TargetNumber;
    G4double height_Y = 1* cm / TargetNumber;
    G4double width_Z = 1 * cm / TargetNumber;
    G4double center_X = -0.5 * cm;
    G4double center_Y = 0 * cm;
    G4double center_Z = 0 * cm;


    G4NistManager* nist = G4NistManager::Instance();
    G4Material * world_environment = nist->FindOrBuildMaterial("G4_AIR");//AIR一定要大写

    
    //此时solid_world是一个指针，这个指针指向一个const G4Box的对象，可以getName()，但是不允许solid_world->SetParameter()
    const auto solid_world = new G4Box("World",world_sizeXY,world_sizeXY,world_sizeZ);

    auto logic_world = new G4LogicalVolume(solid_world, world_environment,"World");

    auto physworld = new G4PVPlacement(0,
                                    G4ThreeVector(0,0,0),
                                    logic_world,
                                    "World",
                                    0,
                                    false,
                                    0,
                                    checkOverlaps);     //在程序正常运行的时候可以把checkOverlaps改成关闭，节省运行时间

        //开始建立靶物质
    G4Material* goethite_material = Goethite_material();
    G4Material* magnetite_material = Magnetite_material();
    G4VPhysicalVolume* leftPart = separetedModel(length_X, height_Y, width_Z, 
                                                center_X, center_Y,center_Z,
                                                goethite_material,
                                                logic_world,
                                                checkOverlaps);
    G4VPhysicalVolume* rightPart = separetedModel(length_X, height_Y, width_Z, 
                                                -center_X, center_Y, center_Z,
                                                magnetite_material,
                                                logic_world,
                                                checkOverlaps);

    return physworld;
}
}