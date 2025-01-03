#include "BarleyPhoto.h"
#include <SFML/Graphics.hpp>

void BarleyPhoto::LoadSprite(std::string photoPathWay)
{
	/*if (!texture.loadFromFile(photoPathWay, sf::IntRect()))
	{
		//Debug or Exit
	}*/

	//sf::Image image;

	image.loadFromFile(photoPathWay);
	texture.loadFromImage(image, sf::IntRect());

	texture.setSmooth(true);
	sf::Sprite sprite(texture);
	barleySprite = sprite;

    if (photoAlphaSetting == ALPHA_ZERO)
    {
        sf::Color spriteColor = barleySprite.getColor();
        spriteColor.a = 0;

        barleySprite.setColor(spriteColor);
    }
}

void BarleyPhoto::SetSpritePosition(sf::Vector2f panelPositionDirections)
{
	_barleyPhotoClock.restart().asSeconds();
	sf::Vector2f updateSpritePosition = barleySprite.getPosition();
	updateSpritePosition.x = updateSpritePosition.x + panelPositionDirections.x;
	updateSpritePosition.y = updateSpritePosition.y + panelPositionDirections.y;
	barleySprite.setPosition(updateSpritePosition);
}

//Things to do tomorrow 11/26/2024
	//-figure out dissolve on a timer
	//-figure out the whole shader thing (That would be super cool)

void BarleyPhoto::BarleyPhotoFader(double deltaTime, float fadeTime)
{
    if (photoAlphaSetting == ALPHA_FADE_IN)
    {
        float alpha = (deltaTime / fadeTime) * 255.0f;

        if (alpha > 255.0f) 
        {
            alpha = 255.0f;
            photoAlphaSetting = FULL_ALPHA;
        }

        sf::Color color = barleySprite.getColor();
        color.a = static_cast<sf::Uint8>(alpha);
        barleySprite.setColor(color);
    }
    else if (photoAlphaSetting == ALPHA_FADE_OUT)
    {
        float alpha = (deltaTime / fadeTime) * 255.0f;

        if (alpha <= 0)
        {
            alpha = 0;
            photoAlphaSetting = ALPHA_ZERO;
        }

        sf::Color color = barleySprite.getColor();
        color.a = static_cast<sf::Uint8>(255.0f - alpha);
        barleySprite.setColor(color);
    }
}


/*#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Dissolve Effect");

    // Load the photo texture
    sf::Texture photoTexture;
    if (!photoTexture.loadFromFile("photo.png")) {
        return -1; // Handle error
    }

    // Load the dissolve mask texture
    sf::Texture maskTexture;
    if (!maskTexture.loadFromFile("dissolve_mask.png")) {
        return -1; // Handle error
    }

    // Create a sprite for the photo
    sf::Sprite photoSprite(photoTexture);

    // Load the shader
    sf::Shader dissolveShader;
    if (!dissolveShader.loadFromFile("dissolve_shader.frag", sf::Shader::Fragment)) {
        return -1; // Handle error
    }

    // Set shader textures
    dissolveShader.setUniform("photo", photoTexture);
    dissolveShader.setUniform("mask", maskTexture);

    // Uniform for dissolve progress (0.0 = full photo, 1.0 = fully dissolved)
    float dissolveProgress = 0.0f;

    // Clock for timing
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update dissolve progress
        float deltaTime = clock.restart().asSeconds();
        dissolveProgress += deltaTime * 0.1f; // Adjust speed as needed
        if (dissolveProgress > 1.0f) dissolveProgress = 1.0f;

        dissolveShader.setUniform("progress", dissolveProgress);

        // Clear, draw, and display
        window.clear(sf::Color::Black);
        window.draw(photoSprite, &dissolveShader);
        window.display();
    }

    return 0;
}

Save this GLSL shader as dissolve_shader.frag:

glsl
Copy code
uniform sampler2D photo;
uniform sampler2D mask;
uniform float progress;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec4 photoColor = texture2D(photo, uv);
    float maskValue = texture2D(mask, uv).r; // Use red channel for mask
    float threshold = progress;

    // Apply dissolve
    if (maskValue < threshold) {
        discard; // Make transparent
    }

    gl_FragColor = photoColor;
}
*/
