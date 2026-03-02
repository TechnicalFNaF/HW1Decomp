#include "AICommonFunctionalities.h"

bool UAICommonFunctionalities::isVerticalAxis(AIScareDirection dir)
{
	return ((int)dir & ((int)AIScareDirection::Up | (int)AIScareDirection::Down)) != false;
}

bool UAICommonFunctionalities::isValidAxisDirection(AIBaseAxisDirection axis, AIScareDirection dir)
{
	return ((int)axis & (int)dir) != 0;
}

bool UAICommonFunctionalities::isHorizontalAxis(AIScareDirection dir)
{
	return ((int)dir & ((int)AIScareDirection::Left | (int)AIScareDirection::Right)) != false;
}