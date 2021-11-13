#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "include/ScoreList.h"

int main() {

    ScoreList score_list("highscore.txt");
    score_list.loadFile();
    score_list.addEntry("John", 200);
    score_list.addEntry("John", 20);
    score_list.addEntry("John", 250);
    score_list.addEntry("John", 250);
    score_list.saveFile();

    return 0;
}