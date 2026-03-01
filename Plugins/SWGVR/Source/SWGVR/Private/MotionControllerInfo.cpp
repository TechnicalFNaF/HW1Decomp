#include "MotionControllerInfo.h"

FMotionControllerInfo::FMotionControllerInfo() {
    this->ClosestGrabbableActor = NULL;
    this->ClosestGrabbableDistance = 0.00f;
    this->ClosestHoveredActor = NULL;
    this->ClosestHoveredComponent = NULL;
    this->ClosestDistance = 0.00f;
    this->bIsTracked = false;
}

