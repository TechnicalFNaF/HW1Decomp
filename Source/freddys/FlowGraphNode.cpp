#include "FlowGraphNode.h"

AFlowGraphNode::AFlowGraphNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	this->bIsFlowSource = false;
	this->bIsConnectedToFlow = false;
}

void AFlowGraphNode::UnregisterConnector(UFlowGraphConnector* Connector) {
}

void AFlowGraphNode::SetFlowSource(bool EnableAsFlowSource) {
}

void AFlowGraphNode::RegisterConnector(UFlowGraphConnector* Connector) {
}




bool AFlowGraphNode::IsFlowSource() const {
	return false;
}

bool AFlowGraphNode::HasFlow() const {
	return false;
}

TArray<UFlowGraphConnector*> AFlowGraphNode::GetConnectors() const {
	return TArray<UFlowGraphConnector*>();
}

void AFlowGraphNode::FlowTypeSwitch(EFlowGraphFlowType& FlowType) {
}

void AFlowGraphNode::CheckConnections() {
}


