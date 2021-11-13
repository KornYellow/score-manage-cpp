#include <iostream>

#include "include/ScoreList.h"

int main() {

    ScoreList score_list("highscore.txt");
    score_list.loadFile();

    score_list.addEntry("Korn", 32);
    score_list.addEntry("Bomb", 22);
    score_list.addEntry("Sunny", 95);
    score_list.addEntry("Dan", 7);
    score_list.addEntry("Bomb", 65);
    score_list.addEntry("Dan", 7);

    score_list.printEntry();

    score_list.saveFile();
    return 0;
}