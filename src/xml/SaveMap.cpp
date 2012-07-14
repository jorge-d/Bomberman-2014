#include "SaveMap.hh"

namespace bomberman
{

  int SaveMap::v = 0;

  SaveMap::SaveMap(Map const &m, std::string const &n) :name(n), map_(m), height(m.getHeight() - 2), width(m.getWidth() - 2)
  {
    this->smap_[BREAKABLE_WALL] = &SaveMap::fillBWall;
    this->smap_[PERMANENT_WALL] = &SaveMap::fillPWall;

    this->smap_[RANGE_BONUS] = &SaveMap::fillBonus;
    this->smap_[SPEED_BONUS] = &SaveMap::fillBonus;
    this->smap_[BAG_BONUS] = &SaveMap::fillBonus;

    mapToXml();
    WriteInXml(n);
  }

  SaveMap::~SaveMap(void)
  {
  }

  void SaveMap::fillBWall(AElement* e, int x, int y)
  {
    TiXmlElement *element;

    (void)e;
    element = new TiXmlElement("bwall");
    element->SetAttribute("x", x);
    element->SetAttribute("y", y);
    this->bwlist_.push_back(element);
  }

  void SaveMap::fillPWall(AElement* e, int x, int y)
  {
    TiXmlElement *element;

    (void)e;
    element = new TiXmlElement("pwall");
    element->SetAttribute("x", x);
    element->SetAttribute("y", y);
    this->pwlist_.push_back(element);
  }

  void SaveMap::fillBonus(AElement* e, int x, int y)
  {
    TiXmlElement *element;

    element = new TiXmlElement("bonus");
    element->SetAttribute("x", x);
    element->SetAttribute("y", y);
    element->SetAttribute("type", e->getType());
    this->blist_.push_back(element);
  }

  void  SaveMap::fillPlayer(std::list<APlayer *> &p)
  {
    TiXmlElement *element;
    std::list<APlayer *>::iterator itb = p.begin();
    std::list<APlayer *>::iterator ite = p.end();

    for( ; itb != ite; ++itb)
      {
	element = new TiXmlElement("player");
	element->SetAttribute("x", (*itb)->getRealPosX() - 1);
	element->SetAttribute("y", (*itb)->getRealPosY() - 1);
	element->SetAttribute("type", (*itb)->getType() == HUMAN ? static_cast<int>(HUMAN) : static_cast<int>(IA));
	element->SetAttribute("bombRange",((*itb)->getRange()));
	element->SetDoubleAttribute("speed", static_cast<double>((*itb)->getSpeed()));
	const gdl::Color &color = (*itb)->getColor();
	element->SetAttribute("color_a", color.a);
	element->SetAttribute("color_r", color.r);
	element->SetAttribute("color_g", color.g);
	element->SetAttribute("color_b", color.b);
	element->SetAttribute("score", (*itb)->getScore());
	element->SetAttribute("bag", (*itb)->getBag());
	this->plist_.push_back(element);
      }
    p.clear();
  }

  bool SaveMap::isOk(void) const
  {
    return (this->ok);
  }

  void SaveMap::linkPlayers()
  {
    TiXmlElement *element;

    element = new TiXmlElement("players");
    element->SetAttribute("nb", this->plist_.size());
    std::list<TiXmlElement*>::iterator itb = this->plist_.begin();
    std::list<TiXmlElement*>::iterator ite = this->plist_.end();
    unsigned int i = 0;
    for( ; itb != ite; ++itb)
      {
	element->LinkEndChild(*itb);
	++i;
      }
    if (i > 0)
    this->doc.LinkEndChild(element);
  }


  void SaveMap::link(const std::string &s, std::list<TiXmlElement*>  &list_)
  {
    TiXmlElement *element;

    element = new TiXmlElement(s.c_str());
    std::list<TiXmlElement*>::iterator itb = list_.begin();
    std::list<TiXmlElement*>::iterator ite = list_.end();
    unsigned int i = 0;
    for( ; itb != ite; ++itb)
      {
	element->LinkEndChild(*itb);
	++i;
      }
    if (i > 0)
    this->doc.LinkEndChild(element);
  }

  void SaveMap::WriteInXml(std::string const &filename)
  {
    TiXmlElement *element;
    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
    if (decl == NULL)
      {
	std::cerr << "Could not declare xml" << std::endl;
	this->ok = false;
      }
    this->doc.LinkEndChild( decl );
    element = new TiXmlElement("map");
    element->SetAttribute("x", this->map_.getWidth());
    element->SetAttribute("y", this->map_.getHeight());
    element->SetAttribute("name", this->name.c_str());
    this->doc.LinkEndChild(element);
    linkPlayers();
    link("pwalls", this->pwlist_);
    link("bwalls", this->bwlist_);
    link("bonuses", this->blist_);
    if (this->doc.SaveFile(filename.c_str()))
      this->ok = true;
    else
      {
	std::cerr << "Could not save xml file" << std::endl;
	this->ok = false;
      }
  }

  void SaveMap::mapToXml()
  {
    std::list<APlayer *> p;
    AElement *t;
    std::map<elemType, SaveMap::ptr>::iterator it;

    for (unsigned y = 1; y <= this->height; y++)
      {
	for (unsigned x = 1; x <= this->width; x++)
	  {
	    if ((t = this->map_.recoverObjectAt(x, y)))
	      {
		if ((it =this->smap_.find(t->getType())) != this->smap_.end())
		  (this->*(it->second))(t, x - 1, y - 1);
	      }
	    else if (this->map_.recoverPlayerAt(p, x, y))
	      fillPlayer(p);
	  }

      }
  }
}
