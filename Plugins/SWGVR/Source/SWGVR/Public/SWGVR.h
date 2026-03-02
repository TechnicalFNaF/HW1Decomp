#include "Modules/ModuleManager.h"

struct FSWGVRUserInfo
{
	int UserID;
};

class FSWGVRModule : public IModuleInterface
{
public:

	FSWGVRModule& Get()
	{
		return *m_instance;
	};

	const FSWGVRUserInfo& GetUserInfo(int UserIndex)
	{
		return UserInfo[UserIndex];
	};

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	// Not compiled in exe
	//void UserLoginEventHandler(bool, int, int);

	static FSWGVRModule* m_instance;
	FSWGVRUserInfo UserInfo[0x4]; // Unused, no info on what it does
};