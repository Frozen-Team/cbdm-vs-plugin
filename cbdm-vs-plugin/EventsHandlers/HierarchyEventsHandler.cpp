#include "stdafx.h"
#include "HierarchyEventsHandler.h"


HierarchyEventsHandler::HierarchyEventsHandler()
{
	m_refsCount = 0;
	ShowMessage(L"HierarchyEventsHandler ctor");
}


HierarchyEventsHandler::~HierarchyEventsHandler()
{
	ShowMessage(L"HierarchyEventsHandler dtor");
}

HRESULT HierarchyEventsHandler::QueryInterface(REFIID riid, void ** ppvObject)
{
	if (!ppvObject)
		return E_INVALIDARG;
	*ppvObject = NULL;
	if (riid == IID_IUnknown || riid == IID_IVsHierarchyEvents || riid == IID_IVsHierarchyEvents2)
	{
		*ppvObject = (LPVOID)this;
		AddRef();
		return NOERROR;
	}
	return E_NOINTERFACE;
}

ULONG HierarchyEventsHandler::AddRef(void)
{
	return InterlockedIncrement(&m_refsCount);
}

ULONG HierarchyEventsHandler::Release(void)
{
	ULONG result = InterlockedDecrement(&m_refsCount);

	if (m_refsCount == 0)
	{
		delete this;
	}

	return result;
}

HRESULT HierarchyEventsHandler::OnItemAdded(VSITEMID itemidParent, VSITEMID itemidSiblingPrev, VSITEMID itemidAdded)
{
	ShowMessage(L"HierarchyEventsHandler::OnItemAdded");

	return S_OK;
}

HRESULT HierarchyEventsHandler::OnItemsAppended(VSITEMID itemidParent)
{
	ShowMessage(L"HierarchyEventsHandler::OnItemsAppended");

	return S_OK;
}

HRESULT HierarchyEventsHandler::OnItemDeleted(VSITEMID itemid)
{
	ShowMessage(L"HierarchyEventsHandler::OnItemDeleted");

	return S_OK;
}

HRESULT HierarchyEventsHandler::OnPropertyChanged(VSITEMID itemid, VSHPROPID propid, DWORD flags)
{
	//ShowMessage(L"HierarchyEventsHandler::OnPropertyChanged");

	return S_OK;
}

HRESULT HierarchyEventsHandler::OnInvalidateItems(VSITEMID itemidParent)
{
	ShowMessage(L"HierarchyEventsHandler::OnInvalidateItems");

	return S_OK;
}

HRESULT HierarchyEventsHandler::OnInvalidateIcon(HICON hicon)
{
	ShowMessage(L"HierarchyEventsHandler::OnInvalidateIcon");

	return S_OK;
}

HRESULT HierarchyEventsHandler::OnItemAdded(VSITEMID itemidParent, VSITEMID itemidSiblingPrev, VSITEMID itemidAdded, VARIANT_BOOL ensureVisible)
{
	ShowMessage(L"HierarchyEventsHandler::OnItemAdded2");

	return S_OK;
}
