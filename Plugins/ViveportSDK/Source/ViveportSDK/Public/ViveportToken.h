// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreUObject.h"
#include "ViveportType.h"
#include "ViveportToken.generated.h"

/**
 * 
 */
UCLASS()
class VIVEPORTSDK_API UViveportToken : public UObject
{
    GENERATED_BODY()
    
public:
    static void IsReady(ViveportApiStatus *);
    static void GetSessionToken(ViveportApiStatus2 *);
};
