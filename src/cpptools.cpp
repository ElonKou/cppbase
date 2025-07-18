/*================================================================
*  Copyright (C)2021 All rights reserved.
*  FileName : cpptools.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sun 11 Sep 2022 02:32:18 PM CST
================================================================*/

#include "cpptools.hh"

namespace cppt {

// print information

void PrintInfo(std::string str, INFO_TYPE info_type) {
    std::string s = GetColors(info_type) + str + NONEC;
    printf("%s", s.c_str());
}

std::time_t GetNowTime() {
    // return std::chrono::system_clock::to_time_t(std::chrono::high_resolution_clock::now());
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

std::string ConvertTime2Str(std::time_t tm, bool hasyear) {
    std::tm* now_tm = std::localtime(&tm);
    char     buffer[32];
    if (hasyear) {
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", now_tm);
    } else {
        std::strftime(buffer, sizeof(buffer), "%H:%M:%S", now_tm);
    }
    return std::string(buffer);
}

// File tools

// example : "/home/biulab/app/TENCENT_EXP/qikan_cache/joint.json"
std::vector<std::string> SeperateFilePath(const std::string& path) {
    size_t      ipos_root = path.find_last_of('/');
    size_t      ipos_sub  = path.find_last_of('.');
    std::string path_root = path.substr(0, ipos_root);                                 // folder     : "/home/biulab/app/TENCENT_EXP/qikan_cache"
    std::string path_pat  = path.substr(ipos_root + 1, path.length() - ipos_root - 1); // file_path  : "joint.json"
    std::string path_name = path.substr(ipos_root + 1, ipos_sub - ipos_root - 1);      // short name : "joint"
    std::string path_sub  = path.substr(ipos_sub, path.length() - ipos_sub);           // sub name   : ".json"
    return {path_root, path_pat, path_name, path_sub};
}

std::vector<std::string> GetAllFiles(const std::string& dir, const std::string& pattern) {
    namespace fs = std::filesystem;
    std::vector<std::string> files;
    if (!fs::exists(dir) || !fs::is_directory(dir))
        return files;

    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            const std::string name = entry.path().filename().string();
            if (pattern.empty() || (name.size() >= pattern.size() && name.compare(name.size() - pattern.size(), pattern.size(), pattern) == 0)) {
                // files.push_back(name); // store only file name
                files.push_back(entry.path().string()); // store full path
            }
        }
    }
    return files;
}

std::vector<std::string> GetAllFiles(const std::vector<std::string>& dirs, const std::string& pattern) {
    std::vector<std::string> all_files;
    for (const auto& dir : dirs) {
        auto files = GetAllFiles(dir, pattern);
        all_files.insert(all_files.end(), files.begin(), files.end());
    }
    return all_files;
}

// std::vector<std::string> GetAllFiles(const std::string& dir, const std::string& pattern) {
//     std::vector<std::string> files;
//     DIR*                     dp = opendir(dir.c_str());
//     struct dirent*           dirp;
//     while ((dirp = readdir(dp)) != NULL) {
//         if (std::string(dirp->d_name) == "." || std::string(dirp->d_name) == "..") {
//             continue;
//         }
//         bool        ret = true;
//         std::string tmp = std::string(dirp->d_name);
//         if (pattern.size() > 0) {
//             if (tmp.size() < pattern.size()) {
//                 continue;
//             }
//             for (size_t i = 0; i < pattern.size(); i++) {
//                 size_t idx = pattern.size() - 1 - i;
//                 size_t idy = tmp.size() - 1 - i;
//                 if (tmp[idy] != pattern[idx]) {
//                     ret = false;
//                     break;
//                 }
//             }
//             if (!ret) {
//                 continue;
//             }
//         }
//         files.push_back(tmp);
//     }
//     closedir(dp);
//     return files;
// }

