#ifndef SCORES_HH_
# define SCORES_HH_

# include <string>
# include <list>
# include "tinyxml.h"

namespace bomberman
{
  struct score
  {
    std::string name;
    std::string date;
    int score;
  };

  class Scores
  {
  private:
    TiXmlDocument doc_;
    std::list<score *> l_;
    bool is_good_;

  public:
    Scores();
    ~Scores();
    void saveScore(std::string const & name, int score);
    std::list<score *> const & loadScores(bool gen_exc = true);
  };
}

#endif //SCORES_HH_
