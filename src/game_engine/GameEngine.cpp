//
// GameEngine.cpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Wed May 11 17:08:42 2011 arnaud mesureur
//

#include <string>
#include "GameEngine.hh"
#include "Human.hh"
#include "ScanDir.hh"
#include "Computer.hh"
#include "Exception.hh"
#include "LoadMap.hh"
#include "SaveMap.hh"
#include "LoadSave.hh"

namespace bomberman
{
  GameEngine::GameEngine(Game* parent)
    : Engine(parent), menuStatus_(INTRODUCTION_SCENE), map_(NULL),
      cursorIndex_(0), timer_(0), reloadSave_(false), nickname_("AAAAA")
  {
    this->mptr_[INTRODUCTION_SCENE] = &GameEngine::handleIntroduction;
    this->mptr_[MAIN_MENU] = &GameEngine::handleMainMenu;
    this->mptr_[CHOOSE_MAP_1P] = &GameEngine::handleNewGame;
    this->mptr_[CHOOSE_MAP_2P] = &GameEngine::handleNewGame;
    this->mptr_[PLAYING] = &GameEngine::handlePlaying;
    this->mptr_[LOAD_GAME] = &GameEngine::handleLoadGame;
    this->mptr_[GAME_PAUSED] = &GameEngine::handlePausedGame;
    this->mptr_[PLAYER_1_WON] = &GameEngine::handleEndOfGame;
    this->mptr_[PLAYER_2_WON] = &GameEngine::handleEndOfGame;
    this->mptr_[IA_WON] = &GameEngine::handleLoosedGame;
    this->mptr_[DISPLAY_SCORES] = &GameEngine::handleDisplayScore;

    this->loadMenus();
  }

  GameEngine::~GameEngine(void)
  {
    if (this->map_)
      delete this->map_;
    this->deleteSaves();
    this->deleteMaps();
  }

  /*
  **      PUBLIC METHODS
  ** -> Getters and handlers
  */

  enum menu GameEngine::getMenuStatus(void) const
  {
    return this->menuStatus_;
  }

  Map *GameEngine::getMap(void) const
  {
    return this->map_;
  }

  const std::vector<ABombxml *> GameEngine::getMapList(void) const
  {
    return this->maplist_;
  }

  const std::list<score *>& GameEngine::getScoreList(void)
  {
    return this->score_.loadScores(false);
  }

  const std::vector<ABombxml *> GameEngine::getSavesList(void) const
  {
    return this->saveslist_;
  }

  const std::vector<std::string> GameEngine::getPauseMenuString(void) const
  {
    return this->pausemenu_;
  }

  const std::vector<std::string> GameEngine::getMainMenuString(void) const
  {
    return this->mainmenu_;
  }

  const std::string& GameEngine::getNickname(void) const
  {
    return this->nickname_;
  }

  unsigned int GameEngine::getCursor(void) const
  {
    return this->cursorIndex_;
  }

  float GameEngine::getElapsedTime(void) const
  {
    return this->clock_.getTotalElapsedTime();
  }

  AElement *GameEngine::recoverObjectAt(unsigned int x, unsigned int y) const
  {
    return this->map_->recoverObjectAt(x, y);
  }

  bool GameEngine::recoverPlayerAt(std::list<APlayer *>& tmp, unsigned int x, unsigned int y) const
  {
    return this->map_->recoverPlayerAt(tmp, x, y);
  }

  bool GameEngine::isKeyDown(gdl::Keys::Key k)
  {
    return this->parent_->getInput().isKeyDown(k);
  }

  void GameEngine::playSound(playable_id s)
  {
    this->soundEngine_->play(s);
  }

  void GameEngine::initialize(void)
  {
    srand(time(NULL));
  }

  void GameEngine::update(void)
  {
    std::map<enum menu, void (GameEngine::*)(void)>::iterator it = this->mptr_.find(this->menuStatus_);
    if (it != this->mptr_.end())
      (this->*(this->mptr_[this->menuStatus_]))();
  }

  void GameEngine::unload(void)
  {
  }

  void GameEngine::addObject(AElement *o) const
  {
    this->map_->addObject(o);
  }

  void GameEngine::addPlayer(APlayer *p) const
  {
    this->map_->addPlayer(p);
  }

  /*
  ** PRIVATE METHODS
  */

  void GameEngine::loadFromFile(bool savedGame)
  {
    try
      {
	if (savedGame)
	  this->map_ = new Map(this, this->saveslist_[this->cursorIndex_]);
	else
	  this->map_ = new Map(this, this->maplist_[this->cursorIndex_],
			       (this->menuStatus_ == CHOOSE_MAP_1P ? 1 : 2));
      }
    catch (const Exception& e)
      {
	std::cerr << "COULDN'T LOAD MAP: " << e.what() << std::endl;
	delete this->map_;
	this->map_ = NULL;
	return ;
      }
    this->startPlaying(true);
  }

