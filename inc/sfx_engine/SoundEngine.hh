//
// SoundEngine.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Wed May 11 17:15:26 2011 arnaud mesureur
//

#ifndef	SOUND_ENGINE_HH_
#define	SOUND_ENGINE_HH_

#include <map>

#include <SFML/Audio.hpp>
#include "Engine.hh"

namespace bomberman {

typedef enum
{
    EXPLOSION,
    BREAK_BOX,
    POWER_UP,
    MENU,
    GAME,
    INTRO,
    BLANK
} playable_id;

/**
 * The Sound engine.
 * @see Engine
 */
class SoundEngine : public Engine
{
public:
    SoundEngine(Game*);
    ~SoundEngine(void);

    void initialize(void);
    void update(void);
    void unload(void);

    void play(playable_id);
    void stop(playable_id);

private:
    std::map<playable_id, sf::Music*> playlist_;
    playable_id currentTrack_;

//////////////////////////////////////////
/// Not implemented
//////////////////////////////////////////
private:
    SoundEngine(SoundEngine const&);
    SoundEngine& operator=(Engine const&);
};

}

#endif	// SOUND_ENGINE_HH_
