#include "PathFinder.h"
#include <iostream>

std::filesystem::path PathFinder::s_resourceDirectory;

std::filesystem::path PathFinder::findProjectRoot(const std::filesystem::path& startPath)
{
    auto currentPath = startPath;

    while (currentPath.has_parent_path() && !std::filesystem::exists(currentPath / "resources"))
    {
        currentPath = currentPath.parent_path();
    }

    if (std::filesystem::exists(currentPath / "resources"))
        return currentPath;

    throw std::runtime_error("Could not find resources directory in parent directories");
}

void PathFinder::initialize(const std::string& executablePath)
{
    std::filesystem::path execPath(executablePath);
    auto projectRoot = findProjectRoot(execPath.parent_path());
    s_resourceDirectory = projectRoot / "resources";
}

//std::string PathFinder::getResourcePath(const std::string& relativePath)
//{
//    std::string fullPath = (PathFinder::s_resourceDirectory / relativePath).string();
//    std::cout << "Loading resource: " << fullPath << std::endl; // Debug
//    return fullPath;
//}

std::string PathFinder::getResourcePath(const std::string& relativePath)
{
    std::string fullPath = "C:/Src/Mini-Studio-JapMyth/resources/" + relativePath;

    // Remplace tous les '\' par '/'
    std::replace(fullPath.begin(), fullPath.end(), '\\', '/');

    std::cout << "PathFinder::getResourcePath - Chemin corrigé: " << fullPath << std::endl;
    return fullPath;
}