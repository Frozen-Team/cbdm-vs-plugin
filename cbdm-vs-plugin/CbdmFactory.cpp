#include "stdafx.h"
#include "CbdmFactory.h"


CbdmFactory::CbdmFactory()
{
	ShowMessage(L"SolutionEventsHandler ctor");
}


CbdmFactory::~CbdmFactory()
{
	ShowMessage(L"SolutionEventsHandler dtor");
}

HRESULT CbdmFactory::OnAfterOpenProject(IVsHierarchy * pHierarchy, BOOL fAdded)
{
	ShowMessage(L"EventsHandler OnAfterOpenProject");
	handlers[pHierarchy] = new CComObject<HierarchyEventsHandler>;
	VSCOOKIE adviceHierarchyEventsHandler;
	HRESULT res = pHierarchy->AdviseHierarchyEvents(handlers[pHierarchy].m_T, &adviceHierarchyEventsHandler);
	handlers[pHierarchy]->setCookie(adviceHierarchyEventsHandler);

	return res;
}

HRESULT CbdmFactory::OnQueryCloseProject(IVsHierarchy * pHierarchy, BOOL fRemoving, BOOL * pfCancel)
{
	return S_OK;
}

HRESULT CbdmFactory::OnBeforeCloseProject(IVsHierarchy * pHierarchy, BOOL fRemoved)
{
	//pHierarchy->UnadviseHierarchyEvents(handlers[pHierarchy]->getCookie());
	//handlers.erase(pHierarchy);	


	return S_OK;
}

HRESULT CbdmFactory::OnAfterLoadProject(IVsHierarchy * pStubHierarchy, IVsHierarchy * pRealHierarchy)
{
	return S_OK;
}

HRESULT CbdmFactory::OnQueryUnloadProject(IVsHierarchy * pRealHierarchy, BOOL * pfCancel)
{
	return S_OK;
}

HRESULT CbdmFactory::OnBeforeUnloadProject(IVsHierarchy * pRealHierarchy, IVsHierarchy * pStubHierarchy)
{
	return S_OK;
}

HRESULT CbdmFactory::OnAfterOpenSolution(IUnknown * pUnkReserved, BOOL fNewSolution)
{
	ShowMessage(L"EventsHandler::OnAfterOpenSolution");
	return S_OK;
}

HRESULT CbdmFactory::OnQueryCloseSolution(IUnknown * pUnkReserved, BOOL * pfCancel)
{
	return S_OK;
}

HRESULT CbdmFactory::OnBeforeCloseSolution(IUnknown * pUnkReserved)
{
	// remove handler


	return S_OK;
}

HRESULT CbdmFactory::OnAfterCloseSolution(IUnknown * pUnkReserved)
{
	ShowMessage(L"EventsHandler::OnAfterCloseSolution");
	return S_OK;
}

HRESULT CbdmFactory::OnAfterMergeSolution(IUnknown * pUnkReserved)
{
	return S_OK;
}