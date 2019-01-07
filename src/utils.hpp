#pragma once

#include <filesystem>
namespace fs = std::filesystem;
#define ExpandCurDir fs::path(__FILE__).parent_path().u8string() + "/"
