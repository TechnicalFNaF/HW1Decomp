#include "FNAF_GameInstanceBase.h"

UFNAF_GameInstanceBase::UFNAF_GameInstanceBase() {
    this->ForcedVariantNumber = -1;
    this->LoadingWidget = NULL;
}

void UFNAF_GameInstanceBase::SwitchFNAFGameType(EFNAFGameType& GameType) {
}

void UFNAF_GameInstanceBase::StartAsyncSaveGame(USaveGame* SaveGame, const FString& SlotName, int32 UserIndex) {
}

void UFNAF_GameInstanceBase::LoadLevelAsync(const FName& LevelName) {
}

bool UFNAF_GameInstanceBase::IsInDemoMode() const {
    return false;
}

bool UFNAF_GameInstanceBase::HasDLC(EFNAFDLCType DLC) const 
{
    if (DLC == EFNAFDLCType::BaseGame)
        return true;

    if (InstalledDLCList.Contains(DLC))
    {
        return true;
    }

    return true;
    //return ViveportDLCValid;
}

bool UFNAF_GameInstanceBase::GetViveportDLCValid() const 
{
    return false;
}

FString UFNAF_GameInstanceBase::GetPrimaryGPUBrand() 
{
    return FPlatformMisc::GetPrimaryGPUBrand();
}

FString UFNAF_GameInstanceBase::GetGPUBrandName() 
{
    return FPlatformMisc::GetCPUBrand(); // Bug, Inappropriately named function
}

EFNAFGameType UFNAF_GameInstanceBase::GetGameType() const 
{
    return EFNAFGameType::Demo;
}

int32 UFNAF_GameInstanceBase::GetForcedVariantNumber() const 
{
    return 0;
}


