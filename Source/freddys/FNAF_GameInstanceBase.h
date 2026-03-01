#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FNAF_Collectables.h"

#include "FNAF_GameInstanceBase.generated.h"

UENUM()
enum class EFNAFDLCType : uint8
{
    BaseGame,
    Halloween,
};

class USaveGame;
class UUserWidget;

UCLASS(NonTransient)
class FREDDYS_API UFNAF_GameInstanceBase : public UGameInstance {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 ForcedVariantNumber;
    
private:
    UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> LoadingWidget;
    UUserWidget* InstancedLoadingWidget;
    
    TArray<EFNAFDLCType> InstalledDLCList;

public:
    UFNAF_GameInstanceBase();

    UFUNCTION(BlueprintCallable)
    void SwitchFNAFGameType(EFNAFGameType& GameType);
    
    UFUNCTION(BlueprintCallable)
    void StartAsyncSaveGame(USaveGame* SaveGame, const FString& SlotName, int32 UserIndex);
    
    UFUNCTION(BlueprintCallable)
    void LoadLevelAsync(const FName& LevelName);
    
    UFUNCTION(BlueprintPure)
    bool IsInDemoMode() const;
    
    UFUNCTION(BlueprintPure)
    bool HasDLC(EFNAFDLCType DLC) const;
    
    UFUNCTION(BlueprintPure)
    bool GetViveportDLCValid() const;
    
    UFUNCTION(BlueprintPure)
    static FString GetPrimaryGPUBrand();
    
    UFUNCTION(BlueprintPure)
    static FString GetGPUBrandName();
    
    UFUNCTION(BlueprintPure)
    EFNAFGameType GetGameType() const;
    
    UFUNCTION(BlueprintPure)
    int32 GetForcedVariantNumber() const;
    
};

