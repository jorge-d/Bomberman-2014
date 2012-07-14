#!/usr/bin/python
import markup
import sys
import random

class putter():
    def __init__(self, strm, x, y, nb_e, nb_pw, nb_bw):
        self.__f = open(strm, 'w+')
        self.__nb = int(nb_e)
        self.__x = int(x) 
        self.__y = int(y)
        self.__nb_pw = int(nb_pw)
        self.__nb_bw = int(nb_bw)
        self.__objects = []
        self.initMap(strm)
    def __del__(self):
         self.__f.close()
    def checkList(self, x, y):
     if  self.__objects.count( (x,y) ) > 0 : return False 
     self.__objects.append( (x,y) )
     return True
    def buildPlayers(self):
        i = 0
        players_x = []
        players_y = []
        while i <= self.__nb:
            x = random.randint(0,self.__x-1)
            y = random.randint(0,self.__y-1)
            if self.checkList(x, y):
                players_x.append(x)
                players_y.append(y)
            i = i + 1
        self.__mymap.players(nb=len(players_x))
        self.__mymap.player( x=players_x, y=players_y)
        self.__mymap.players.close()
    def buildBreakableWalls(self):
        bwalls_x = []
        bwalls_y = []
        i = 0
        while i < self.__nb_bw:
            x = random.randint(1,self.__x-2)
            y = random.randint(1,self.__y-2)
            if self.checkList(x, y):
                bwalls_x.append(x)
                bwalls_y.append(y)
            i = i + 1
        self.__mymap.bwalls()
        self.__mymap.bwall( x=bwalls_x, y=bwalls_y)
        self.__mymap.bwalls.close()
    def buildPermanentWalls(self):
        pwalls_x = []
        pwalls_y = []
        i = 0
        while i < self.__nb_pw:
            x = random.randint(1,self.__x-2)
            y = random.randint(1,self.__y-2)
            if self.checkList(x, y):
                pwalls_x.append(x)
                pwalls_y.append(y)
            i = i + 1
        self.__mymap.pwalls()
        self.__mymap.pwall( x=pwalls_x, y=pwalls_y)
        self.__mymap.pwalls.close()
    def writeMap(self):
        self.__f.write(str(self.__mymap))
    def initMap(self, strm):
        self.__mymap = markup.page( mode='xml',onetags=[ 'map', 'player', 'bwall', 'pwall'], twotags=[ 'players', 'bwalls', 'pwalls' ] )
        self.__mymap.init()
        self.__mymap.map(name=strm, x=self.__x, y=self.__y )
 
def usage():
    print "USAGE:\n==> [MANDATORY OPTION]: [-f/--filename: filename]\n==> [OTHER OPTIONS]:"
    print "[-r/--random]\t option random would be taken alone"
    print "You must set [-x, -y, -p/--players, -w/--pwalls, -b/bwalls] together"
    print "[-x: x]\t x option sets map width\n[-y: y]\t y option sets map height\n[-p/--players: players]\t p option sets number of players"
    print "[-w/--pwalls: walls]\t w option sets number of permanent walls\n[-b/--bwalls: boxes]\t b option sets number of breakable walls"
    sys.exit(2)

import getopt
def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "r|f:p:w:b:x:y:", ["random", "filename", "players", "pwalls", "bwalls"])
    except getopt.GetoptError, err:
        # print help information and exit:
        print str(err) # will print something like "option -a not recognized"
        usage()
        sys.exit(2)
    rand = False
    filename = None
    nb_p = None
    nb_wall =None
    nb_box = None
    y = random.randint(10, 50)
    x = y
    for o, a in opts:
        if o == "-r":
            rand = True
        elif o in ("-f", "--filename"):
            filename = a
        elif o == "-x":
            x = a
        elif o == "-y":
            y = a
        elif o in ("-p", "--players"):
            nb_p  = a
        elif o in ("-w", "--pwalls"):
            nb_wall = a
        elif o in ("-b", "--bwalls"):
            nb_box = a 
    if (rand == False and (not nb_p or not nb_wall or not nb_box)) or not filename:
        usage()
    elif rand == True:
        nb_p = random.randint(2,x/10)
        nb_box = random.randint(10,x*y/4)
        nb_wall = random.randint(3,x)

    put = putter(filename, x, y, nb_p, nb_wall, nb_box)
    put.buildPlayers()
    put.buildPermanentWalls()
    put.buildBreakableWalls()
    put.writeMap()
       

if __name__ == "__main__":
    main()

