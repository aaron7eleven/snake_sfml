#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "Game.h"
#include "Wall.h"
#include "Item.h"


Game::Game() :
    snake(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT) / 2.0f, GRID_SIZE),
    item(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT) / 4.0f, GRID_SIZE),
    gameOverUI(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT)),
    mainMenuUI(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT))
{   
    // Works with default origin (0,0) (Top Left)
    //Wall wall_top(sf::Vector2f(GRID_SIZE / 2.0f, GRID_SIZE / 2.0f), sf::Vector2f(VIEW_WIDTH - GRID_SIZE, GRID_SIZE));
    //Wall wall_bottom(sf::Vector2f(GRID_SIZE / 2.0f, VIEW_WIDTH - 1.5f * GRID_SIZE), sf::Vector2f(VIEW_WIDTH - GRID_SIZE, GRID_SIZE));

    //Wall wall_left(sf::Vector2f(GRID_SIZE / 2.0f, GRID_SIZE / 2.0f), sf::Vector2f(GRID_SIZE, VIEW_HEIGHT - GRID_SIZE));
    //Wall wall_right(sf::Vector2f(VIEW_HEIGHT - 1.5f * GRID_SIZE, GRID_SIZE / 2.0f), sf::Vector2f(GRID_SIZE, VIEW_HEIGHT - GRID_SIZE));

    // Works with origin in center of wall
    Wall wall_top   (sf::Vector2f(VIEW_WIDTH / 2.0f         , GRID_SIZE),               sf::Vector2f(VIEW_WIDTH - GRID_SIZE , GRID_SIZE));
    Wall wall_bottom(sf::Vector2f(VIEW_WIDTH / 2.0f         , VIEW_HEIGHT - GRID_SIZE), sf::Vector2f(VIEW_WIDTH - GRID_SIZE , GRID_SIZE));
    Wall wall_left  (sf::Vector2f(GRID_SIZE                 , VIEW_WIDTH / 2.0f),       sf::Vector2f(GRID_SIZE              , VIEW_HEIGHT - GRID_SIZE));
    Wall wall_right (sf::Vector2f(VIEW_HEIGHT - GRID_SIZE   , VIEW_WIDTH / 2.0f),       sf::Vector2f(GRID_SIZE              , VIEW_HEIGHT - GRID_SIZE));

    walls.push_back(wall_top);
    walls.push_back(wall_bottom);
    walls.push_back(wall_left);
    walls.push_back(wall_right);
    

    // Old but Working GameOver UI
    //font.loadFromFile("./Assets/Font/PressStart2P-Regular.ttf");
    //gameOverText.setFont(font);
    //gameOverText.setString("Game Over\n\nScore = XXX\n\nR = Restart");
    //gameOverText.setCharacterSize(24);
    //
    //sf::FloatRect textRect = gameOverText.getLocalBounds();

    //gameOverText.setOrigin(textRect.left + textRect.width/ 2.0f, textRect.top + textRect.height / 2.0f);
    //gameOverText.setPosition(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT) / 2.0f);


    std::string hitAppleSoundFilename = "./Assets/Sound/hit_apple.wav";
    std::string gameOverSoundFilename = "./Assets/Sound/game_over.wav";
    soundHolder.AddSound("hitApple", hitAppleSoundFilename);
    soundHolder.AddSound("gameOver", gameOverSoundFilename);
}

Game::~Game()
{
}

void Game::LateInit() {
    std::string snakeFilename = "./Assets/Art/snake_body_small.png";
    textureHolder.AddTexture("snakeTexture", snakeFilename);
    snake.SetTexture(textureHolder.GetTexture("snakeTexture"));
    snake.SetTextureToBody();

    music.openFromFile("./Assets/Sound/background_music.wav");
    music.setLoop(true);
    //music.play();


}

void Game::Update(float deltaTime) {
    snake.Update(deltaTime);
    Gameplay();
}


void Game::Draw(sf::RenderWindow& window) {

    if (isMainMenu) {
        UpdateMainMenuUI();
        mainMenuUI.Draw(window);
    } else if (!isGameOver) {
       for (Wall wall : walls) {
           wall.Draw(window);
       }

       item.Draw(window);
       snake.Draw(window);
   }
   else {
       UpdateGameOverUI();
       //window.draw(gameOverText);
       gameOverUI.Draw(window);
   }
}

