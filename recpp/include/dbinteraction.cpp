#include "dbinteraction.h"
#include "cookbook.h"


dbInteraction::dbInteraction(){

}

dbInteraction::~dbInteraction(){

}

QString dbInteraction::getDbName(){
    return this->dbName;
}

bool dbInteraction::dbAccessible(){
    this->rc = sqlite3_open(dbName, &this->db);
    if (rc){
        return false;
    } else {
        return true;
    }
}

Cookbook dbInteraction::loadCookbook(){
    if (this->dbAccessible()){
        this->sql = "SELECT * FROM RECIPES;";
        return parseSqlToCookbook(this->sql);
    }
}

Cookbook dbInteraction::parseSqlToCookbook(QString sqlReturn){
    Cookbook *cb = new Cookbook;
    QString name = "";
    QString descr = "";
    QString comm = "";
    QString fileName = "";
    int nOfRec = 0;
    std::vector<Recipe*> recipes;

    // parse the sql statement


    cb->setName(name);
    cb->setDescription(descr);
    cb->setComment(comm);
    cb->set


    //cb->setName()
}
