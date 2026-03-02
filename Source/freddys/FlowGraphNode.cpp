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
	// TODO
}

void AFlowGraphNode::CheckConnections()
{
	// not sure abt this
	for (UFlowGraphConnector* Connector : FlowConnectors)
	{
		Connector->CheckConnection();
	}
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

void AFlowGraphNode::UnregisterConnector(UFlowGraphConnector* Connector)
{
	// does nothing
}

void AFlowGraphNode::RegisterConnector(UFlowGraphConnector* Connector)
{
	// does nothing
}




bool AFlowGraphNode::IsFlowSource() const {
	return false;
}

TArray<UFlowGraphConnector*> AFlowGraphNode::GetConnectors() const {
	return TArray<UFlowGraphConnector*>();
}

void AFlowGraphNode::FlowTypeSwitch(EFlowGraphFlowType& FlowType) {
}
