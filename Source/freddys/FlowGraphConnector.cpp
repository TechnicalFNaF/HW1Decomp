#include "FlowGraphConnector.h"

#undef INFINITY
#define INFINITY ((float)(_HUGE_ENUF * _HUGE_ENUF))

TSet<UFlowGraphConnector*> UFlowGraphConnector::FlowGraphConnectors;

// Matching
UFlowGraphConnector::UFlowGraphConnector()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

// Matching
void UFlowGraphConnector::BeginDestroy()
{
	FlowGraphConnectors.Remove(this);
	UnregisterFromNodeOwner();
	Super::BeginDestroy();
}

// Matching
void UFlowGraphConnector::BeginPlay()
{
	FlowGraphConnectors.Add(this);
	Super::BeginPlay();
}

// Matching
void UFlowGraphConnector::OnAttachmentChanged()
{
	RegisterToNodeOwner();
	Super::OnAttachmentChanged();
}

// Matching
void UFlowGraphConnector::DetachFromComponent(const FDetachmentTransformRules& DetachmentRules)
{
	UnregisterFromNodeOwner();
	Super::DetachFromComponent(DetachmentRules);
}

// Matching
void UFlowGraphConnector::OnRegister()
{
	RegisterToNodeOwner();
	Super::OnRegister();
	OnConnectorRegistered();
}

// Matching
void UFlowGraphConnector::OnComponentCreated()
{
	Super::OnComponentCreated();
}

// Matching
void UFlowGraphConnector::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	FlowGraphConnectors.Remove(this);
	UnregisterFromNodeOwner();
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

// Matching
bool UFlowGraphConnector::HasFlow() const
{
	AFlowGraphNode* NodeOwner = GetNodeOwner();
	return NodeOwner && NodeOwner->HasFlow();
}

// Matching
void UFlowGraphConnector::CheckConnection()
{
	FVector ThisLocation = GetComponentLocation();

	UFlowGraphConnector* BestConnector = nullptr;
	float BestConnectorDistance = INFINITY;
	
	for (UFlowGraphConnector* const Connector : FlowGraphConnectors)
	{
		if (Connector != this)
		{
			float Distance = FVector::DistSquared(ThisLocation, Connector->GetComponentLocation());
			if (Distance < BestConnectorDistance)
			{
				BestConnector = Connector;
				BestConnectorDistance = Distance;
			}
		}
	}
	
	if (BestConnectorDistance <= FlowConnectorDistance)
	{
		Connect(BestConnector);
	}
	else
	{
		Disconnect();
	}
}

// Matching
void UFlowGraphConnector::Disconnect()
{
	if (ConnectedTo)
	{
		OnDisconnected();
		OnFlowGraphDisconnected.Broadcast();
	
		ConnectedTo->OnDisconnected();
		ConnectedTo->OnFlowGraphDisconnected.Broadcast();
	
		ConnectedTo->GetNodeOwner()->internal_OnConnectorDisconnected(ConnectedTo);
		ConnectedTo = nullptr;

		AFlowGraphNode* NodeOwner = GetNodeOwner();
		if (NodeOwner)
		{
			NodeOwner->internal_OnConnectorDisconnected(this);
		}
	}
}

// Matching
AFlowGraphNode* UFlowGraphConnector::GetNodeOwner() const
{
	return Cast<AFlowGraphNode>(GetOwner());
}

// Matching
void UFlowGraphConnector::Connect(UFlowGraphConnector* OtherConnector)
{
	if (ConnectedTo != OtherConnector && OtherConnector != this)
	{
		Disconnect();
		if (OtherConnector)
		{
			OnConnectionEstablished(OtherConnector);
			OtherConnector->OnConnectionEstablished(this);
		}
		ConnectedTo = OtherConnector;
	}
}

// Matching
void UFlowGraphConnector::OnConnectionEstablished(UFlowGraphConnector* OtherConnector)
{
	if (ConnectedTo != OtherConnector)
	{
		OnConnected(OtherConnector);
		OnFlowGraphConnected.Broadcast(OtherConnector);
		ConnectedTo = OtherConnector;

		AFlowGraphNode* NodeOwner = GetNodeOwner();
		if (NodeOwner)
		{
			NodeOwner->internal_OnConnectorConnected(this, OtherConnector);
		}
	}
}

// Matching
void UFlowGraphConnector::UnregisterFromNodeOwner()
{
	AFlowGraphNode* NodeOwner = GetNodeOwner();
	if (NodeOwner)
		NodeOwner->UnregisterConnector(this);
}

// Matching
void UFlowGraphConnector::RegisterToNodeOwner()
{
	AFlowGraphNode* NodeOwner = GetNodeOwner();
	if (NodeOwner)
		NodeOwner->RegisterConnector(this);
}


