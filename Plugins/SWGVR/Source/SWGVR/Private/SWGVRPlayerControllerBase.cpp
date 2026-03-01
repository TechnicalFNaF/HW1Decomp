#include "SWGVRPlayerControllerBase.h"

ASWGVRPlayerControllerBase::ASWGVRPlayerControllerBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->ClickEventKeys.AddDefaulted(1);
}

void ASWGVRPlayerControllerBase::OnUsingGamepadChanged_Implementation() {
}

bool ASWGVRPlayerControllerBase::IsUsingGamepad() const {
    return false;
}


