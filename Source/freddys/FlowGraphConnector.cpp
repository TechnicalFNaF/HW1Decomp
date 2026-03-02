#include "FlowGraphConnector.h"

TSet<UFlowGraphConnector*> UFlowGraphConnector::FlowGraphConnectors;

void UFlowGraphConnector::BeginDestroy()
{
	FlowGraphConnectors.Remove(this);
	UnregisterFromNodeOwner();
	Super::BeginDestroy();
}

void UFlowGraphConnector::BeginPlay()
{
	FlowGraphConnectors.Add(this);
	Super::BeginPlay();
}

void UFlowGraphConnector::OnAttachmentChanged()
{
	RegisterToNodeOwner();
	Super::OnAttachmentChanged();
}

void UFlowGraphConnector::DetachFromComponent(const FDetachmentTransformRules& DetachmentRules)
{
	UnregisterFromNodeOwner();
	Super::DetachFromComponent(DetachmentRules);
}

void UFlowGraphConnector::OnRegister()
{
	RegisterToNodeOwner();
	Super::OnRegister();
	OnConnectorRegistered();
}

void UFlowGraphConnector::OnComponentCreated()
{
	// does nothing extra
	Super::OnComponentCreated();
}

void UFlowGraphConnector::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	FlowGraphConnectors.Remove(this);
	UnregisterFromNodeOwner();
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

bool UFlowGraphConnector::HasFlow() const
{
	AFlowGraphNode* NodeOwner = GetNodeOwner();
	return NodeOwner && NodeOwner->HasFlow();
}

void UFlowGraphConnector::CheckConnection()
{
	FVector ThisLocation = GetComponentLocation();

	UFlowGraphConnector* BestConnector = nullptr;
	float BestConnectorDistance = FLT_MAX;
	
	for (UFlowGraphConnector* Connector : FlowGraphConnectors)
	{
		if (Connector != this)
		{
			float Distance = FVector::DistSquared(GetComponentLocation(), ThisLocation);
			if (Distance < BestConnectorDistance)
			{
				BestConnector = Connector;
				BestConnectorDistance = Distance;
			}
		}
	}
	
	if (BestConnectorDistance > FlowConnectorDistance)
	{
		Disconnect();
	}
	else if (ConnectedTo != BestConnector && BestConnector != this)
	{
		Connect(BestConnector);
	}
}

void UFlowGraphConnector::Disconnect()
{
	if (ConnectedTo)
	{
		OnDisconnected();
		OnFlowGraphDisconnected.Broadcast();
	
		ConnectedTo->OnDisconnected();
		ConnectedTo->OnFlowGraphDisconnected.Broadcast();
	
		// todo dont call getnodeowner twice
		GetNodeOwner()->internal_OnConnectorDisconnected(ConnectedTo);
		ConnectedTo = nullptr;

		AFlowGraphNode* NodeOwner = GetNodeOwner();
		if (NodeOwner)
		{
			NodeOwner->internal_OnConnectorDisconnected(this);
		}
	}
}

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

void UFlowGraphConnector::UnregisterFromNodeOwner()
{
	AFlowGraphNode* NodeOwner = GetNodeOwner();
	if (NodeOwner)
		NodeOwner->UnregisterConnector(this);
}

void UFlowGraphConnector::RegisterToNodeOwner()
{
	AFlowGraphNode* NodeOwner = GetNodeOwner();
	if (NodeOwner)
		NodeOwner->RegisterConnector(this);
}


