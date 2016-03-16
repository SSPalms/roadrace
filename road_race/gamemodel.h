#ifndef GAMEMODEL_
#define GAMEMODEL_

#include <string>
#include <vector>

#include <QTimer>

#include "square.h"
#include "gamefile.h"
#include "player.h"

#include "utils.h"

using namespace std;

// This is a way to keep track of information and rules about specific resources.
struct Resource {
    std::string name, shortName;
    int value;
    Resource(string name_, string shortName_, int value_): name(name_), shortName(shortName_), value(value_) {}
};

//the actual game model
class Game{

  private:
    vector<vector<Square*>> squares;
    vector<Resource*> resource_types;
    //for singleton if needed
    GameFileManager *loader;
    string id;
    string alias;
    string password;
    int round_num;
    vector<Player*> player_list;
    int width, height;

   Game();
  public:
    bool applyCommand( std::string command );
    bool save();
    string load();
    void update();

    //moar singleton functionality
private:
    static Game* instance_;

public:
    static Game& instance();
    void setGameLoader ( GameFileManager * gfm );

    ~Game();

    GameFileManager *getGameLoader () { return loader; }

    void updateResources();

    //getters n setters

    vector<Resource*> getResources() { return resource_types; }
    Resource *getResource ( string shortName );
    vector<vector<Square*>> getSquares() { return squares; }
    Square *getSquare ( int x, int y) { return squares[x][y]; }
    Square *getSquare ( int id );
    vector<Square*> getPlayerSquares ( Player *owner );
    string getId() { return id; }
    string getAlias() { return alias; }
    string getPassword() { return password; }
    int getRoundNum() { return round_num; }
    vector<Player*> getPlayerList() { return player_list; }
    Player *getPlayer ( std::string name);
    int getWidth() { return width; }
    int getHeight() { return height; }

    void setResources ( vector<Resource*> vr );
    void addResource ( Resource * r ) { resource_types.push_back(r); }
    void setSquares ( vector<vector<Square*>> sq );
    void setSquare ( Square * sq, int x, int y ) { delete squares[x][y]; squares[x][y] = sq; }
    void setId ( string _id ) { id = _id; }
    void setAlias ( string a ) { alias = a; }
    void setPassword ( string p ) { password = p; }
    void setRoundNum ( int rn ) { round_num = rn; }
    void setPlayerList ( vector<Player*> pl ) { player_list = pl; }
    void setWidth ( int w ) { width = w; }
    void setHeight ( int h ) { height = h; }

};

class Updater {
private:
    QTimer *timer;
    Updater() {}
    static Updater *instance_;

public:
    static Updater &instance();

    void start();
    void stop();

    ~Updater () { delete instance_; }
};

// implement a command structure
class Command{
public:
    virtual bool execute()=0;

};
//fortress/road construction
class buildCommand: public Command{
private:
    int id;
public:
    buildCommand(int newId){
        id = newId;
    }

    bool execute();
};
//when a square is unmade
class destroyCommand: public Command{
private:
    int id;
public:
    destroyCommand(int newId){
        id = newId;
    }
    bool execute();
};
//gathering resources
class resourceCommand: public Command{
private:
    int resources;
    int squareid;
    int playerId;
public:
    resourceCommand(int id1,int id2){
        squareid = id1;
        playerId = id2;
    }
    bool execute();
    int get();
    int store();
};
//creating dragons
class dragonCommand: public Command{
private:
    int playerId;
    int x;
    int y;
    int hp;
    bool status;
public:
    dragonCommand(int sendId){
        playerId = sendId;
    }
    bool execute();
    bool die();
    bool damage();
};
//for random events
class eventHandler{
    private:
    string type;
    string image;
    int length;
public:
    virtual bool execute() = 0;
};

#endif // GAMEMODEL_
