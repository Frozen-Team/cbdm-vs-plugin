#include "stdafx.h"
#include "SolutionEventsHandler.h"


SolutionEventsHandler::SolutionEventsHandler()
{
	m_refsCount = 0;
	ShowMessage(L"SolutionEventsHandler ctor");
}


SolutionEventsHandler::~SolutionEventsHandler()
{
	ShowMessage(L"SolutionEventsHandler dtor");
}

HRESULT SolutionEventsHandler::QueryInterface(REFIID riid, void ** ppvObject)
{
	if (!ppvObject)
		return E_INVALIDARG;
	*ppvObject = NULL;
	if (riid == IID_IUnknown || riid == IID_IVsSolutionEvents || riid == IID_IVsSolutionEvents2 ||
		riid == IID_IVsSolutionEvents3 || riid == IID_IVsSolutionEvents4)
	{
		*ppvObject = (LPVOID)this;
		AddRef();
		return NOERROR;
	}
	return E_NOINTERFACE;
}

ULONG SolutionEventsHandler::AddRef(void)
{
	return InterlockedIncrement(&m_refsCount);
}

ULONG SolutionEventsHandler::Release(void)
{
	ULONG result = InterlockedDecrement(&m_refsCount);

	if (m_refsCount == 0)
	{
		delete this;
	}

	return result;
}

HRESULT SolutionEventsHandler::OnAfterOpenProject(IVsHierarchy * pHierarchy, BOOL fAdded)
{
	ShowMessage(L"EventsHandler OnAfterOpenProject");
	HierarchyEventsHandler* pHandler = new HierarchyEventsHandler();
	handlers[pHierarchy] = pHandler;
	VSCOOKIE adviceHierarchyEventsHandler;
	HRESULT res = pHierarchy->AdviseHierarchyEvents(pHandler, &adviceHierarchyEventsHandler);
	pHandler->setCookie(adviceHierarchyEventsHandler);
	pHandler = nullptr;

	return res;
}

HRESULT SolutionEventsHandler::OnQueryCloseProject(IVsHierarchy * pHierarchy, BOOL fRemoving, BOOL * pfCancel)
{
	return S_OK;
}

HRESULT SolutionEventsHandler::OnBeforeCloseProject(IVsHierarchy * pHierarchy, BOOL fRemoved)
{
	pHierarchy->UnadviseHierarchyEvents(handlers[pHierarchy]->getCookie());
	handlers.erase(pHierarchy);	


	return S_OK;
}

HRESULT SolutionEventsHandler::OnAfterLoadProject(IVsHierarchy * pStubHierarchy, IVsHierarchy * pRealHierarchy)
{
	return S_OK;
}

HRESULT SolutionEventsHandler::OnQueryUnloadProject(IVsHierarchy * pRealHierarchy, BOOL * pfCancel)
{
	return S_OK;
}

HRESULT SolutionEventsHandler::OnBeforeUnloadProject(IVsHierarchy * pRealHierarchy, IVsHierarchy * pStubHierarchy)
{
	return S_OK;
}

HRESULT SolutionEventsHandler::OnAfterOpenSolution(IUnknown * pUnkReserved, BOOL fNewSolution)
{
	ShowMessage(L"EventsHandler::OnAfterOpenSolution");
	return S_OK;
}

HRESULT SolutionEventsHandler::OnQueryCloseSolution(IUnknown * pUnkReserved, BOOL * pfCancel)
{
	return S_OK;
}

HRESULT SolutionEventsHandler::OnBeforeCloseSolution(IUnknown * pUnkReserved)
{
	// remove handler


	return S_OK;
}

HRESULT SolutionEventsHandler::OnAfterCloseSolution(IUnknown * pUnkReserved)
{
	ShowMessage(L"EventsHandler::OnAfterCloseSolution");
	return S_OK;
}

HRESULT SolutionEventsHandler::OnAfterMergeSolution(IUnknown * pUnkReserved)
{
	return S_OK;
}

HRESULT SolutionEventsHandler::OnAfterRenameProject(IVsHierarchy * pHierarchy)
{
	return S_OK;
}

HRESULT SolutionEventsHandler::OnQueryChangeProjectParent(IVsHierarchy * pHierarchy, IVsHierarchy * pNewParentHier, BOOL * pfCancel)
{
	return S_OK;
}

HRESULT SolutionEventsHandler::OnAfterChangeProjectParent(IVsHierarchy * pHierarchy)
{
	return S_OK;
}

HRESULT SolutionEventsHandler::OnAfterAsynchOpenProject(IVsHierarchy * pHierarchy, BOOL fAdded)
{
	return S_OK;
}