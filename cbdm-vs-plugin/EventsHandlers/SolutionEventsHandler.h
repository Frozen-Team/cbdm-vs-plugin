#pragma once
#include <map>

#include "HierarchyEventsHandler.h"

class SolutionEventsHandler:
	public IVsSolutionEvents2,
	public IVsSolutionEvents4
{
private:
	ULONG m_refsCount;
	std::map<IVsHierarchy*, CAdapt<CComPtr<HierarchyEventsHandler>>> handlers;

public:
	VSL_DECLARE_NOT_COPYABLE(SolutionEventsHandler)
public:
	SolutionEventsHandler();

	virtual ~SolutionEventsHandler();

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


	// Common
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject) override;

	virtual ULONG STDMETHODCALLTYPE AddRef(void) override;

	virtual ULONG STDMETHODCALLTYPE Release(void) override;

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

	// Inherited via IVsSolutionEvents4
	virtual HRESULT STDMETHODCALLTYPE OnAfterRenameProject(IVsHierarchy * pHierarchy) override;

	virtual HRESULT STDMETHODCALLTYPE OnQueryChangeProjectParent(IVsHierarchy * pHierarchy, IVsHierarchy * pNewParentHier, BOOL * pfCancel) override;

	virtual HRESULT STDMETHODCALLTYPE OnAfterChangeProjectParent(IVsHierarchy * pHierarchy) override;

	virtual HRESULT STDMETHODCALLTYPE OnAfterAsynchOpenProject(IVsHierarchy * pHierarchy, BOOL fAdded) override;
};

