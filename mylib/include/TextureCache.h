#pragma once

#include <string>
#include <vector>

namespace sf
{
    class Texture;
}

/**
 * @class TextureCache
 * @brief Manages texture storage and loading to prevent unnecessary reloading.
 */
class TextureCache {
public:
    /**
     * @brief Constructor for TextureCache.
     * @param execFilePath The execution file path used to locate resources.
     */
    TextureCache(const std::string& execFilePath);

    /**
     * @brief Retrieves a texture from the cache or loads it if not already cached.
     * @param filename The name of the texture file.
     * @return Reference to the loaded texture.
     */
    sf::Texture& GetTexture(const std::string& filename);

    /**
     * @brief Destructor for TextureCache.
     */
    ~TextureCache();

private:
    /**
     * @struct TextureInfo
     * @brief Stores information about a loaded texture.
     */
    struct TextureInfo {
        sf::Texture* texture;  ///< Pointer to the loaded texture.
        std::string path;      ///< File path of the texture.
    };

    /**
     * @brief Converts a relative file path into an absolute path.
     * @param filename The relative path of the file.
     * @return The absolute file path.
     */
    std::string GetAbsoluteFilepath(const std::string& filename);

    std::vector<TextureInfo> m_allTextureInfos; ///< Stores all loaded textures.
    std::string m_execFilePath; ///< Stores the execution file path.
};