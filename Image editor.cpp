#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define Print(x) std::cout << x << std::endl

void grayscalePicture(sf::Image image);
void blurryPicture(sf::Image image);
void loadImageFromPath(sf::Image&, std::string&);

int main()
{
	Print("Welcome to Image editor!" << std::endl);
	Print("First thing you should do is paste your image into console and press ENTER:");

	std::string imagePath;
	std::cin >> imagePath;

	sf::Image image;
	loadImageFromPath(image, imagePath);

	int option = -1;
	while (option != 0)
	{
		Print("1) Grayscale picture");
		Print("2) Get a blurry picture");
		Print("3) Change image path");
		Print("0) Exit app" << std::endl);

		std::cin >> option;

		switch (option) {
		case 1:
			grayscalePicture(image);
			break;
		case 2:
			blurryPicture(image);
			break;
		case 3:
			Print("Enter new image path:");
			std::cin >> imagePath;
			loadImageFromPath(image, imagePath);
		}
	}
}

void loadImageFromPath(sf::Image& image, std::string& imagePath)
{
	while (true)
	{
		if (image.loadFromFile(imagePath)) {
			Print(std::endl << "Image is successfully loaded, now choose what option you want:");
			break;
		}
		else {
			Print(std::endl << "Image failed to load, try again");
			std::cin >> imagePath;
		}
	}
}

void grayscalePicture(sf::Image image)
{
	sf::RenderWindow window(sf::VideoMode(image.getSize().x, image.getSize().y), "Image Editor - Black and White");
	sf::Texture texture;
	sf::Sprite sprite;
	
	for (int i = 0; i < image.getSize().x; i++) {
		for (int j = 0; j < image.getSize().y; j++) 
		{
			sf::Color color = image.getPixel(i, j);
			int avg = (color.r + color.g + color.b) / 3;
			image.setPixel(i, j, sf::Color(avg, avg, avg));
		}
	}

	texture.loadFromImage(image);
	sprite.setTexture(texture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	
		window.clear();
		window.draw(sprite);
		window.display();
	}
}

void blurryPicture(sf::Image image)
{
	sf::RenderWindow window(sf::VideoMode(image.getSize().x, image.getSize().y), "Image Editor - Blury picture");
	sf::Texture texture;
	sf::Sprite sprite;

	for (int i = 0; i < image.getSize().x; i++) {
		for (int j = 0; j < image.getSize().y; j++)
		{

			sf::Color color = image.getPixel(i, j);
			sf::Color colors[9];

			if (i == 0) {
				colors[0] = sf::Color::White;
				colors[1] = sf::Color::White;
				colors[2] = sf::Color::White;
			}

			if (j == 0) {
				colors[0] = sf::Color::White;
				colors[3] = sf::Color::White;
				colors[6] = sf::Color::White;
			}
			
			if (i == image.getSize().x - 1) {
				colors[6] = sf::Color::White;
				colors[7] = sf::Color::White;
				colors[8] = sf::Color::White;
			}
			
			if (j == image.getSize().y - 1) {
				colors[2] = sf::Color::White;
				colors[5] = sf::Color::White;
				colors[8] = sf::Color::White;
			}

			for (int k = 0; k < 9; k++) 
			{
				if (colors[0] != sf::Color::White) {
					colors[0] = image.getPixel(i - 1, j - 1);
				}
				if (colors[1] != sf::Color::White) {
					colors[1] = image.getPixel(i - 1, j);
				}
				if (colors[2] != sf::Color::White) {
					colors[2] = image.getPixel(i - 1, j + 1);
				}
				if (colors[3] != sf::Color::White) {
					colors[3] = image.getPixel(i, j - 1);
				}
				if (colors[4] != sf::Color::White) {
					colors[4] = image.getPixel(i, j);
				}
				if (colors[5] != sf::Color::White) {
					colors[5] = image.getPixel(i, j + 1);
				}
				if (colors[6] != sf::Color::White) {
					colors[6] = image.getPixel(i + 1, j - 1);
				}
				if (colors[7] != sf::Color::White) {
					colors[7] = image.getPixel(i + 1, j);
				}
				if (colors[8] != sf::Color::White) {
					colors[8] = image.getPixel(i + 1, j + 1);
				}
			}

			int red, green, blue;
			for (int k = 0; k < 9; k++) {
				red += colors[k].r;
				green += colors[k].g;
				blue += colors[k].b;
			}

			red /= 9;
			green /= 9;
			blue /= 9;
			
			image.setPixel(i, j, sf::Color(red, green, blue));
		}
	}

	texture.loadFromImage(image);
	sprite.setTexture(texture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}
}