  void GameEngine::deleteSaves(void)
  {
    for (std::vector<ABombxml *>::iterator it = this->saveslist_.begin(); it != this->saveslist_.end(); ++it)
      delete (*it);
    this->saveslist_.clear();
  }

  void GameEngine::deleteMaps(void)
  {
    for (std::vector<ABombxml *>::iterator it = this->maplist_.begin(); it != this->maplist_.end(); ++it)
      if (*it)
	delete (*it);
    this->maplist_.clear();
  }

  void GameEngine::loadMaps(void)
  {
    ScanDir scan("./maps/");
    std::vector<std::string> n;

    this->maplist_.push_back(NULL);
    if (scan.isOk() && scan.getFilesFromExtension(n, "xml"))
      for (std::vector<std::string>::iterator it = n.begin(); it != n.end(); ++it)
	{
	  ABombxml *m = new LoadMap((*it));

	  if (m->isOk())
	    this->maplist_.push_back(m);
   	  else
	    delete m;
	}
    std::cout << this->maplist_.size() - 1 << " maps loaded!" << std::endl;
  }

  void GameEngine::loadSaves(void)
  {
    ScanDir scan("./saves/");
    std::vector<std::string> n;

    if (scan.isOk() && scan.getFilesFromExtension(n, "xml"))
      for (std::vector<std::string>::iterator it = n.begin(); it != n.end(); ++it)
	{
	  ABombxml *m = new LoadSave((*it));

	  if (m->isOk())
	    this->saveslist_.push_back(m);
   	  else
	    delete m;
	}
    std::cout << this->saveslist_.size() << " saved games were loaded!" << std::endl;
  }

  void GameEngine::loadMenus(void)
  {
    this->loadMaps();

    this->loadSaves();

    this->mainmenu_.push_back(std::string("One Player"));
    this->mainmenu_.push_back(std::string("Two Players"));
    this->mainmenu_.push_back(std::string("Load"));
    this->mainmenu_.push_back(std::string("Scores"));
    this->mainmenu_.push_back(std::string("Exit Game"));

    this->pausemenu_.push_back(std::string("Resume"));
    this->pausemenu_.push_back(std::string("Save"));
    this->pausemenu_.push_back(std::string("Main menu"));
  }


  /*
  ** Various Private methods
  */

  void GameEngine::incCursor(void)
  {
    float t = this->parent_->getClock().getTotalGameTime();

    if (t - this->timer_ > Constants::MenuNavigationSpeed)
      {
	this->timer_ = t;
	this->cursorIndex_++;
      }
  }

  void GameEngine::decCursor(void)
  {
    float t = this->parent_->getClock().getTotalGameTime();

    if (t - this->timer_ > Constants::MenuNavigationSpeed)
      {
	this->timer_ = t;
	this->cursorIndex_--;
      }
  }

  bool GameEngine::validateSelection(void)
  {
    float t = this->parent_->getClock().getTotalGameTime();

    if (t - this->timer_ > Constants::MenuNavigationSpeed)
      {
	this->timer_ = t;
	return true;
      }
    return false;
  }

  void GameEngine::startPlaying(bool reset)
  {
    this->menuStatus_ = PLAYING;
    if (reset)
      this->clock_.reset();
    this->clock_.play();
    this->cursorIndex_ = 0;
  }

  void GameEngine::returnMainMenu(void)
  {
    if (this->map_)
      {
	delete this->map_;
	this->map_ = NULL;
      }
    this->cursorIndex_ = 0;
    this->menuStatus_ = MAIN_MENU;
  }

  bool GameEngine::navigateNickName(void)
  {
    float t;
    static float save;

    t = this->parent_->getClock().getTotalGameTime();
    if (t - save > Constants::NickNameMenuNavigationSpeed)
      {
	save = t;
	return true;
      }
    return false;
  }

  void GameEngine::changeLetter(bool up)
  {
    if (up)
      {
	if (this->nickname_[this->cursorIndex_] == 'A')
	  this->nickname_[this->cursorIndex_] = ' ';
	else if (this->nickname_[this->cursorIndex_] == ' ')
	  this->nickname_[this->cursorIndex_] = 'Z';
	else
	  this->nickname_[this->cursorIndex_] -= 1;
	return ;
      }
    if (this->nickname_[this->cursorIndex_] == 'Z')
      this->nickname_[this->cursorIndex_] = ' ';
    else if (this->nickname_[this->cursorIndex_] == ' ')
      this->nickname_[this->cursorIndex_] = 'A';
    else
      this->nickname_[this->cursorIndex_] += 1;
  }

  /*
  ** Method pointer handlers
  */

  void GameEngine::handleIntroduction(void)
  {
    /*
    ** Play something
    */
    if (this->isKeyDown(gdl::Keys::Return) && this->validateSelection())
      this->menuStatus_ = MAIN_MENU;
  }