void Game::Run() {

    float deltaTime = 0.0f;
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake", sf::Style::Default);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    LateInit();

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                //cout << "Resizing";
                break;
            }
        }

        Update(deltaTime);
        window.clear();
        Draw(window);
        window.display();
    }
}

void Game::Gameplay() {
    
    if (isMainMenu) {
        // Moving Down
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
            isHardMode = false;
            isGameOver = false;
            isMainMenu = false;
            
            RestartGame();

            sound.setBuffer(*soundHolder.GetSound("hitApple"));
            sound.play();
            music.play();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
            isHardMode = true;
            isGameOver = false;
            isMainMenu = false;
            RestartGame();

            sound.setBuffer(*soundHolder.GetSound("hitApple"));
            sound.play();
            music.play();
            
        }

    } else if (!isGameOver) {
        // Check if Snake hit walls
        for (Wall wall : walls) {
            if (snake.CheckCollison(wall.GetWall())) {
                std::cout << "Hit Wall -> Game Over" << std::endl;
                isGameOver = true;
                music.stop();
                sound.setBuffer(*soundHolder.GetSound("gameOver"));
                sound.play();
                
            }
        }

        // Check if Snake hit itself
        std::vector<sf::RectangleShape> snakeBody = snake.GetSnakeBody();

        for (int i = 1; i < snakeBody.size(); i++) {
            if (snake.CheckCollison(snakeBody[i])) {
                std::cout << "Hit Self -> Game Over" << std::endl;
                isGameOver = true;
                music.stop();
                sound.setBuffer(*soundHolder.GetSound("gameOver"));
                sound.play();
            }
        }

        // Check if Snake hit item
        if (snake.CheckCollison(item.GetItem())) {
            std::cout << "Hit Apple -> Grow" << std::endl;
            float randX = (float(rand() % 28 + 2) * GRID_SIZE);
            float randY = (float(rand() % 28 + 2) * GRID_SIZE);
            item = Item(sf::Vector2f(randX, randY), GRID_SIZE);
            snake.Grow();
            sound.setBuffer(*soundHolder.GetSound("hitApple"));
            sound.play();
        }

    }
    else {
        // Moving Down
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            RestartGame();
            isGameOver = false;
            isMainMenu = false;
            sound.setBuffer(*soundHolder.GetSound("hitApple"));
            sound.play();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            //RestartGame();
            isGameOver = false;
            isMainMenu = true;
            sound.setBuffer(*soundHolder.GetSound("hitApple"));
            sound.play();
        }
    }
}

void Game::UpdateGameOverUI() {
    std::string text = " Game Over ";
    std::string restartText = "R to Restart";
    std::string mainMenuText = "M to Main Menu";
    int snakeLength = snake.Length();
    std::string scoreText = " Score = " + std::to_string(snakeLength);
    std::string finalGameOverText = text + "\n\n" + scoreText + "\n\n" + restartText;
    std::string gameOvertextWithScore = text + "\n\n" + scoreText;
    //gameOverText.setString(text + "\n\n" + scoreText + "\n\n" + restartText);

    gameOverUI.SetText(0, gameOvertextWithScore);
    gameOverUI.SetText(1, restartText);
    gameOverUI.SetText(2, mainMenuText);
    gameOverUI.CenterText();
}

void Game::UpdateMainMenuUI() {
    std::string titleText = "    Snake    \n\n Created by \naaron7eleven";
    std::string easyText = "N for Normal Mode";
    std::string hardText = "H for Hard Mode";

    mainMenuUI.SetText(0, titleText);
    mainMenuUI.SetText(1, easyText);
    mainMenuUI.SetText(2, hardText);
    mainMenuUI.CenterText();
}

void Game::RestartGame() {
    
    snake = Snake(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT) / 2.0f, GRID_SIZE);
    snake.SetTexture(textureHolder.GetTexture("snakeTexture"));
    snake.SetTextureToBody();
    
    if(isHardMode)
        snake.SetMoveTime(snake.GetMoveTime() / 2.0f);

    music.play();
    item = Item(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT) / 4.0f, GRID_SIZE);
}

