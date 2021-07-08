#include <stdio.h>
#include <time.h>
#include "GameController.h"
#include <windows.h>

class Tower
{
private:
	Texture texture;

public:
	void SetDefaultValues(const char path[], float _scaleX, float _scaleY);
	
	Sprite towerDown;
	Sprite towerUp;

	float height;
	float weight;

	float scaleX;
	float scaleY;

	sf::Vector2f position;

	bool moving;
};

const int WEIGHT = 1500;
const int HEIGHT = 1000;

sf::RenderWindow window(sf::VideoMode(WEIGHT, HEIGHT), "Flappy Bird");

void PhysicMoving(Object2D* person, float boostDown, float v_up, float dt, float *vy);
void PhysicKick(float v_up, float *vy);

int Rand(int min, int max);

void ControllTowers(Tower towers[], int count, float distance, int* firstTower, float dt, float vy);

bool CheckCollision(Object2D* person, Tower* tower);

int main()
{
	srand(time(NULL));
	
	Object2D bird;

	bird.AddAnim("птичка кадры\\bird.png", "fly", 3);
	bird.SetScale(0.3, 0.3);
	bird.SetPosition(50, 350);
	
	bird.weight = bird.scale.x * 250;
	bird.height = bird.scale.y * 175;

	float boostFall  = 0.002;
	float velocityUp = 0.55;

	float vy_bird = 0;

	const int countTowers = 4;
	Tower towers[countTowers];

	int firstTower = 0;
	float vy_tower = 0.45;

	for (int i = 0; i < countTowers; i++)
	{
		towers[i].SetDefaultValues("Tower.png", 0.7, 0.7);

		towers[i].position.x = WEIGHT;
		towers[i].position.y = Rand(HEIGHT - (int)towers[i].height, HEIGHT - 120);
	}

	towers[firstTower].moving = true;

	sf::Clock clock;

	bool isGameOver = false;

	while (window.isOpen())
	{
		float dt = clock.getElapsedTime().asMicroseconds(); 
		dt /= 1000;
		clock.restart();
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
		}

		if (!isGameOver)
		{
			window.clear({ 255, 255, 255 });

			bird.Animate("fly", 100, window);
			PhysicMoving(&bird, boostFall, velocityUp, dt, &vy_bird);

			ControllTowers(towers, countTowers, 500, &firstTower, dt, vy_tower);

			isGameOver = CheckCollision(&bird, &towers[firstTower]);

			window.display();
		}
	}
}

void PhysicMoving(Object2D *person, float boostDown, float v_up, float dt, float *vy)
{
	float x = person->position.x;
	float y = person->position.y;

	PhysicKick(v_up, vy);

	(*vy) += boostDown * dt;

	y += (*vy) * dt;

	person->Move(x, y);
}

void PhysicKick(float v_up, float *vy)
{
	static bool isSpace = 0;

	if (GetAsyncKeyState(VK_SPACE) && isSpace == 0)
	{
		(*vy)  = 0;
		(*vy) -= v_up;

		isSpace = 1;
	}

	if (!GetAsyncKeyState(VK_SPACE)) isSpace = 0;
}

void Tower::SetDefaultValues(const char path[], float _scaleX, float _scaleY)
{
	texture.loadFromFile(path);

	sf::Vector2u size = texture.getSize();

	towerUp.  setTexture(texture);
	towerDown.setTexture(texture);

	scaleX = _scaleX;
	scaleY = _scaleY;

	towerUp.  setScale(scaleX, -scaleY);
	towerDown.setScale(scaleX,  scaleY);
	
	height = size.y * scaleY;
	weight = size.x * scaleX;

	moving = false;
}

int Rand(int min, int max)
{
	return (rand() % (max - min + 1) + min);
}

void ControllTowers(Tower towers[], int count, float distance, int *firstTower, float dt, float vy)
{
	static int lastTower = 0;

	for (int i = 0; i < count; i++)
	{
		if (towers[i].moving)
		{
			float posX = towers[i].position.x;
			float posY = towers[i].position.y;

			towers[i].towerUp.  setPosition(posX, posY - 270);
			towers[i].towerDown.setPosition(posX, posY);

			posX -= vy * dt;

			towers[i].position.x = posX;

			window.draw(towers[i].towerUp);
			window.draw(towers[i].towerDown);
		}
	}

	if (WEIGHT - (towers[lastTower].position.x + towers[lastTower].weight) >= distance)
	{
		if (lastTower == count - 1) lastTower = 0;
		else                        lastTower++;

		towers[lastTower].position.x = WEIGHT;
		towers[lastTower].moving = true;

		towers[lastTower].position.y = Rand(HEIGHT - (int)towers[lastTower].height, HEIGHT - 120);
	}

	if (towers[*firstTower].position.x + towers[*firstTower].weight <= 0)
	{
		if (*firstTower == count - 1) (*firstTower) = 0;
		else                          (*firstTower)++;
	}
}

bool CheckCollision(Object2D *person, Tower *tower)
{
	bool collision = 0;

	if      (person->position.y < 0)                       person->position.y = 0;
	else if (person->position.y + person->height > HEIGHT) person->position.y = HEIGHT - person->height;

	if (person->position.y                  <= tower->towerUp.  getPosition().y ||
		person->position.y + person->height >= tower->towerDown.getPosition().y)
	{
		if (person->position.x + person->weight >= tower->position.x &&
			person->position.x                  <= tower->position.x + tower->weight)
		{
			collision = 1;
		}
	}

	return collision;
}
