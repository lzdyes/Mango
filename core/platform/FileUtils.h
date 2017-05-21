#pragma once

#include <string>
#include <vector>

#include "base/Data.h"

namespace RE {
	class FileUtils {
	public:
		static FileUtils* getInstance();

	public:
		bool isFileExists(std::string& path);
		bool isRealPath(std::string& path);
		std::string realPath(std::string& path);

		void addSearchDir(std::string& path);
		void clearSearchDirs();

		Data getData(std::string& path);

	public:
		const std::string App;

	protected:
		std::vector<std::string> _searchDirs;
	};
}