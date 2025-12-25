#ifndef N3DetectorConstruction_h
#define N3DetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"

class G4LogicalVolume;

namespace N3{

class DetectorConstruction : public G4VUserDetectorConstruction{
    public:
    DetectorConstruction();
    ~DetectorConstruction() override = default;
    
    G4VPhysicalVolume* Construct() override;

    protected:
    G4LogicalVolume* fScoringVolume = nullptr;

};

}

#endif