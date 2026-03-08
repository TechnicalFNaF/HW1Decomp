#include "AICommonFunctionalities.h"

// Matching
bool UAICommonFunctionalities::isVerticalAxis(AIScareDirection dir)
{
	return ((uint8)dir & (uint8)AIBaseAxisDirection::Vertical) != 0;
}

// Matching
bool UAICommonFunctionalities::isValidAxisDirection(AIBaseAxisDirection axis, AIScareDirection dir)
{
	return ((uint8)axis & (uint8)dir) != 0;
}

// Not matching
bool UAICommonFunctionalities::isHorizontalAxis(AIScareDirection dir)
{
	return ((uint8)dir & (uint8)AIBaseAxisDirection::Horizontal) != 0;
}