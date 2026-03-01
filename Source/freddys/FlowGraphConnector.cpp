#include "FlowGraphConnector.h"

UFlowGraphConnector::UFlowGraphConnector(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	this->ConnectedTo = NULL;
	this->FlowConnectorDistance = 100.00f;
}




bool UFlowGraphConnector::HasFlow() const {
	return false;
}

AFlowGraphNode* UFlowGraphConnector::GetNodeOwner() const {
	return NULL;
}

AFlowGraphNode* UFlowGraphConnector::GetConnectedNode() const {
	return NULL;
}

UFlowGraphConnector* UFlowGraphConnector::GetConnectedConnector() const {
	return NULL;
}

void UFlowGraphConnector::Disconnect() {
}

void UFlowGraphConnector::Connect(UFlowGraphConnector* OtherConnector) {
}

void UFlowGraphConnector::CheckConnection() {
}


