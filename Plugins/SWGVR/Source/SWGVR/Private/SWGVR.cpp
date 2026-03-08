#include "SWGVR.h"

IMPLEMENT_MODULE(FSWGVRModule, SWGVR)

FSWGVRModule* FSWGVRModule::m_instance = nullptr;

// Matching
void FSWGVRModule::StartupModule()
{
	m_instance = this;
}

void FSWGVRModule::ShutdownModule()
{
	// Empty, does not exist in exe
}