std::vector<std::string> Split(const std::string& s, const std::string& seperator) {
    std::vector<std::string> result;
    size_t                   i = 0;

    while (i != s.size()) {
        int flag = 0;
        while (i != s.size() && flag == 0) {
            flag = 1;
            for (size_t x = 0; x < seperator.size(); ++x)
                if (s[i] == seperator[x]) {
                    ++i;
                    flag = 0;
                    break;
                }
        }
        flag     = 0;
        size_t j = i;
        while (j != s.size() && flag == 0) {
            for (size_t x = 0; x < seperator.size(); ++x)
                if (s[j] == seperator[x]) {
                    flag = 1;
                    break;
                }
            if (flag == 0)
                ++j;
        }
        if (i != j) {
            result.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return result;
}

std::string Replace_all(const std::string& str, const std::string& old_value, const std::string& new_value) {
    std::string str_tmp = str;
    while (true) {
        std::string::size_type pos(0);
        if ((pos = str_tmp.find(old_value)) != std::string::npos)
            str_tmp.replace(pos, new_value.length(), new_value);
        else
            break;
    }
    return str_tmp;
}

std::string CombinePath(const std::vector<std::string>& paths) {
    namespace fs = std::filesystem;
    fs::path combined;
    for (const auto& p : paths) {
        combined /= p; // auto combine '/' target
    }
    return combined.string(); // return std::string types
}

std::string GetResourcePath(const std::string& res_folder, const std::string& res_type, const std::string& filename,
                            const std::string& dataset, bool ischeck) {
    namespace fs = std::filesystem;
    fs::path              base(res_folder);
    std::vector<fs::path> search_paths;

    if (dataset == "default") {
        // 1.add all private_* paths
        for (const auto& entry : fs::directory_iterator(base)) {
            if (entry.is_directory()) {
                const auto name = entry.path().filename().string();
                if (name.find("private_") == 0) {
                    if (filename.empty()) {
                        search_paths.emplace_back(entry.path() / dataset / "data" / res_type);
                    } else {
                        search_paths.emplace_back(entry.path() / dataset / "data" / res_type / filename);
                    }
                }
            }
        }
        // 2. add public path
        if (filename.empty()) {
            search_paths.emplace_back(base / res_type);
        } else {
            search_paths.emplace_back(base / res_type / filename);
        }
    } else if (dataset == "public") {
        // check public path
        if (filename.empty()) {
            search_paths.emplace_back(base / res_type);
        } else {
            search_paths.emplace_back(base / res_type / filename);
        }
    } else {
        // check private path
        if (filename.empty()) {
            search_paths.emplace_back(base / dataset / "data" / res_type);
        } else {
            search_paths.emplace_back(base / dataset / "data" / res_type / filename);
        }
    }

    if (!ischeck) {
        return search_paths.empty() ? "" : search_paths.front().string();
    }

    // chech whether the file exists in the search paths
    for (const auto& path : search_paths) {
        if (fs::exists(path)) {
            return path.string();
        }
    }

    return ""; // Not found
}

std::vector<std::string> GetResourceFolders(const std::string& res_folder, const std::string& res_type, const std::string& dataset, bool ischeck) {
    namespace fs = std::filesystem;
    fs::path                 base(res_folder);
    std::vector<std::string> result;

    if (dataset == "default") {
        // find all private_* folders
        for (const auto& entry : fs::directory_iterator(base)) {
            if (entry.is_directory()) {
                const std::string name = entry.path().filename().string();
                if (name.find("private_") == 0) {
                    fs::path target = entry.path() / res_type;
                    if (!ischeck || fs::exists(target)) {
                        result.push_back(target.string());
                    }
                }
            }
        }
        // find public folder
        fs::path public_path = base / res_type;
        if (!ischeck || fs::exists(public_path)) {
            result.push_back(public_path.string());
        }
    } else if (dataset == "public") {
        // only add public folders
        fs::path public_path = base / res_type;
        if (!ischeck || fs::exists(public_path)) {
            result.push_back(public_path.string());
        }
    } else {
        // find specific dataset folder
        fs::path private_path = base / dataset / res_type;
        if (!ischeck || fs::exists(private_path)) {
            result.push_back(private_path.string());
        }
    }

    return result;
}

bool IsExist(const std::string& filename) {
    int ret = access(filename.c_str(), 0);
    return ret == 0;
}
bool CreateFodler(const std::string& foldername) {
    if (!IsExist(foldername)) {
        std::string cmd = "mkdir -p " + foldername;
        int         ret = system(cmd.c_str());
        return ret == 0;
    } else {
        return true;
    }
}

bool DeleteFolder(const std::string& foldername) {
    if (IsExist(foldername)) {
        std::string cmd = "rm -rf " + foldername;
        int         ret = system(cmd.c_str());
        return ret == 0;
    } else {
        std::cout << foldername << " doesn't exist." << std::endl;
        return true;
    }
}

inline double GetTimerMS(time_point t1, time_point t2) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
}

inline double GetTimerUS(time_point t1, time_point t2) {
    return std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
}

// Timer
Timer::Timer() {
    st   = std::chrono::high_resolution_clock::now();
    last = st;
    now  = st;
}

Timer::~Timer() {}

void Timer::Start() {
    now  = std::chrono::high_resolution_clock::now();
    last = now;
}

double Timer::StopMS() {
    now         = std::chrono::high_resolution_clock::now();
    double dura = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
    last        = now;
    return dura;
}

double Timer::StopUS() {
    now         = std::chrono::high_resolution_clock::now();
    double dura = std::chrono::duration_cast<std::chrono::microseconds>(now - last).count();
    last        = now;
    return dura;
}

double Timer::GetRelativeTime() {
    time_point c = std::chrono::high_resolution_clock::now();
    return GetTimerMS(st, c);
}

double Timer::GetAbstractTime() {
    auto now                  = std::chrono::system_clock::now();
    auto duration_since_epoch = now.time_since_epoch();

    auto milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(duration_since_epoch).count();
    return milliseconds_since_epoch;
}

} // namespace cppt