#pragma once

#include <map>
#include <vector>

class HierarchyFileWriter
{
	VSL_DECLARE_NOT_COPYABLE(HierarchyFileWriter)
public:
	explicit HierarchyFileWriter();
	virtual ~HierarchyFileWriter();

protected:
	void StartHierarchyWriter(const std::wstring&);

	bool addHierarchyItem(const std::wstring&, const std::wstring&);

	bool deleteHierarchyItem(const std::wstring&);

	bool flush();

	void clear();

private:

	// (key, val) == (path in vs, path on disk)
	std::map<std::wstring, std::wstring> m_hierarchyCache;

	static const std::wstring hierarchyFileName;

	std::wstring hierarchyFilePath;

};

