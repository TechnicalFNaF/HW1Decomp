#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FlowGraphConnector.generated.h"

UDELEGATE() DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFlowGraphConnected, UFlowGraphConnector*, OtherConnector);
UDELEGATE() DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFlowGraphDisconnected);

UCLASS(Blueprintable, ClassGroup=Custom, Config=Game, meta=(BlueprintSpawnableComponent))
class FREDDYS_API UFlowGraphConnector : public USceneComponent 
{
    GENERATED_BODY()

    friend class AFlowGraphNode;

public:
    UPROPERTY(BlueprintAssignable)
    FOnFlowGraphConnected OnFlowGraphConnected;
    
    UPROPERTY(BlueprintAssignable)
    FOnFlowGraphDisconnected OnFlowGraphDisconnected;
    
protected:
    UPROPERTY(BlueprintReadOnly, Instanced, Transient)
    UFlowGraphConnector* ConnectedTo;
    
private:
    UPROPERTY(Config)
    float FlowConnectorDistance;
    
public:
    UFlowGraphConnector(const FObjectInitializer& ObjectInitializer);

protected:
    UFUNCTION(BlueprintImplementableEvent)
    void OnDisconnected();
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnConnectorRegistered();
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnConnected(UFlowGraphConnector* OtherConnector);
    
public:
    UFUNCTION(BlueprintPure)
    bool HasFlow() const;
    
    UFUNCTION(BlueprintPure)
    AFlowGraphNode* GetNodeOwner() const;
    
    UFUNCTION(BlueprintPure)
    AFlowGraphNode* GetConnectedNode() const;
    
    UFUNCTION(BlueprintPure)
    UFlowGraphConnector* GetConnectedConnector() const;
    
    UFUNCTION(BlueprintCallable)
    void Disconnect();
    
    UFUNCTION(BlueprintCallable)
    void Connect(UFlowGraphConnector* OtherConnector);
    
    UFUNCTION(BlueprintCallable)
    void CheckConnection();
    
};

