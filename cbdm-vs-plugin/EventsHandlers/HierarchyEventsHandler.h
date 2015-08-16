#pragma once


class HierarchyEventsHandler : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IVsHierarchyEvents, 
	public IVsHierarchyEvents2
{
private:
	ULONG m_refsCount;
	VSCOOKIE cookie;
public:
	VSL_DECLARE_NOT_COPYABLE(HierarchyEventsHandler)

public:
	BEGIN_COM_MAP(HierarchyEventsHandler)
		COM_INTERFACE_ENTRY(IVsHierarchyEvents)
		COM_INTERFACE_ENTRY(IVsHierarchyEvents2)
	END_COM_MAP()


public:
	HierarchyEventsHandler();

	virtual ~HierarchyEventsHandler();
	void setCookie(VSCOOKIE cookie) { this->cookie = cookie; }
	VSCOOKIE getCookie() { return this->cookie; }

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

	// Inherited via IVsHierarchyEvents
	//virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject) override;
	//virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
	//virtual ULONG STDMETHODCALLTYPE Release(void) override;


	virtual HRESULT STDMETHODCALLTYPE OnItemAdded(VSITEMID itemidParent, VSITEMID itemidSiblingPrev, VSITEMID itemidAdded) override;
	virtual HRESULT STDMETHODCALLTYPE OnItemsAppended(VSITEMID itemidParent) override;
	virtual HRESULT STDMETHODCALLTYPE OnItemDeleted(VSITEMID itemid) override;
	virtual HRESULT STDMETHODCALLTYPE OnPropertyChanged(VSITEMID itemid, VSHPROPID propid, DWORD flags) override;
	virtual HRESULT STDMETHODCALLTYPE OnInvalidateItems(VSITEMID itemidParent) override;
	virtual HRESULT STDMETHODCALLTYPE OnInvalidateIcon(HICON hicon) override;

	// Inherited via IVsHierarchyEvents2
	virtual HRESULT STDMETHODCALLTYPE OnItemAdded(VSITEMID itemidParent, VSITEMID itemidSiblingPrev, VSITEMID itemidAdded, VARIANT_BOOL ensureVisible) override;
};

