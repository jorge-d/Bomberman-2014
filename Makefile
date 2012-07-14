##
## Makefile for bomberman in /home/mesure_a/workspace
##
## Made by arnaud mesureur
## Login   <mesure_a@epitech.net>
##
## Started on  Tue May  3 16:53:28 2011 arnaud mesureur
##

#
# GNU Makefile (use gmake)
#

# \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
#		*** VARIABLES ***
# //////////////////////////////////////////////////

SHELL	=	/bin/sh

##########################################
### Directories & Path
##########################################

SRCDIR	=	src
HDRDIR	=	inc
OBJDIR	=	obj

GAME_ENGINE	=	game_engine
ELEMENTS	=	elements

GFX_ENGINE	=	gfx_engine
DRAWABLES	=	drawables
PRIMITIVES	=	primitives
MENU		=	menu

SFX_ENGINE	=	sfx_engine

OTHERS		=	others

XML		=	xml
TINYXML		=	tinyxml

VPATH	=	 $(SRCDIR)				\
		:$(SRCDIR)/$(GAME_ENGINE)		\
		:$(SRCDIR)/$(GAME_ENGINE)/$(ELEMENTS)	\
		:$(SRCDIR)/$(GFX_ENGINE)		\
		:$(SRCDIR)/$(GFX_ENGINE)/$(DRAWABLES)	\
		:$(SRCDIR)/$(GFX_ENGINE)/$(MENU)	\
		:$(SRCDIR)/$(GFX_ENGINE)/$(PRIMITIVES)	\
		:$(SRCDIR)/$(SFX_ENGINE)		\
		:$(SRCDIR)/$(OTHERS)			\
		:$(SRCDIR)/$(XML)			\
		:$(SRCDIR)/$(XML)/$(TINYXML)


##########################################
### Compiler configurations
##########################################

CXX		=	$(if $(CLG), clang++, g++)
CXXFLAGS	+=	-Wall -Wextra -pipe
CXXFLAGS	+=	$(INCLUDE)
CXXFLAGS	+=	$(if $(XF), $(XFLAGS),)
CXXFLAGS	+=	$(if $(DF), $(DFLAGS), $(OFLAGS))

# includes
INCLUDE	=	-I. -I$(HDRDIR)
INCLUDE +=	-I$(HDRDIR)/$(GAME_ENGINE)
INCLUDE	+=	-I$(HDRDIR)/$(GAME_ENGINE)/$(ELEMENTS)
INCLUDE +=	-I$(HDRDIR)/$(GFX_ENGINE)
INCLUDE	+=	-I$(HDRDIR)/$(GFX_ENGINE)/$(DRAWABLES)
INCLUDE	+=	-I$(HDRDIR)/$(GFX_ENGINE)/$(MENU)
INCLUDE	+=	-I$(HDRDIR)/$(GFX_ENGINE)/$(PRIMITIVES)
INCLUDE +=	-I$(HDRDIR)/$(SFX_ENGINE)
INCLUDE +=	-I$(HDRDIR)/$(OTHERS)
INCLUDE +=	-I$(HDRDIR)/$(XML)
INCLUDE +=	-I$(HDRDIR)/$(XML)/$(TINYXML)
INCLUDE +=	-I$(HDRDIR)/gdl
INCLUDE +=      -I/usr/X11/lib

# libraries
LDFLAGS	=	-framework OpenGL -lm
LDFLAGS	+=	-Lgdl/lib -lgdl_gl -Wl,-rpath=./gdl/lib -llua
LDFLAGS	+=	-lsfml-audio

# debug flags activated w/ DF on otherwise
# optimization is on by default (OF)
DFLAGS	+=	-ggdb -DDEBUG_
OFLAGS	+=	-O2

##########################################
### Sources
##########################################

