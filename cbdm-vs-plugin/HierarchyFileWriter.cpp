#include "stdafx.h"
#include "HierarchyFileWriter.h"
#include "common.h"


const std::wstring HierarchyFileWriter::hierarchyFileName = L"cbdm_hierarchy.txt";

HierarchyFileWriter::HierarchyFileWriter()
{}


HierarchyFileWriter::~HierarchyFileWriter()
{}

void HierarchyFileWriter::StartHierarchyWriter(const std::wstring &path)
{
	hierarchyFilePath = path + PATH_SEP + hierarchyFileName;
}

/**
	\brief

*/
bool HierarchyFileWriter::addHierarchyItem(const std::wstring & vsPath, const std::wstring & diskPath)
{
	auto retValue = true;
	if (m_hierarchyCache.find(vsPath) != std::end(m_hierarchyCache))
	{	
		retValue = false;
	}
	m_hierarchyCache[vsPath] = diskPath;

	return retValue;
}

bool HierarchyFileWriter::deleteHierarchyItem(const std::wstring & vsPath)
{
	auto item = m_hierarchyCache.find(vsPath);
	if (item != std::end(m_hierarchyCache))
	{
		m_hierarchyCache.erase(item);
		return true;
	}
	return false;
}

bool HierarchyFileWriter::flush()
{
	std::ofstream ofHierarchy;

	ofHierarchy.open(hierarchyFilePath);
	if (!ofHierarchy.is_open())
	{
		return false;
	}

	return true;
}

void HierarchyFileWriter::clear()
{
	m_hierarchyCache.clear();
}
