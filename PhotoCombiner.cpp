#include "PhotoCombiner.h"
#include <SFML/Graphics.hpp>

#include "PhotoWindow.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <filesystem>
#include <SFML/Window.hpp>
#include "PhotoCombiner.h"

std::string PhotoCombiner::BlendTwoPhotos(BarleyPhoto& firstPhoto, BarleyPhoto& secondPhoto, std::string pathToSave)
{
	sf::Image firstPhotoImage = firstPhoto.image;
	sf::Vector2u firstPhotoSize = firstPhotoImage.getSize();

	sf::Texture secondPhotoTexture = secondPhoto.texture;
	sf::Vector2u secondPhotoSize = secondPhotoTexture.getSize();
	sf::Image secondPhotoImage = secondPhotoTexture.copyToImage();

	sf::Uint8* PanelPixels = new sf::Uint8[(firstPhotoSize.x + secondPhotoSize.x) * (firstPhotoSize.y + secondPhotoSize.y) * 4];

	int PanelPixelsCount = 0;

	for (int i = 0; i < firstPhotoSize.y; i++)
	{
		for (int j = 0; j < firstPhotoSize.x; j++)
		{
			sf::Color firstColor = firstPhotoImage.getPixel(j, i);
			PanelPixels[PanelPixelsCount] = firstColor.r;
			PanelPixels[PanelPixelsCount + 1] = firstColor.g;
			PanelPixels[PanelPixelsCount + 2] = firstColor.b;
			PanelPixels[PanelPixelsCount + 3] = firstColor.a;
			PanelPixelsCount = PanelPixelsCount + 4;

			sf::Color secondColor = secondPhotoImage.getPixel(j, i);
			PanelPixels[PanelPixelsCount] = secondColor.r;
			PanelPixels[PanelPixelsCount + 1] = secondColor.g;
			PanelPixels[PanelPixelsCount + 2] = secondColor.b;
			PanelPixels[PanelPixelsCount + 3] = secondColor.a;
			PanelPixelsCount = PanelPixelsCount + 4;
		}
	}

	
	sf::Texture blendedPhotoTexture;
	blendedPhotoTexture.create(firstPhotoSize.x + secondPhotoSize.x, firstPhotoSize.y);
	blendedPhotoTexture.update(PanelPixels);
	sf::Image image2 = blendedPhotoTexture.copyToImage();
	bool soWhat = image2.saveToFile(pathToSave);
	return pathToSave;
}

