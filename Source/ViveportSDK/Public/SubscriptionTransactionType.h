#pragma once
#include "CoreMinimal.h"
#include "SubscriptionTransactionType.generated.h"

UENUM()
enum class SubscriptionTransactionType {
    UNKNOWN,
    PAID,
    REDEEM,
    FREETRIAL,
};

