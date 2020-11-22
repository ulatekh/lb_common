#pragma once

#if __APPLE__

#include <boost/filesystem.hpp>
namespace lb {
    namespace filesystem {
        using path = boost::filesystem::path;
        using boost::filesystem::absolute;
        using boost::filesystem::current_path;
        using boost::filesystem::directory_entry;
        using boost::filesystem::directory_iterator;
        using boost::filesystem::exists;
        using boost::filesystem::file_size;
        using file_time_type = std::time_t;
        using boost::filesystem::hash_value;
        using boost::filesystem::is_directory;
        using boost::filesystem::is_regular_file;
        using boost::filesystem::last_write_time;
        using boost::filesystem::recursive_directory_iterator;
        using boost::filesystem::remove;
        using boost::filesystem::rename;
        using boost::filesystem::temp_directory_path;

        using boost::filesystem::filesystem_error;
    }
}

#else
#include <filesystem>
namespace lb {
    namespace filesystem {
        using path = std::filesystem::path;
        using std::filesystem::absolute;
        using std::filesystem::current_path;
        using std::filesystem::directory_entry;
        using std::filesystem::directory_iterator;
        using std::filesystem::exists;
        using std::filesystem::file_size;
        using std::filesystem::file_time_type;
        using std::filesystem::hash_value;
        using std::filesystem::is_directory;
        using std::filesystem::is_regular_file;
        using std::filesystem::last_write_time;
        using std::filesystem::recursive_directory_iterator;
        using std::filesystem::remove;
        using std::filesystem::rename;
        using std::filesystem::temp_directory_path;

        using std::filesystem::filesystem_error;
    }
}
#endif

