#include "FlowGraphNode.h"

#include "FlowGraphConnector.h"

TSet<AFlowGraphNode*> AFlowGraphNode::FlowGraphSources;

// Matching
AFlowGraphNode::AFlowGraphNode()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Matching
void AFlowGraphNode::BeginPlay()
{
	FlowConnectors.Empty();

	TArray<UActorComponent*> Components = GetComponentsByClass(UFlowGraphConnector::StaticClass());
	for (UActorComponent* Comp : Components)
	{
		FlowConnectors.Add(Cast<UFlowGraphConnector>(Comp));
	}
	
	if (bIsFlowSource)
	{
		FlowGraphSources.Add(this);
	}
	
	Super::BeginPlay();
}

// Matching
void AFlowGraphNode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

// Matching
void AFlowGraphNode::CalculateFlow()
{
	TArray<AFlowGraphNode*> NodesToVisit;
	TArray<AFlowGraphNode*> NodesVisited;

	NodesToVisit.Add(this);

	bool bConnectedToFlow = false;
	while (NodesToVisit.Num() > 0)
	{
		AFlowGraphNode* Node = NodesToVisit[0]; 
		NodesToVisit.RemoveAt(0);
		NodesVisited.Add(Node);
		
		for (UFlowGraphConnector* const Connector : Node->FlowConnectors)
		{
			UFlowGraphConnector* ConnectedTo = Connector->GetConnectedConnector();
			if (ConnectedTo)
			{
				AFlowGraphNode* NodeOwner = ConnectedTo->GetNodeOwner();
				if (NodeOwner)
				{
					if (NodeOwner->bIsFlowSource)
						bConnectedToFlow = true;

					if (!NodesVisited.Contains(NodeOwner))
						NodesToVisit.AddUnique(NodeOwner);
				}
			}
		}
	}
	
	while (NodesVisited.Num() > 0)
	{
		AFlowGraphNode* Node = NodesVisited[0]; 
		NodesVisited.RemoveAt(0);
		Node->ChangeFlowStatus(bConnectedToFlow);
	}
}

// Matching
void AFlowGraphNode::CheckConnections()
{
	for (UFlowGraphConnector* Connector : FlowConnectors)
	{
		Connector->CheckConnection();
	}
}

// Matching
bool AFlowGraphNode::HasFlow() const
{
	return bIsFlowSource || bIsConnectedToFlow;
}

// Matching
void AFlowGraphNode::SetFlowSource(bool EnableAsFlowSource)
{
	if (bIsFlowSource != EnableAsFlowSource)
	{
		bIsFlowSource = EnableAsFlowSource;
		if (EnableAsFlowSource)
		{
			FlowGraphSources.Add(this);
		}
		else
		{
			FlowGraphSources.Remove(this);
		}
		OnFlowChanged();
		CalculateFlow();
	}
}

// Matching
void AFlowGraphNode::ChangeFlowStatus(bool bConnectedToFlow)
{
	if (bConnectedToFlow != bIsConnectedToFlow && !bIsFlowSource)
	{
		bIsConnectedToFlow = bConnectedToFlow;
		OnFlowChanged();
	}
}

// Matching
void AFlowGraphNode::UnregisterConnector(UFlowGraphConnector* Connector)
{
	
}

// Matching
void AFlowGraphNode::RegisterConnector(UFlowGraphConnector* Connector)
{
	
}

// Matching
void AFlowGraphNode::internal_OnConnectorConnected(
	UFlowGraphConnector* MyConnector, UFlowGraphConnector* TheirConnector)
{
	CalculateFlow();
	OnConnectorConnected(MyConnector, TheirConnector);
}

// Matching
void AFlowGraphNode::internal_OnConnectorDisconnected(UFlowGraphConnector* MyConnector)
{
	CalculateFlow();
	OnConnectorDisconnected(MyConnector);
}
