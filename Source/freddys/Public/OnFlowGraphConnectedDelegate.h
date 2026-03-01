#pragma once
#include "CoreMinimal.h"
#include "OnFlowGraphConnectedDelegate.generated.h"

class UFlowGraphConnector;

UDELEGATE() DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFlowGraphConnected, UFlowGraphConnector*, OtherConnector);

