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
	virtual void Tick(float DeltaSeconds) override;
	
private:
	UPROPERTY(EditAnywhere)
	bool bIsFlowSource;
	
	UPROPERTY(Transient, VisibleAnywhere)
	bool bIsConnectedToFlow;

	// todo make uproperty blah blah stale pointer
	TSet<UFlowGraphConnector*> FlowConnectors;
	static TSet<AFlowGraphNode*> FlowGraphSources;

	void CalculateFlow();
	
public:
	UFUNCTION(BlueprintCallable)
	void CheckConnections();

	// Matching
	UFUNCTION(BlueprintCallable, meta=(ExpandEnumAsExecs="FlowType"))
	void FlowTypeSwitch(EFlowGraphFlowType& FlowType)
	{
		FlowType = HasFlow() ? EFlowGraphFlowType::HasFlow : EFlowGraphFlowType::NoFlow;
	}

	UFUNCTION(BlueprintPure)
	bool HasFlow() const;
	
	UFUNCTION(BlueprintCallable)
	void SetFlowSource(bool EnableAsFlowSource);

	// Matching
	UFUNCTION(BlueprintPure)
	bool IsFlowSource() const
	{
		return bIsFlowSource;
	}
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnConnectorConnected(UFlowGraphConnector* MyConnector, UFlowGraphConnector* TheirConnector);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnConnectorDisconnected(UFlowGraphConnector* MyConnector);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnFlowChanged();

	void ChangeFlowStatus(bool bConnectedToFlow);
	
public:
	UFUNCTION(BlueprintCallable)
	void UnregisterConnector(UFlowGraphConnector* Connector);
	
	UFUNCTION(BlueprintCallable)
	void RegisterConnector(UFlowGraphConnector* Connector);
	
	// Matching
	UFUNCTION(BlueprintPure)
	TArray<UFlowGraphConnector*> GetConnectors() const
	{
		return FlowConnectors.Array();
	}

	void internal_OnConnectorConnected(UFlowGraphConnector* MyConnector, UFlowGraphConnector* TheirConnector);
	void internal_OnConnectorDisconnected(UFlowGraphConnector* MyConnector);
};

