#pragma once

#include <fstream>
#include <print>
#include <vector>
#include <filesystem>
#include <expected>
#include <map>
#include <format>

namespace short_names {
    using std::string;
    using std::vector;
    using std::map;
    using std::println;
    using std::print;
    using std::expected;
    using std::unexpected;
    using std::format;
    namespace fs = std::filesystem;
}

namespace io {
    inline std::expected<bool, std::string>
    printFileContents(std::string filename) {
        if (!std::filesystem::exists(filename)) {
            return std::unexpected("Filename does not exist");
        }

        std::ifstream file(filename);
        if (!file.is_open()) {
            return std::unexpected("File could not be opened");
        }

        std::string line;
        while (std::getline(file, line)) {
            std::println("{}", line);
        }

        return true;
    }

    inline std::expected<std::string, std::string>
    readFileToString(std::string filename) {
        if (!std::filesystem::exists(filename)) {
            return std::unexpected("Filename does not exist");
        }

        std::ifstream file(filename);
        if (!file.is_open()) {
            return std::unexpected("File could not be opened");
        }

        std::string line;
        std::string contents;

        while (std::getline(file, line)) {
            contents += (line + "\n");
        }

        if (!contents.empty() && contents.back() == '\n') {
            contents.pop_back();
        }

        return contents;
    }

    inline std::expected<std::vector<std::string>, std::string>
    readFileToVector(std::string filename) {
        if (!std::filesystem::exists(filename)) {
            return std::unexpected("Filename does not exist");
        }

        std::ifstream file(filename);
        if (!file.is_open()) {
            return std::unexpected("File could not be opened");
        }

        std::string line;
        std::vector<std::string> contents;

        while (std::getline(file, line)) {
            contents.push_back(line);
        }

        return contents;
    }

    inline std::expected<std::filesystem::path, std::string>
    getCurrentDirectory() {
        try {
            std::filesystem::path cwd = std::filesystem::current_path();
            return cwd;
        } catch (const std::filesystem::filesystem_error &e) {
            std::string error = e.what();
            return error;
        }
    }

    inline std::filesystem::path
    combine(std::filesystem::path first, std::filesystem::path second) {
        return first / second;
    }

    inline std::string
    trim(const std::string &str) {
        unsigned long first = str.find_first_not_of(" \t\n\r\f\v");
        if (std::string::npos == first) {
            return str;
        }

        unsigned long last = str.find_last_not_of(" \t\n\r\f\v");
        return str.substr(first, (last - first + 1));
    }

    inline std::expected<std::map<std::string, std::string>, std::string>
    loadEnv(const std::string &filename = ".env") {
        if (!std::filesystem::exists(filename)) {
            return std::unexpected("Filename does not exist");
        }

        std::map<std::string, std::string> env_vars;

        std::ifstream file(filename);
        if (!file.is_open()) {
            return std::unexpected("Error: Could not open .env file");
        }
    
        std::string line;
        while (std::getline(file, line)) {
            line = trim(line);
            if (line.empty() || line[0] == '#') {
                continue;
            }
    
            unsigned long equals_pos = line.find('=');
            if (equals_pos == std::string::npos) {
                std::unexpected(
                    std::format(
                        "Warning: Skipping malformed line in .env: {}", line
                    )
                );
            }
    
            std::string key = trim(line.substr(0, equals_pos));
            std::string value = trim(line.substr(equals_pos + 1));
    
            if (!value.empty()) {
                if (
                    (value.front() == '\'' && value.back() == '\'')
                    || (value.front() == '"' && value.back() == '"')
                ) {
                    value = value.substr(1, value.length() - 2);
                }
            }
    
            env_vars[key] = value;
        }
    
        file.close();
        return env_vars;
    }
}
