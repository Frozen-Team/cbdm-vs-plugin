#include "stdafx.h"
#include "ItemsInfoProvider.h"
#include "common.h"


ItemsInfoProvider::ItemsInfoProvider()
{
	m_pHierarchy = nullptr;
}

ItemsInfoProvider::~ItemsInfoProvider()
{}

HRESULT ItemsInfoProvider::CheckHierarchyPointer()
{
	if (m_pHierarchy == nullptr)
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT ItemsInfoProvider::SetHierarchyPointer(IVsHierarchy * pHierarchy)
{
	if (pHierarchy == nullptr)
	{
		return E_FAIL;
	}
	m_pHierarchy = pHierarchy;

	return S_OK;
}

HRESULT ItemsInfoProvider::GetItemName(VSITEMID itemId,  BSTR* name)
{
	VSL_CHECKHRESULT(CheckHierarchyPointer());
	VARIANT var;
	HRESULT result = m_pHierarchy->GetProperty(itemId, VSHPROPID_Name, &var);
	if (result == S_OK && var.bstrVal != nullptr)
	{
		*name = var.bstrVal;
	}

	return result;
}

HRESULT ItemsInfoProvider::GetProjectName(BSTR* name)
{
	return GetItemName(VSITEMID_ROOT, name);
}

HRESULT ItemsInfoProvider::GetFirstChildItemId(VSITEMID itemId, VSITEMID& childItemId, int visibleOnly)
{
	VSL_CHECKHRESULT(CheckHierarchyPointer());
	VARIANT var;
	HRESULT result = m_pHierarchy->GetProperty(itemId, (visibleOnly ? VSHPROPID_FirstVisibleChild : VSHPROPID_FirstChild), &var);
	if (result == S_OK)
	{
		childItemId = var.intVal;
	}

	return result;
}

HRESULT ItemsInfoProvider::GetItemType(VSITEMID itemId, GUID * type)
{

	return S_OK;
}

HRESULT ItemsInfoProvider::IsVirtualFolder(VSITEMID itemId, int & isVirtual)
{
	VSL_CHECKHRESULT(CheckHierarchyPointer());
	VARIANT var;
	HRESULT result = m_pHierarchy->GetProperty(itemId, VSHPROPID_ExtObject, &var);

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

HRESULT ItemsInfoProvider::GetProjectPath(BSTR * path)
{
	return E_NOTIMPL;
}

HRESULT ItemsInfoProvider::GetProjectDir(BSTR * dir)
{
	return E_NOTIMPL;
}

HRESULT ItemsInfoProvider::WalkHierarchyItems(VSITEMID itemId, BSTR basePath, std::vector<CAdapt<CComBSTR>>& vsHierarchy,
	 int recursionLevel, bool visibleNodesOnly)
{
	VSL_CHECKHRESULT(CheckHierarchyPointer());
	VARIANT var;

	recursionLevel++;
	//Get the first child node of the current hierarchy being walked
	HRESULT result = m_pHierarchy->GetProperty(itemId, (visibleNodesOnly ? VSHPROPID_FirstVisibleChild : VSHPROPID_FirstChild), &var);
	VSL_CHECKHRESULT(result);

	BSTR name;
	result = GetItemName(itemId, &name); // get parent name
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
			result = GetItemName(childId, &newSiblingName);

			HRESULT result = m_pHierarchy->GetProperty(childId, VSHPROPID_ExtObject, &var);
			//VSL_CHECKHRESULT(result);


			ProjectItem* pProjectItem = (ProjectItem*)var.byref;
			if (pProjectItem != nullptr)
			{
				int isVirtual = 0;
				HRESULT rr = IsVirtualFolder(childId, isVirtual);

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

			WalkHierarchyItems(childId, newBasePath, vsHierarchy, recursionLevel, visibleNodesOnly);
			result = m_pHierarchy->GetProperty(childId, (visibleNodesOnly ? VSHPROPID_NextVisibleSibling : VSHPROPID_NextSibling), &var);

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
