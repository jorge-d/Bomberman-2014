//
// DisplayLists.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Sun May 29 06:51:07 2011 arnaud mesureur
//

#ifndef DISPLAY_LISTS_HH_
#define DISPLAY_LISTS_HH_

#include <GL/gl.h>
#include <GL/glu.h>

#include <map>
#include <queue>

#include "IPrimitive.hh"

namespace bomberman {
namespace gfx {

/**
 * Display id type.
 * Enumeration of all type of display that
 * can be managed by the open GL display lists
 * through the DisplayLists class.
 */
typedef enum
{
    TCUBE,
    TRECT,
    CSPLIT,
    TBACKG
} display_id;

/**
 * The Display lists.
 * A wrapper on the openGL display lists.
 * This class is a singleton.
 */
class DisplayLists
{
//////////////////////////////////////////
/// Public members
//////////////////////////////////////////
public:
    /**
     * The instance getter.
     * @return The single instance of the DisplayLists class.
     */
    static DisplayLists& getInstance(void);
    /**
     * Kill the instance.
     */
    void destroyInstance(void);

    /**
     * Create a list.
     * It creates a new list to display bind to an id.
     * @param the display id.
     * @param the primitive object to display.
     */
    void createList(display_id id, IPrimitive* p);
    /**
     * Call a display list.
     * @param the display id of the list to call.
     */
    void call(display_id id) const;
    /**
     * Overload of the "[]" operator.
     * @see DisplayLists::call.
     * @param the display id of the list to call.
     */
    void operator[](display_id id) const;

//////////////////////////////////////////
/// Private members
//////////////////////////////////////////
private:
    static DisplayLists* instance_;
    std::map<display_id, GLuint> handles_;
    std::queue<IPrimitive*> list_;

private:
    DisplayLists(void);
    ~DisplayLists(void);

private:
    void addToList(IPrimitive*);
    GLuint genList(void);

//////////////////////////////////////////
/// Not implemented
//////////////////////////////////////////
private:
    DisplayLists(DisplayLists const&);
    DisplayLists& operator=(DisplayLists const&);
};

}}

#endif  // DISPLAY_LISTS_HH_
