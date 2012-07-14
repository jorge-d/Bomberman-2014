//
// BindHelper.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Sun May 29 06:51:07 2011 arnaud mesureur
//

#ifndef BIND_HELPER_HH_
#define BIND_HELPER_HH_

#include "gdl/Image.hpp"

namespace bomberman {
namespace gfx {

/**
 * The texture id
 */
typedef enum
{
    WALL,
    BOX,
    EMPTY,
    BAG,
    SPEED,
    RANGE,
    FLAME,
    IA,
    SCREENBOARD_BG,
    INTRO_MENU_BG,
    MAIN_MENU_BG,
    NEW_GAME_MENU_BG,
    PAUSE_MENU_BG,
    ENDGAME_MENU_BG,
    ARROW_MENU,
    FONT_TEXT,
    NONE
} bindable_type;

/**
 * Help to bind correctly.
 * This class avoid useless call to the bind call
 * if the correct texture is already binded.
 */
class BindHelper
{
public:
    /**
     * Bind the texture.
     * @param the texture.
     * @param the bindable id.
     */
    static void bind(gdl::Image& img, bindable_type);
    /**
     * Reset the current texture id to NONE
     */
    static void reset(void);

private:
    static bindable_type currentBind_;
};


}}

#endif  // BIND_HELPER_HH_
