# ScoreList

เป็นตัวช่วยในการบันทึกคะแนน สำหรับบันทึกคะแนน Highscore โดยสามารถบันทึกชื่อและคะแนนเป็นลำดับมากไปน้อย

- [ScoreList](#scorelist)
  - [Examples](#examples)
  - [Usage](#usage)
  - [Methods](#methods)
    - [`Score(std::string, int);`](#scorestdstring-int)
    - [`ScoreList(std::string);`](#scoreliststdstring)

## Examples

ทำเกมที่มีการบันทึก Highscore ได้ง่าย ๆ โดย

``` cpp
#include <iostream>
#include "include/ScoreList.h"

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

ลองรันโปรแกรมครั้งที่ 1 โดยใส่ชื่อ Korn และคะแนน 23

``` console
Output :
- Load entry(s) failed, file or data not found.
Enter name : Korn
Enter score : 23
- Added 'Korn' with a score of 23 points.
- Saved 1 entry(s) to 'highscore.txt' successfully.
```

ลองรันโปรแกรมครั้งที่ 2 โดยใส่ชื่อ John และคะแนน 55

``` console
Output :
- Loaded 1 entry(s) from 'highscore.txt' successfully!
Enter name : John
Enter score : 55
- Added 'John' entry with a score of 55 points.
- Saved 2 entry(s) to 'highscore.txt' successfully.
```

ลองรันโปรแกรมครั้งที่ 3 โดยใส่ชื่อ Korn และคะแนน 60

``` console
Output :
- Loaded 2 entry(s) from 'highscore.txt' successfully!
Enter name : Korn
Enter score : 60
- Updated 'Korn' with a score of 60 points.
- Saved 2 entry(s) to 'highscore.txt' successfully.
```

ไฟล์ highscore.txt

```
Korn
60
John
55
```

<br>

ถ้ามี Object อื่น ก็สามารถส่ง Address ไปได้

``` cpp
#include <iostream>

#include "include/ScoreList.h"

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

        score_list->addEntry(user_name, user_score);
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

หากเพิ่มข้อมูลหลายอย่าง คะแนนต่างกัน ระบบจะจัดการให้เอง

``` cpp
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

สร้าง Object `ScoreList` โดยใส่ชื่อไฟล์ไปด้วยสำหรับบันทึกข้อมูลลงไฟล์ สามารถลองเพิ่มข้อมูลคะแนนลงไป โดยสร้าง Object `Score` แล้วใส่ชื่อ / ใส่คะแนน

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

สามารถเพิ่มคะแนนใหม่ด้วยวิธีนี้ได้เลย `addEntry(Score(ชื่อ, คะแนน));`
จากนั้นลองพิมพ์รายการที่มีอยู่ออกมาได้เป็นตารางโดยใช้คำสั่ง `printEntry();`

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

สามารถบันทึกข้อมูลลงไฟล์ได้โดยใช้คำสั่ง `saveFile();`

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

เมื่อทดลองโหลดข้อมูลจากไฟล์ โดยใช้คำสั่ง `loadFile();` แล้วพิมพ์ข้อมูลอีกรอบ

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

เมื่อโหลดแล้วก็สามารถเพิ่มข้อมูลใส่แล้วบันทึกข้อมูลอีกรอบได้เลย
- หากชื่อซ้ำกัน แต่คะแนนน้อยกว่าคะแนนในรายการ **คะแนนจะไม่ถูกบันทึก**
- หากชื่อซ้ำกัน แต่คะแนนมากกว่าคะแนนในรายการ **คะแนนจะถูกอัพเดต**
- หากชื่อซ้ำกัน คะแนนซ้ำกัน **จะไม่สามารถเพิ่มข้อมูลลงในรายการซ้ำได้**

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
- **std::string** ชื่อ
- **int** คะแนน

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
        เปลี่ยนชื่อใหม่ให้กับ Object<br>
        <b>Parameter</b>
        <ul>
          <li><b>std::string</b> ชื่อที่ต้องการเปลี่ยน</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>std::string Score::getName();</code></td>
      <td>
        ดึงชื่อจาก Object
      </td>
    </tr>
    <tr>
      <td><code>void setScore(int);</code></td>
      <td>
        เปลี่ยนคะแนนใหม่ให้กับ Object<br>
        <b>Parameter</b>
        <ul>
          <li><b>int</b> คะแนนที่ต้องการเปลี่ยน</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>int getScore();</code></td>
      <td>
        ดึงคะแนนจาก Object
      </td>
    </tr>
  </tbody>
</table>

<br>

### `ScoreList(std::string);`
**Parameter**
- **std::string** ชื่อไฟล์ที่ต้องการบันทึก / โหลด

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
        สำหรับโหลดข้อมูลจากไฟล์เก็บไว้ในรายการ<br>
        <b>Return</b>
        <ul>
          <li><b>bool</b> สำเร็จหรือไม่</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>void saveFile();</code></td>
      <td>
        สำหรับบันทึกข้อมูลจากรายการลงในไฟล์
      </td>
    </tr>
    <tr>
      <td><code>bool addEntry(Score player);</code><br>
      <code>bool addEntry(std::string, int);</code>
      </td>
      <td>
        สำหรับเพิ่มข้อมูลคะแนนลงในรายการ โดยเรียงจากมากไปน้อย<br>
        <b>Parameter</b>
        <ul>
          <li><b>Score</b> Object คะแนน</li>
        </ul>
        <b>Parameter</b>
        <ul>
          <li><b>std::string</b> ชื่อที่ต้องการบันทึก</li>
          <li><b>int</b> คะแนนที่ต้องการบันทึก</li>
        </ul>
        <b>Return</b>
        <ul>
          <li><b>bool</b> สำเร็จหรือไม่</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>void printEntry(int = 0);</code></td>
      <td>
        พิมพ์ข้อมูลออกมาเป็นตาราง<br>
        <b>Parameter</b>
        <ul>
          <li><b>int</b> จำนวนข้อมูลที่ต้องการพิมพ์ (Default : 0 พิมพ์ทั้งหมด)</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>std::vector &lt;Score&gt; get();</code></td>
      <td>
        สำหรับดึงค่าข้อมูลรายการ<br>
        <b>Return</b>
        <ul>
          <li><b>std::vector &lt;Score&gt;</b></li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>void set(std::vector &lt;Score&gt;);</code></td>
      <td>
        สำหรับเซ็ตค่ารายการ<br>
        <b>Parameter</b>
        <ul>
          <li><b>std::vector &lt;Score&gt;</b></b></li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>int clear();</code></td>
      <td>
        ล้างข้อมูลในรายการทั้งหมด<br>
        <b>Return</b>
        <ul>
          <li><b>int</b> จำนวนรายการที่ลบ</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>void removeEntry(int)</code></td>
      <td>
        ลบข้อมูลที่ตำแหน่งหนึ่งของรายการ<br>
        <b>Parameter</b>
        <ul>
          <li><b>int</b> ลำดับข้อมูลที่ต้องการลบ</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td><code>Score getEntry(int)</code></td>
      <td>
        ดึงข้อมูลจากในรายการที่ต้องการโดยใส่ลำดับที่ต้องการ<br>
        <b>Parameter</b>
        <ul>
          <li><b>int</b> ลำดับข้อมูลที่ต้องการ</li>
        </ul>
        <b>Return</b>
        <ul>
          <li><b>Score</b></li>
        </ul>
      </td>
    </tr>
  </tbody>
</table>