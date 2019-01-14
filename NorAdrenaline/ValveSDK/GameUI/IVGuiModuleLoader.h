//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef IVGUIMODULELOADER_H
#define IVGUIMODULELOADER_H
#ifdef _WIN32
#pragma once
#endif

//-----------------------------------------------------------------------------
// Purpose: interface to accessing all loaded modules
//-----------------------------------------------------------------------------
class IVGuiModuleLoader : public IBaseInterface
{
public:
	virtual int GetModuleCount() = 0;
	virtual const char *GetModuleLabel(int moduleIndex) = 0;
	virtual CreateInterfaceFn GetModuleFactory(int moduleIndex) = 0;
	virtual bool ActivateModule(int moduleIndex) = 0;
	virtual bool ActivateModule(const char *moduleName) = 0;
	virtual void SetPlatformToRestart() = 0;
};

extern IVGuiModuleLoader* g_pIVGuiModuleLoader;

#define VGUIMODULELOADER_INTERFACE_VERSION "VGuiModuleLoader003"
#endif