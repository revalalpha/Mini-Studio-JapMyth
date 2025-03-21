//#pragma once
//
//#include <SFML/Graphics.hpp>
//#include <string>
//#include <unordered_map>
//#include <memory>
//
//class TextureManager
//{
//public:
//    static TextureManager& getInstance()
//    {
//        static TextureManager instance;
//        return instance;
//    }
//
//    TextureManager(const TextureManager&) = delete;
//    TextureManager& operator=(const TextureManager&) = delete;
//
//    void initialize();
//    void cleanup();
//
//    bool loadTexture(const std::string& name, const std::string& filename);
//
//    sf::Texture* getTexture(const std::string& name);
//
//    void removeTexture(const std::string& name);
//
//    bool hasTexture(const std::string& name) const;
//
//    sf::Vector2u getTextureDimensions(const std::string& name) const;
//
//    bool loadTexturesFromDirectory(const std::string& directory, const std::string& pattern = "*");
//
//    std::vector<std::string> getLoadedTextureNames() const;
//    void loadAllGameTextures();
//
//private:
//    TextureManager();
//    ~TextureManager();
//
//    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
//    bool m_initialized;
//};

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