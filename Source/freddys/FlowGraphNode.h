#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlowGraphNode.generated.h"

class UFlowGraphConnector;

UENUM()
enum class EFlowGraphFlowType : uint8 
{
    HasFlow,
    NoFlow,
};

UCLASS()
class FREDDYS_API AFlowGraphNode : public AActor 
{
    GENERATED_BODY()

public:
private:
    UPROPERTY(EditAnywhere)
    bool bIsFlowSource;
    
    UPROPERTY(Transient, VisibleAnywhere)
    bool bIsConnectedToFlow;
    
public:
    AFlowGraphNode(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void UnregisterConnector(UFlowGraphConnector* Connector);
    
    UFUNCTION(BlueprintCallable)
    void SetFlowSource(bool EnableAsFlowSource);
    
    UFUNCTION(BlueprintCallable)
    void RegisterConnector(UFlowGraphConnector* Connector);
    
protected:
    UFUNCTION(BlueprintImplementableEvent)
    void OnFlowChanged();
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnConnectorDisconnected(UFlowGraphConnector* MyConnector);
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnConnectorConnected(UFlowGraphConnector* MyConnector, UFlowGraphConnector* TheirConnector);
    
public:
    UFUNCTION(BlueprintPure)
    bool IsFlowSource() const;
    
    UFUNCTION(BlueprintPure)
    bool HasFlow() const;
    
    UFUNCTION(BlueprintPure)
    TArray<UFlowGraphConnector*> GetConnectors() const;
    
    UFUNCTION(BlueprintCallable)
    void FlowTypeSwitch(EFlowGraphFlowType& FlowType);
    
    UFUNCTION(BlueprintCallable)
    void CheckConnections();
    
};