EXEC	=	bomberman
SRCS	=	main.cpp		\
		Game.cpp		\
		Engine.cpp		\
		$(GAME_SRCS)		\
		$(GFX_SRCS)		\
		$(SOUND_SRCS)		\
		$(OTHER_SRCS)		\
		$(XML_SRCS)

OBJS	=	$(SRCS:%.cpp=$(OBJDIR)/%.o)

GAME_SRCS	=	GameEngine.cpp		\
			Map.cpp			\
			APlayer.cpp		\
			Flame.cpp		\
			Human.cpp		\
			Computer.cpp		\
			Bomb.cpp		\
			AElement.cpp		\
			BreakableWall.cpp	\
			PermanentWall.cpp	\
			SpeedBonus.cpp		\
			RangeBonus.cpp		\
			BagBonus.cpp

# Main gfx
GFX_SRCS	=	GraphicsEngine.cpp	\
			DisplayLists.cpp	\
			Vector3f.cpp		\
			Camera.cpp		\
			ScreenBoard.cpp		\
			Square.cpp
# Primitives gfx
GFX_SRCS	+=	TRect.cpp		\
			TCube.cpp		\
			CSplit.cpp		\
			TBackG.cpp
# Drawables gfx
GFX_SRCS	+=	DrawableFactory.cpp	\
			GWall.cpp		\
			GPlayer.cpp		\
			GBomb.cpp		\
			GEmpty.cpp		\
			GBox.cpp		\
			GFlame.cpp		\
			GRangeBx.cpp		\
			GBagBx.cpp		\
			GSpeedBx.cpp		\
			BindHelper.cpp

# Menus
GFX_SRCS	+=	Menu.cpp		\
			String.cpp		\
			IntroSceneMenu.cpp	\
			MainMenu.cpp		\
			NewGameMenu.cpp		\
			PauseMenu.cpp		\
			ScoreMenu.cpp		\
			LoadMenu.cpp		\
			WinMenu.cpp		\
			LooseMenu.cpp

SOUND_SRCS	=	SoundEngine.cpp

OTHER_SRCS	=	ScanDir.cpp		\
			Exception.cpp		\
			LuaBind.cpp		\
			LuaException.cpp

XML_SRCS	=	ABombxml.cpp		\

#Save
XML_SRCS	+=	SaveMap.cpp		\

#load
XML_SRCS	+=	LoadMap.cpp		\
			LoadSave.cpp		\

# TinyXml
XML_SRCS	+=	tinystr.cpp		\
			tinyxml.cpp		\
			tinyxmlerror.cpp	\
			tinyxmlparser.cpp

# Scores
XML_SRCS	+=	Scores.cpp

##########################################
### Tools
##########################################

TAR		=	tar czf
PRINTF          =	/usr/bin/printf
END		=	\033[m
GREEN		=	\033[32m
RED		=	\033[31m


# \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
#		*** RULES ***
# ////////////////////////////////////////

all		: $(EXEC)

$(EXEC)		: $(OBJS)
		@$(CXX) -o $(EXEC) $(OBJS) $(LDFLAGS)
		@$(PRINTF) "$(GREEN)[OK]$(END) $@ successfully linked\n"

clean		:
		@$(RM) $(OBJS)
		@ $(PRINTF) "$(RED)[OK]$(END) CLEAN $(EXEC) - objs\n"

fclean		: clean
		@$(RM) $(EXEC)
		@$(PRINTF) "$(RED)[OK]$(END) FCLEAN $(EXEC)\n"

re		: fclean all

tarball		: fclean
		@$(TAR)  $(EXEC).tar.gz $(SRCDIR) $(HDRDIR) $(OBJDIR) Makefile
		@$(PRINTF) "$(RED)[OK]$(END) tarball created: $(EXEC).tar.gz\n"

.SUFFIXES	:
.SUFFIXES	: .cpp .o

$(OBJDIR)/%.o	: %.cpp
		@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<
		@$(PRINTF) "$(GREEN)[OK]$(END) --> $< \n"

.PHONY		: all clean fclean re tarball
