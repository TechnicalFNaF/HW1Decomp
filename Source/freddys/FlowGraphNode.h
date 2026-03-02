#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlowGraphNode.generated.h"

class UFlowGraphConnector;

UENUM()
enum class EFlowGraphFlowType : uint8 
{
	HasFlow,
	NoFlow
};

UCLASS()
class FREDDYS_API AFlowGraphNode : public AActor 
{
	GENERATED_BODY()

public:
	AFlowGraphNode();

	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere)
	bool bIsFlowSource;
	
	UPROPERTY(Transient, VisibleAnywhere)
	bool bIsConnectedToFlow;

	// todo make uproperty blah blah stale pointer
	TSet<UFlowGraphConnector*> FlowConnectors;
	static TSet<AFlowGraphNode*> FlowGraphSources;

public:
	void CalculateFlow();
	
	UFUNCTION(BlueprintCallable)
	void CheckConnections();

	UFUNCTION(BlueprintPure)
	bool HasFlow() const;
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnConnectorConnected(UFlowGraphConnector* MyConnector, UFlowGraphConnector* TheirConnector);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnConnectorDisconnected(UFlowGraphConnector* MyConnector);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnFlowChanged();
	
public:
	UFUNCTION(BlueprintCallable)
	void SetFlowSource(bool EnableAsFlowSource);
	
	UFUNCTION(BlueprintCallable)
	void UnregisterConnector(UFlowGraphConnector* Connector);
	
	UFUNCTION(BlueprintCallable)
	void RegisterConnector(UFlowGraphConnector* Connector);
	
	UFUNCTION(BlueprintPure)
	bool IsFlowSource() const;
	
	UFUNCTION(BlueprintPure)
	TArray<UFlowGraphConnector*> GetConnectors() const;
	
	UFUNCTION(BlueprintCallable)
	void FlowTypeSwitch(EFlowGraphFlowType& FlowType);
	
};