  void GameEngine::handleMainMenu(void)
  {
    if (this->isKeyDown(gdl::Keys::Down) && this->cursorIndex_< (this->mainmenu_.size() - 1))
      this->incCursor();
    else if (this->isKeyDown(gdl::Keys::Up) && this->cursorIndex_ > 0)
      this->decCursor();
    if (this->isKeyDown(gdl::Keys::Return) && this->validateSelection())
      {
	gdl::Window w;

	switch (this->cursorIndex_)
	  {
	  case 0:
	    this->menuStatus_ = CHOOSE_MAP_1P;
	    break;
	  case 1:
	    this->menuStatus_ = CHOOSE_MAP_2P;
	    break;
	  case 2:
	    this->menuStatus_ = LOAD_GAME;
	    break;
	  case 3:
	    this->menuStatus_ = DISPLAY_SCORES;
	    break;
	  default:
	    w.close();
	  }
	this->cursorIndex_ = 0;
      }
  }


  void GameEngine::handleNewGame(void)
  {
    if (this->maplist_.size())
      {
	if (this->isKeyDown(gdl::Keys::Down) && this->cursorIndex_ < (this->maplist_.size() - 1))
	  this->incCursor();
	else if (this->isKeyDown(gdl::Keys::Up) && this->cursorIndex_ > 0)
	  this->decCursor();
	if (this->isKeyDown(gdl::Keys::Return) && this->validateSelection())
	  this->loadFromFile(false);
      }
    if (this->isKeyDown(gdl::Keys::Escape))
      this->returnMainMenu();
  }

  void GameEngine::handleLoadGame(void)
  {
    if (this->reloadSave_)
      {
	this->reloadSave_ = false;
	this->deleteSaves();
	this->loadSaves();
      }
    if (this->saveslist_.size())
      {
	if (this->isKeyDown(gdl::Keys::Down) && this->cursorIndex_ < (this->saveslist_.size() - 1))
	  this->incCursor();
	else if (this->isKeyDown(gdl::Keys::Up) && this->cursorIndex_ > 0)
	  this->decCursor();
	if (this->isKeyDown(gdl::Keys::Return) && this->validateSelection())
	  this->loadFromFile(true);
      }
    if (this->isKeyDown(gdl::Keys::Escape))
      this->returnMainMenu();
  }

  void GameEngine::handlePausedGame(void)
  {
    if (this->isKeyDown(gdl::Keys::Down) && this->cursorIndex_< (this->pausemenu_.size() - 1))
      this->incCursor();
    else if (this->isKeyDown(gdl::Keys::Up) && this->cursorIndex_ > 0)
      this->decCursor();

    if (this->isKeyDown(gdl::Keys::Return) && this->validateSelection())
      {
	if (this->cursorIndex_ == 0)
	  this->startPlaying(false);
	else if (this->cursorIndex_ == 1)
	  {
	    SaveMap l(*this->map_, "saves/save_" + NumberToString(this->saveslist_.size()) + ".xml");

	    if (l.isOk())
	      {
		this->reloadSave_ = true;
		std::cout << "GAME WAS CORRECTLY SAVED!" << std::endl;
	      }
	    else
	      std::cerr << "ERROR WHILE SAVING!" << std::endl;
	  }
	else
	  this->returnMainMenu();
      }
  }

  void GameEngine::handleEndOfGame(void)
  {
    if (this->isKeyDown(gdl::Keys::Right) && this->cursorIndex_ < (this->nickname_.size() - 1))
      this->incCursor();
    else if (this->isKeyDown(gdl::Keys::Left) && this->cursorIndex_ > 0)
      this->decCursor();

    if (this->isKeyDown(gdl::Keys::Up) && this->navigateNickName())
      this->changeLetter(true);
    else if (this->isKeyDown(gdl::Keys::Down) && this->navigateNickName())
      this->changeLetter(false);

    if (this->isKeyDown(gdl::Keys::Return) && this->validateSelection())
      {
	this->score_.saveScore(this->nickname_, (this->menuStatus_ == PLAYER_1_WON ?
						 this->map_->getPlayer(1)->getScore() :
						 this->map_->getPlayer(2)->getScore()));
	this->nickname_ = "AAAAA";
	this->returnMainMenu();
      }
  }

  void GameEngine::handleLoosedGame(void)
  {
    if (this->isKeyDown(gdl::Keys::Return) && this->validateSelection())
      this->returnMainMenu();
  }

  void GameEngine::handleDisplayScore(void)
  {
    if (this->isKeyDown(gdl::Keys::Escape))
      this->returnMainMenu();
  }

  void GameEngine::handlePlaying(void)
  {
    if (!this->isKeyDown(gdl::Keys::Escape))
      {
	this->clock_.update();
	this->map_->updatePlayers();
	this->map_->updateObjects();
	if ((this->menuStatus_ = this->map_->isFinished()) != PLAYING)
	  {
	    this->cursorIndex_ = 0;
	    this->clock_.pause();
	  }
      }
    else
      {
	this->menuStatus_ = GAME_PAUSED;
	this->cursorIndex_ = 0;
	this->clock_.pause();
      }
  }
}

