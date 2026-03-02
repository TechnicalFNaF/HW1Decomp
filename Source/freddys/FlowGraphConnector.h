#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FlowGraphNode.h"
#include "FlowGraphConnector.generated.h"

UDELEGATE() DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFlowGraphConnected, UFlowGraphConnector*, OtherConnector);
UDELEGATE() DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFlowGraphDisconnected);

UCLASS(Blueprintable, ClassGroup=Custom, Config=Game, meta=(BlueprintSpawnableComponent))
class FREDDYS_API UFlowGraphConnector : public USceneComponent 
{
	GENERATED_BODY()

	friend class AFlowGraphNode;
	
public:
	UFlowGraphConnector() : Super()
	{
		PrimaryComponentTick.bCanEverTick = false;
		bWantsInitializeComponent = true;
	}

	UPROPERTY(BlueprintAssignable)
	FOnFlowGraphConnected OnFlowGraphConnected;
	
	UPROPERTY(BlueprintAssignable)
	FOnFlowGraphDisconnected OnFlowGraphDisconnected;
	
protected:
	static TSet<UFlowGraphConnector*> FlowGraphConnectors;
	
	UPROPERTY(BlueprintReadOnly, Instanced, Transient)
	UFlowGraphConnector* ConnectedTo;
	
private:
	UPROPERTY(Config)
	float FlowConnectorDistance = 1.0f;

public:
	virtual void BeginDestroy() override;
	virtual void BeginPlay() override;

	virtual void OnAttachmentChanged() override;
	virtual void DetachFromComponent(const FDetachmentTransformRules& DetachmentRules) override;

	virtual void OnRegister() override;
	virtual void OnComponentCreated() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
	
	UFUNCTION(BlueprintPure)
	bool HasFlow() const;
	
	UFUNCTION(BlueprintCallable)
	void CheckConnection();
	
	UFUNCTION(BlueprintCallable)
	void Connect(UFlowGraphConnector* OtherConnector);
	
	UFUNCTION(BlueprintCallable)
	void Disconnect();
	
	UFUNCTION(BlueprintPure)
	AFlowGraphNode* GetNodeOwner() const
	{
		return Cast<AFlowGraphNode>(GetOwner());
	}
	
	UFUNCTION(BlueprintPure)
	AFlowGraphNode* GetConnectedNode() const
	{
		return ConnectedTo ? ConnectedTo->GetNodeOwner() : nullptr;
	}
	
	UFUNCTION(BlueprintPure)
	UFlowGraphConnector* GetConnectedConnector() const
	{
		return ConnectedTo;
	}

protected:
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnConnectorRegistered();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnConnected(UFlowGraphConnector* OtherConnector);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnDisconnected();
	
private:
	void OnConnectionEstablished(UFlowGraphConnector* OtherConnector);
	void UnregisterFromNodeOwner();
	void RegisterToNodeOwner();
	
};

