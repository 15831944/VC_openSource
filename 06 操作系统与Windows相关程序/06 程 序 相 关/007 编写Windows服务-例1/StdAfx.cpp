// stdafx.cpp : source file that includes just the standard includes
//  stdafx.pch will be the pre-compiled header
//  stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#include <statreg.cpp>
#endif

#include <atlimpl.cpp>

LRESULT CServiceModule::BackupData()
{
	CopyFile("c:\\Book.mdb","d:\\Book.mdb",true);
  return 0;
}
