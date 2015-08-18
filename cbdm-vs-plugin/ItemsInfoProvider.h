#pragma once
class ItemsInfoProvider
{
public:
	ItemsInfoProvider();
	virtual ~ItemsInfoProvider();

protected:
	HRESULT IsVirtualFolder(IVsHierarchy* pHierarchy, VSITEMID itemId, int& isVirtual);

	HRESULT GetChildItemId(IVsHierarchy* pHierarchy, VSITEMID itemId,  VSITEMID& childItemId, int visibleOnly);

	HRESULT GetItemName(IVsHierarchy* pHierarchy, VSITEMID itemId, BSTR* name);

	HRESULT GetRootName(IVsHierarchy* pHierarchy, BSTR* name);

	HRESULT WalkHierarchyItems(IVsHierarchy* pHierarchy, VSITEMID itemId, BSTR basePath, 
		std::vector<CAdapt<CComBSTR>>& vsHierarchy, int recursionLevel, bool visibleNodesOnly);

	// To delete, deprecated
	HRESULT GetNodeName(IVsHierarchy* pHierarchy, VSITEMID itemId, CComBSTR& name);

	


	
};

