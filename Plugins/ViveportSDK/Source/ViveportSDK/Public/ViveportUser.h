// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreUObject.h"
#include "ViveportType.h"

#include "ViveportUser.generated.h"

/**
 * 
 */
UCLASS()
class VIVEPORTSDK_API UViveportUser : public UObject
{
    GENERATED_BODY()
    
public:
    static bool IsReady(ViveportApiStatus *);
    static FString GetUserID();
    static FString GetUserName();
    static FString GetUserAvatarUrl();
};
