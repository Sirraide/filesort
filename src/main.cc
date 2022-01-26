#include <clocale>
#include <filesystem>
#include <fmt/format.h>
#include <sys/stat.h>
#include <vector>

namespace fs = std::filesystem;

int main() {
	setlocale(LC_ALL, "");

	fs::directory_iterator dir("..");
	std::vector<fs::path>  files;

	for (const auto& entry : dir) {
		if (!entry.is_regular_file()) continue;
		files.push_back(entry.path());
	}

	std::sort(files.begin(), files.end(), [](const fs::path& a, const fs::path& b) {
		struct stat st_a {
		}, st_b{};
		stat(a.c_str(), &st_a);
		stat(b.c_str(), &st_b);
		return st_a.st_ctim.tv_sec < st_b.st_ctim.tv_sec;
	});

	int i = 0;
	for (const auto& file : files)
		rename(file, fmt::format("../{} {}", ++i, file.filename().string()));
}
