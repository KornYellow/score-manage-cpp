# ScoreList

A library to help you save high score by sorting high to low score

- [ScoreList](#scorelist)
  - [Examples](#examples)
  - [Usage](#usage)
  - [Methods](#methods)
    - [`Score(std::string, int);`](#scorestdstring-int)
    - [`ScoreList(std::string);`](#scoreliststdstring)

## Examples

Making game that easily save high score by

``` cpp
#include <iostream>
#include "ScoreList.h"

int main() {

    ScoreList score_list("highscore.txt");
    score_list.loadFile();

    std::string user_name;
    std::cout << "Enter name : ";
    std::getline(std::cin, user_name);

    int user_score;
    std::cout << "Enter score : ";
    std::cin >> user_score;

    score_list.addEntry(user_name, user_score);

    score_list.saveFile();
    return 0;
}
```

Test 1: by saving Korn and score 23

``` console
Output :
- Load entry(s) failed, file or data not found.
Enter name : Korn
Enter score : 23
- Added 'Korn' with a score of 23 points.
- Saved 1 entry(s) to 'highscore.txt' successfully.
```

Test 2: by saving John and score 55

``` console
Output :
- Loaded 1 entry(s) from 'highscore.txt' successfully!
Enter name : John
Enter score : 55
- Added 'John' entry with a score of 55 points.
- Saved 2 entry(s) to 'highscore.txt' successfully.
```

Test 3: by saving Korn and score 60

``` console
Output :
- Loaded 2 entry(s) from 'highscore.txt' successfully!
Enter name : Korn
Enter score : 60
- Updated 'Korn' with a score of 60 points.
- Saved 2 entry(s) to 'highscore.txt' successfully.
```

highscore.txt

```
Korn
60
John
55
```

<br>

If you have other object you can send pointer of `ScoreList` to that object

``` cpp
#include <iostream>

#include "ScoreList.h"

class Game {
private:
    ScoreList* score_list;
public:
    Game(ScoreList* score_list) {

        this->score_list = score_list;
    }
    void getScore() {

        std::string user_name;
        std::cout << "Enter name : ";
        std::getline(std::cin, user_name);

        int user_score;
        std::cout << "Enter score : ";
        std::cin >> user_score;

        this->score_list->addEntry(user_name, user_score);
    }
};

int main() {

    ScoreList score_list("highscore.txt");
    score_list.loadFile();

    Game game(&score_list);
    game.getScore();

    score_list.saveFile();
    return 0;
}
```

``` console
Output :
- Load entry(s) failed, file or data not found.
Enter name : Korn
Enter score : 23
- Added 'Korn' with a score of 23 points.
- Saved 1 entry(s) to 'highscore.txt' successfully.
```

<br>

If you saved different score or name the system will work it all out

``` cpp
#include <iostream>

#include "ScoreList.h"

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
```

``` console
Output :
- Load entry(s) failed, file or data not found.
- Added 'Korn' with a score of 32 points.
- Added 'Bomb' with a score of 22 points.
- Added 'Sunny' entry with a score of 95 points.
- Added 'Dan' with a score of 7 points.
- Updated 'Bomb' with a score of 65 points.
- Failed to add 'Dan' entry, found duplicate name and score.
*== highscore.txt ============*
 - 1  Sunny     95
 - 2  Bomb      65
 - 3  Korn      32
 - 4  Dan       7
*=============================*
- Saved 4 entry(s) to 'highscore.txt' successfully.
```

## Usage

Make an object `ScoreList` and put file name for high score in constructor and you can try to make an object `Score` with name and score in the constructor 

``` cpp
ScoreList score_list("highscore.txt");
Score score("Korn", 54);
score_list.addEntry(score);
```

``` console
Output :
- Added 'Korn' with a score of 54 points.
```
<br>

put the score in using `addEntry(Score(name, score));`
You can print the entries out by using `printEntry();`

``` cpp
ScoreList score_list("highscore.txt");
score_list.addEntry("Korn", 54);
score_list.addEntry("Jenny", 18);
score_list.printEntry();
```

``` console
Output :
- Added 'Korn' with a score of 54 points.
- Added 'Jenny' with a score of 18 points.
*== highscore.txt ============*
 - 1  Korn      54
 - 2  Jenny     18
*=============================*
```
<br>

You must use `saveFile();` to save the score to a file

``` cpp
ScoreList score_list("highscore.txt");
score_list.addEntry("Korn", 54);
score_list.addEntry("Jenny", 18);
score_list.printEntry();
score_list.saveFile();
```

``` console
Output :
- Added 'Korn' with a score of 54 points.
- Added 'Jenny' with a score of 18 points.
*== highscore.txt ============*
 - 1  Korn      54
 - 2  Jenny     18
*=============================*
- Saved 2 entry(s) to 'highscore.txt' successfully.
```
<br>

and use `loadFile();` to load your saved file and let's try to print the entries again

``` cpp
ScoreList score_list("highscore.txt");
score_list.loadFile();
score_list.printEntry();
```

``` console
Output :
- Loaded 2 entry(s) from 'highscore.txt' successfully!
*== highscore.txt ============*
 - 1  Korn      54
 - 2  Jenny     18
*=============================*
```
<br>

When the data is loaded you can add more entry as you like 
- If added name is the same but the score is less than before **the new score will not be save**
- If added name is the same but the score is more than before **the new score will be save**
- If added name is the same and the score is the same **the process will be ignored**

``` cpp
ScoreList score_list("highscore.txt");
score_list.loadFile();
score_list.addEntry("John", 200);
score_list.addEntry("John", 20);
score_list.addEntry("John", 250);
score_list.addEntry("John", 250);
score_list.saveFile();
```

``` console
- Loaded 2 entry(s) from 'highscore.txt' successfully!
- Added 'John' entry with a score of 200 points.
- Failed to add 'John' entry, found duplicate name and not a highscore.
- Updated 'John' with a score of 250 points.
- Failed to add 'John' entry, found duplicate name and score.
- Saved 3 entry(s) to 'highscore.txt' successfully.
```

## Methods

### `Score(std::string, int);`
**Parameter**
- **std::string** name
- **int** score

<table>
  <thead>
    <tr>
      <th>Method</th>
      <th>Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>void setName(std::string);</code></td>
      <td>
        change a name in object<br>
        <b>Parameter</b>
        <ul>
          <li><b>std::string</b> name to change</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>std::string Score::getName();</code></td>
      <td>
        get name from an object
      </td>
    </tr>
    <tr>
      <td><code>void setScore(int);</code></td>
      <td>
        change a score in object<br>
        <b>Parameter</b>
        <ul>
          <li><b>int</b> score to changeli>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>int getScore();</code></td>
      <td>
        get score from an object
      </td>
    </tr>
  </tbody>
</table>

<br>

### `ScoreList(std::string);`
**Parameter**
- **std::string** file name to save / load

<table>
  <thead>
    <tr>
      <th>Method</th>
      <th>Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>bool loadFile();</code></td>
      <td>
        for loading data in an object<br>
        <b>Return</b>
        <ul>
          <li><b>bool</b> is it success?</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>void saveFile();</code></td>
      <td>
        for saving data in an object
      </td>
    </tr>
    <tr>
      <td><code>bool addEntry(Score player);</code><br>
      <code>bool addEntry(std::string, int);</code>
      </td>
      <td>
        for adding new score to an object sorting high to low<br>
        <b>Parameter</b>
        <ul>
          <li><b>Score</b> score object</li>
        </ul>
        <b>Parameter</b>
        <ul>
          <li><b>std::string</b> name to save</li>
          <li><b>int</b> score to save</li>
        </ul>
        <b>Return</b>
        <ul>
          <li><b>bool</b> is it success?</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>void printEntry(int = 0);</code></td>
      <td>
        print out entries<br>
        <b>Parameter</b>
        <ul>
          <li><b>int</b> entries to print (Default : 0 all)</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>std::vector &lt;Score&gt; get();</code></td>
      <td>
        get score entries from an object<br>
        <b>Return</b>
        <ul>
          <li><b>std::vector &lt;Score&gt;</b></li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>void set(std::vector &lt;Score&gt;);</code></td>
      <td>
        set score entries in an object<br>
        <b>Parameter</b>
        <ul>
          <li><b>std::vector &lt;Score&gt;</b></b></li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>int clear();</code></td>
      <td>
        clear all entries in an object<br>
        <b>Return</b>
        <ul>
          <li><b>int</b> deleted entries</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>void removeEntry(int)</code></td>
      <td>
        delete an entry at an index<br>
        <b>Parameter</b>
        <ul>
          <li><b>int</b> index of entries</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>Score getEntry(int)</code></td>
      <td>
        get an entry at index<br>
        <b>Parameter</b>
        <ul>
          <li><b>int</b> index of entries</li>
        </ul>
        <b>Return</b>
        <ul>
          <li><b>Score</b></li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>Score getFileName()</code></td>
      <td>
        get file name<br>
        <b>Return</b>
        <ul>
          <li><b>std::string</b> file name</li>
        </ul>
      </td>
    </tr>
  </tbody>
</table>
