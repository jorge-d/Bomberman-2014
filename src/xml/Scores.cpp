#include <time.h>
#include "Scores.hh"
#include "Exception.hh"

namespace bomberman
{
  Scores::Scores()
    : doc_("scores.xml"), is_good_(true)
  {}

  Scores::~Scores()
  {
    std::list<score *>::iterator it;
    std::list<score *>::iterator end = this->l_.end();

    for (it = this->l_.begin(); it != end; it++)
      delete *it;
  }

  bool sort_scores(score *f, score *s)
  {
    return (f->score > s->score);
  }

  void Scores::saveScore(std::string const & name, int s)
  {
    TiXmlDeclaration *decl = new TiXmlDeclaration( "1.0", "", "" );
    TiXmlElement *scor = new TiXmlElement("score");
    TiXmlElement *scores;
    std::list<score *> l;
    time_t rawtime;
    char date[512];
    struct tm *t;

    time(&rawtime);
    t = localtime(&rawtime);
    strftime(date, 512, "%F", t);
    l = this->loadScores(false);
    if (l.empty())
      scores = new TiXmlElement("scores");
    else
      scores = this->doc_.FirstChildElement("scores");
    if (scores == NULL)
      {
	this->is_good_ = false;
	return ;
      }
    scor->SetAttribute("id", name.c_str());
    scor->SetAttribute("value", s);
    scor->SetAttribute("date", date);
    scores->LinkEndChild(scor);
    this->doc_.LinkEndChild(decl);
    this->doc_.LinkEndChild(scores);
    if (!this->doc_.SaveFile())
      throw Exception(this->doc_.ErrorDesc());
  }

  /*
  ** PENSER A VIRER LE THROW
  */

  std::list<score *> const & Scores::loadScores(bool gen_exc)
  {
    TiXmlElement *scores;
    TiXmlElement *sc;
    score *tmp;

    while (!this->l_.empty())
      {
	delete this->l_.front();
	this->l_.pop_front();
      }
    if (this->is_good_ == false)
      return this->l_;
    if (!this->doc_.LoadFile())
      {
	if (gen_exc)
	  throw Exception(this->doc_.ErrorDesc());
	else
	  return this->l_;
      }
    scores = this->doc_.FirstChildElement("scores");
    if (scores == NULL)
      {
	this->is_good_ = false;
	return this->l_;
      }
    sc = scores->FirstChildElement();
    while (sc)
      {
       	tmp = new score;
	if (sc->Attribute("id"))
	  tmp->name = sc->Attribute("id");
	if (sc->Attribute("date"))
	  tmp->date = sc->Attribute("date");
	sc->QueryIntAttribute("value", &tmp->score);
	tmp->name = sc->Attribute("id");
	this->l_.push_back(tmp);
       	sc = sc->NextSiblingElement();
      }
    this->l_.sort(sort_scores);
    return this->l_;
  }
}
