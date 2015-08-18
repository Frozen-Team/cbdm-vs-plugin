#include "stdafx.h"
#include "ItemsInfoProvider.h"
#include "common.h"


ItemsInfoProvider::ItemsInfoProvider()
{}


ItemsInfoProvider::~ItemsInfoProvider()
{}

// To delete, deprecated
HRESULT ItemsInfoProvider::GetNodeName(IVsHierarchy* pHierarchy, VSITEMID itemId, CComBSTR& name)
{
	if (pHierarchy == nullptr)
	{
		return E_FAIL;
	}

	VARIANT vTypeName;

	HRESULT r1 = pHierarchy->GetProperty(itemId, VSHPROPID_TypeGuid, &vTypeName);

	VARIANT value;
	HRESULT result = pHierarchy->GetProperty(itemId, VSHPROPID_Name, &value);

	if (result == S_OK && value.bstrVal != nullptr)
	{
		name.AssignBSTR(value.bstrVal);
	}
	else
	{
		return result;
	}

	BSTR canonical;

	result = pHierarchy->GetCanonicalName(itemId, &canonical);

	return result;
}

HRESULT ItemsInfoProvider::GetItemName(IVsHierarchy* pHierarchy, VSITEMID itemId,  BSTR* name)
{
	if (pHierarchy == nullptr)
	{
		return E_FAIL;
	}
	VARIANT var;
	HRESULT result = pHierarchy->GetProperty(itemId, VSHPROPID_Name, &var);
	if (result == S_OK && var.bstrVal != nullptr)
	{
		*name = var.bstrVal;
	}

	return result;
}

HRESULT ItemsInfoProvider::GetRootName(IVsHierarchy* pHierarchy, BSTR* name)
{
	return GetItemName(pHierarchy, VSITEMID_ROOT, name);
}

HRESULT ItemsInfoProvider::GetChildItemId(IVsHierarchy* pHierarchy, VSITEMID itemId, VSITEMID& childItemId, int visibleOnly)
{
	VARIANT var;
	HRESULT result = pHierarchy->GetProperty(itemId, (visibleOnly ? VSHPROPID_FirstVisibleChild : VSHPROPID_FirstChild), &var);
	if (result == S_OK)
	{
		childItemId = var.intVal;
	}

	return result;
}

HRESULT ItemsInfoProvider::IsVirtualFolder(IVsHierarchy * pHierarchy, VSITEMID itemId, int & isVirtual)
{
	if (pHierarchy == nullptr)
	{
		return E_FAIL;
	}

	VARIANT var;
	HRESULT result = pHierarchy->GetProperty(itemId, VSHPROPID_ExtObject, &var);

	ProjectItem* pProjectItem = (ProjectItem*)var.byref;
	if (result != S_OK || pProjectItem == nullptr)
	{
		return E_FAIL;
	}
	BSTR kindBstr;
	pProjectItem->get_Kind(&kindBstr);

	GUID kindGuid;
	result = CLSIDFromString(kindBstr, &kindGuid);
	
	if (result != S_OK)
	{
		return result;
	}

	if (kindGuid == GUID_ItemType_VirtualFolder)
	{
		isVirtual = true;
	}
	else
	{
		isVirtual = false;
	}

	return S_OK;
}

HRESULT ItemsInfoProvider::WalkHierarchyItems(IVsHierarchy* pHierarchy, VSITEMID itemId, BSTR basePath, std::vector<CAdapt<CComBSTR>>& vsHierarchy,
	 int recursionLevel, bool visibleNodesOnly)
{
	if (pHierarchy == nullptr)
	{
		return S_FALSE;
	}

	VARIANT var;






	recursionLevel++;
	//Get the first child node of the current hierarchy being walked
	HRESULT result = pHierarchy->GetProperty(itemId, (visibleNodesOnly ? VSHPROPID_FirstVisibleChild : VSHPROPID_FirstChild), &var);
	VSL_CHECKHRESULT(result);

	BSTR name;
	result = GetItemName(pHierarchy, itemId, &name); // get parent name
	VSL_CHECKHRESULT(result);

	CComBSTR newBasePath(L""); // create new BSTR object
	newBasePath.Append(basePath);
	newBasePath.Append(PATH_SEP);
	newBasePath.Append(name);
	// vsHierarchy.push_back(newBasePath); TODO: Save filters (folders) or not?


	if (result == S_OK)
	{
		VSITEMID childId = (VSITEMID)var.pbVal;
		while (childId != VSITEMID_NIL)
		{
			BSTR newSiblingName;
			result = GetItemName(pHierarchy, childId, &newSiblingName);

			HRESULT result = pHierarchy->GetProperty(childId, VSHPROPID_ExtObject, &var);
			//VSL_CHECKHRESULT(result);


			ProjectItem* pProjectItem = (ProjectItem*)var.byref;
			if (pProjectItem != nullptr)
			{

				BSTR strName;
				pProjectItem->get_Name(&strName);
				pProjectItem->get_Kind(&strName);
				short count;
				pProjectItem->get_FileCount(&count);
				pProjectItem->get_FileNames(0, &strName);
				pProjectItem->get_FileNames(1, &strName);
				Project* project;
				pProjectItem->get_ContainingProject(&project);
				//GUID_ItemType
				//GUID_ItemType_VirtualFolder
				project->get_Name(&strName);
				project->get_FileName(&strName);
				project->get_FullName(&strName);


				int a = 9;
				// TODO
			}

			CComPtr<ProjectItem> itm = (ProjectItem*)childId;
			// TODO!

			CComBSTR newSiblingPath(L"");
			newSiblingPath.Append(newBasePath);
			newSiblingPath.Append(PATH_SEP);
			newSiblingPath.Append(newSiblingName);
			vsHierarchy.push_back(CComBSTR(newSiblingPath.Detach()));

			WalkHierarchyItems(pHierarchy, childId, newBasePath, vsHierarchy, recursionLevel, visibleNodesOnly);
			result = pHierarchy->GetProperty(childId, (visibleNodesOnly ? VSHPROPID_NextVisibleSibling : VSHPROPID_NextSibling), &var);

			if (result == S_OK)
			{
				childId = (VSITEMID)var.pbVal;


				//vsHierarchy.push_back(newBasePath);




			}
			else
			{
				break;
			}
		}
	}

	return result;
}
