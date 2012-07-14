//
// LoadHelper.hpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 09:27:15 2011 arnaud mesureur
//

#ifndef LOAD_HELPER_HPP_
#define LOAD_HELPER_HPP_

#include <cstdlib>
#include <iostream>

#include <gdl/Image.hpp>
#include <gdl/Model.hpp>

/**
 * Provide a safe way to load images staticly
 */
template<typename T>
T loadHelper(char const* filename)
{
    try
    {
        return T::load(filename);
    }
    catch (...)
    {
      std::cerr << "Can't load resources : " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
}

#endif  // LOAD_HELPER_HPP_
