#include "stdafx.h"
#include "HierarchyEventsHandler.h"
#include "common.h"


void HierarchyEventsHandler::SetHierarchy(IVsHierarchy * pHierarchy)
{
	this->m_pHierarchy = pHierarchy;

	BSTR name;
	HRESULT result = GetProjectName(&name);
	VSL_CHECKHRESULT(result);
	CComBSTR rootName;
	VSL_CHECKHRESULT(rootName.Append(name));
	VSL_CHECKHRESULT(rootName.Append(L':'));
	std::vector<CAdapt<CComBSTR>> vsHierarchy;
	VSITEMID firstChild;
	result = GetFirstChildItemId(VSITEMID_ROOT, firstChild, true);
	VSL_CHECKHRESULT(result);
	WalkHierarchyItems(firstChild, rootName, vsHierarchy, 0, true);
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
	
	//ShowMessage(L"HierarchyEventsHandler::OnInvalidateItems");

	return S_OK;
}

HRESULT HierarchyEventsHandler::OnInvalidateIcon(HICON hicon)
{
	return S_OK;
}

HRESULT HierarchyEventsHandler::OnItemAdded(VSITEMID itemidParent, VSITEMID itemidSiblingPrev, VSITEMID itemidAdded, VARIANT_BOOL ensureVisible)
{
	ShowMessage(L"HierarchyEventsHandler::OnItemAdded2");/*
	VARIANT var;
	if (m_pHierarchy)
	{
		CComBSTR name;
		HRESULT res = GetNodeName(m_pHierarchy, itemidAdded, name);
		res = m_pHierarchy->GetProperty(itemidAdded, VSHPROPID_Name, &var);
	}*/

	return S_OK;
}
