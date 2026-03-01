#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AchievementsFunctions.generated.h"

class UObject;

UCLASS(BlueprintType)
class FREDDYS_API UAchievementsFunctions : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UAchievementsFunctions();

    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void ClearAllAchievements(UObject* WorldContextObject);
    
};

