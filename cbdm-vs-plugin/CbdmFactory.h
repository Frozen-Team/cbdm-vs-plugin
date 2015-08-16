#pragma once
#include <map>

#include "EventsHandlers\HierarchyEventsHandler.h"

class CbdmFactory :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IVsSolutionEvents2
{
	VSL_DECLARE_NOT_COPYABLE(CbdmFactory)
private:
	
	std::map<IVsHierarchy*, CAdapt<CComPtr<HierarchyEventsHandler>>> handlers;

public:
	BEGIN_COM_MAP(CbdmFactory)
		COM_INTERFACE_ENTRY(IVsSolutionEvents)
		COM_INTERFACE_ENTRY(IVsSolutionEvents2)
	END_COM_MAP()
	
public:
	CbdmFactory();

	virtual ~CbdmFactory();

	void ShowMessage(CComBSTR message)
	{
		CComPtr<IVsUIShell> shell;
		HRESULT queryRes = VSL_SERVICE_PROVIDER::QueryService(SID_SVsUIShell, &shell);
		VSL_CHECKHRESULT(queryRes);


		LONG lResult;
		HRESULT hr = shell->ShowMessageBox(
			0,
			CLSID_NULL,
			W2OLE(L"Message"),
			message,
			NULL,
			0,
			OLEMSGBUTTON_OK,
			OLEMSGDEFBUTTON_FIRST,
			OLEMSGICON_INFO,
			0,
			&lResult);
	}

	// Inherited via IVsSolutionEvents
	virtual HRESULT STDMETHODCALLTYPE OnAfterOpenProject(IVsHierarchy * pHierarchy, BOOL fAdded) override;
	virtual HRESULT STDMETHODCALLTYPE OnQueryCloseProject(IVsHierarchy * pHierarchy, BOOL fRemoving, BOOL * pfCancel) override;
	virtual HRESULT STDMETHODCALLTYPE OnBeforeCloseProject(IVsHierarchy * pHierarchy, BOOL fRemoved) override;
	virtual HRESULT STDMETHODCALLTYPE OnAfterLoadProject(IVsHierarchy * pStubHierarchy, IVsHierarchy * pRealHierarchy) override;
	virtual HRESULT STDMETHODCALLTYPE OnQueryUnloadProject(IVsHierarchy * pRealHierarchy, BOOL * pfCancel) override;
	virtual HRESULT STDMETHODCALLTYPE OnBeforeUnloadProject(IVsHierarchy * pRealHierarchy, IVsHierarchy * pStubHierarchy) override;
	virtual HRESULT STDMETHODCALLTYPE OnAfterOpenSolution(IUnknown * pUnkReserved, BOOL fNewSolution) override;
	virtual HRESULT STDMETHODCALLTYPE OnQueryCloseSolution(IUnknown * pUnkReserved, BOOL * pfCancel) override;
	virtual HRESULT STDMETHODCALLTYPE OnBeforeCloseSolution(IUnknown * pUnkReserved) override;
	virtual HRESULT STDMETHODCALLTYPE OnAfterCloseSolution(IUnknown * pUnkReserved) override;

	// Inherited via IVsSolutionEvents2
	virtual HRESULT STDMETHODCALLTYPE OnAfterMergeSolution(IUnknown * pUnkReserved) override;
};

