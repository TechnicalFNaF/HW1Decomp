#include "HeldGrabbableInfo.h"

FHeldGrabbableInfo::FHeldGrabbableInfo() {
    this->bUsePhysics = false;
    this->Collision = ECollisionEnabled::NoCollision;
    this->GrabSnapType = EGrabSnapType::LocationToHand;
    this->IsLerpingToHand = false;
}

