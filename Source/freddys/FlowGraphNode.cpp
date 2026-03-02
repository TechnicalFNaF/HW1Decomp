#include "FlowGraphNode.h"

#include "FlowGraphConnector.h"

TSet<AFlowGraphNode*> AFlowGraphNode::FlowGraphSources;

AFlowGraphNode::AFlowGraphNode()
{
	PrimaryActorTick.bCanEverTick = false;
}

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

void AFlowGraphNode::CalculateFlow()
{
	// inaccurate todo diff this
	
	TArray<AFlowGraphNode*> Array1{this};
	TArray<AFlowGraphNode*> Array2;

	bool bConnectedToFlow = false;
	while (Array1.Num() > 0)
	{
		Array2.Add(Array1.Pop());
		for (UFlowGraphConnector* Connector : FlowConnectors)
		{
			UFlowGraphConnector* ConnectedTo = Connector->GetConnectedConnector();
			if (!ConnectedTo)
				continue;

			AFlowGraphNode* NodeOwner = ConnectedTo->GetNodeOwner();
			if (!NodeOwner)
				continue;
			
			if (NodeOwner->bIsFlowSource)
				bConnectedToFlow = true;

			if (!Array2.Contains(NodeOwner))
				Array1.AddUnique(NodeOwner);
		}
	}
	
	while (Array2.Num() > 0)
	{
		AFlowGraphNode* Node = Array2[0]; 
		Array2.Pop(); // def wrong but idk ill just diff it bro

		Node->ChangeFlowStatus(bConnectedToFlow);
	}
}

void AFlowGraphNode::CheckConnections()
{
	// not sure abt this
	for (UFlowGraphConnector* Connector : FlowConnectors)
	{
		Connector->CheckConnection();
	}
}

void AFlowGraphNode::FlowTypeSwitch(EFlowGraphFlowType& FlowType)
{
	FlowType = HasFlow() ? EFlowGraphFlowType::HasFlow : EFlowGraphFlowType::NoFlow;
}

bool AFlowGraphNode::HasFlow() const
{
	return bIsFlowSource || bIsConnectedToFlow;
}

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

void AFlowGraphNode::ChangeFlowStatus(bool bConnectedToFlow)
{
	if (bConnectedToFlow != bIsConnectedToFlow && !bIsFlowSource)
	{
		bIsConnectedToFlow = bConnectedToFlow;
		OnFlowChanged();
	}
}

void AFlowGraphNode::UnregisterConnector(UFlowGraphConnector* Connector)
{
	// does nothing
}

void AFlowGraphNode::RegisterConnector(UFlowGraphConnector* Connector)
{
	// does nothing
}