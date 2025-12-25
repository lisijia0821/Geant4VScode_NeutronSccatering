#ifndef N3TrackInformation
#define M3TrackInformation

#include "G4VUserTrackInformation.hh"

class TrackInfo : public G4VUserTrackInformation{

public:
TrackInfo():hasCollided(false){}
~TrackInfo() override = default;

void SetCollided() { hasCollided = true; }
bool HasCollided() const { return hasCollided;}

private:

bool hasCollided;


};

#endif