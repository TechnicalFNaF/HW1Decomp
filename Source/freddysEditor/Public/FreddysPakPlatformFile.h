#pragma once

#include "CoreMinimal.h"
#include "IPlatformFilePak.h"

class FFreddysPakPlatformFile : public FPakPlatformFile
{
public:
	void OnFEngineLoopInitComplete();
	virtual bool Initialize(IPlatformFile* Inner, const TCHAR* CommandLineParam) override;

	/**
	 * Get the unique name for the freddys pak platform file layer
	 */
	static const TCHAR* GetTypeName()
	{
		return TEXT("FreddysPakPlatformFile");
	}
	
	virtual const TCHAR* GetName() const override
	{
		return FFreddysPakPlatformFile::GetTypeName();
	}
};
