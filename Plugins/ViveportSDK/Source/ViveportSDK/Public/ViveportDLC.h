// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreUObject.h"
#include "ViveportType.h"
#include "ViveportDLC.generated.h"

/**
 * 
 */
UCLASS()
class VIVEPORTSDK_API UViveportDLC : public UObject
{
    GENERATED_BODY()

public:
    static int IsReady(ViveportApiStatus* callback);
    static int GetCount();
    static bool GetIsAvailable(int index, FString &app_id, bool &isAvailable);
    static int IsSubscribed();
};
