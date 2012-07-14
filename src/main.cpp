//
// main.cpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Wed May 11 14:43:55 2011 arnaud mesureur
//

#include <cstdlib>
#include <exception>
#include <string>
#include "GraphicsEngine.hh"
#include "Game.hh"

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        std::string opt(argv[1]);
        if (opt == "--fullscreen")
            bomberman::fullscreen = true;
    }
    try
    {
        bomberman::Game game;
        game.run();
    }
    catch (const std::bad_alloc&)
    {
        std::cerr << "Virtual memory exhausted" << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) // wtf, gdl doesn't throw only std::exception
    {
        std::cerr << "Can't load resources" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
