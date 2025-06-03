#include "../application.h"
#include <iostream>

/**
 * Retrieves a texture from the cache or loads it from disk if not cached
 * @param path Path to the texture file
 * @return Reference to the cached texture
 */
sf::Texture& UI::getTexture(const std::string& path)
{
    // Check if texture already loaded
    auto it = textureCache.find(path);
    if (it == textureCache.end()) {
        // Texture not found, load it
        sf::Texture newTexture;
        if (!newTexture.loadFromFile(path)) {
            std::cerr << "Warning: Failed to load texture: " << path << std::endl;
        }
        auto result = textureCache.emplace(path, std::move(newTexture));
        return result.first->second;
    }
    
    // Return cached texture
    return it->second;
}

/**
 * Creates a button with standard properties
 * @param x X position of the button
 * @param y Y position of the button
 * @param width Width of the button
 * @param height Height of the button
 * @param text Text displayed on the button
 * @param state State to transition to when button is clicked
 * @param texturePath Path to button texture
 * @return Pointer to the newly created button
 */
std::unique_ptr<Button> UI::createStandardButton(int x, int y, int width, int height, const std::string& text,
                                 const std::string& texturePath)
{
    std::unique_ptr<Button> button = std::make_unique<Button>(x, y, width, height);
    if (!text.empty()) {
        button->setText(text);
    }
    if (!texturePath.empty()) {
        button->setTexture(texturePath);
    }
    return std::move(button);
}

/**
 * Helper method to calculate center X coordinate based on width
 */
int UI::centerX(int width) const
{
    if (!application) {
        return 0;
    }
    return (application->window_width / 2) - (width / 2);
}

/**
 * Helper method to calculate center Y coordinate based on height
 */
int UI::centerY(int height) const
{
    if (!application) {
        return 0;
    }
    return (application->window_height / 2) - (height / 2);
}