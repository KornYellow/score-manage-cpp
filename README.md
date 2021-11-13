# ScoreList

เป็นตัวช่วยในการบันทึกคะแนน สำหรับบันทึกคะแนน Highscore โดยสามารถบันทึกชื่อและคะแนนเป็นลำดับมากไปน้อย

สารบัญ
- [ScoreList](#scorelist)
  - [Examples](#examples)
  - [Usage](#usage)
  - [Methods](#methods)
    - [`Score(std::string, int);`](#scorestdstring-int)
      - [`void setName(std::string);`](#void-setnamestdstring)
      - [`std::string Score::getName();`](#stdstring-scoregetname)
      - [`void setScore(int);`](#void-setscoreint)
      - [`int getScore();`](#int-getscore)
    - [`ScoreList(std::string)`](#scoreliststdstring)
      - [`bool loadFile()`](#bool-loadfile)
      - [`void saveFile()`](#void-savefile)
      - [`bool addEntry(Score player)` <br> `bool addEntry(std::string, int)`](#bool-addentryscore-player--bool-addentrystdstring-int)
      - [`void printEntry(int)`](#void-printentryint)
      - [`std::vector <Score> ScoreList::get();`](#stdvector-score-scorelistget)
      - [`void set(std::vector <Score>);`](#void-setstdvector-score)
      - [`int clear();`](#int-clear)
      - [`void removeEntry(int)`](#void-removeentryint)
      - [`Score getEntry(int)`](#score-getentryint)

## Examples

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

## Usage

## Methods

### `Score(std::string, int);`

#### `void setName(std::string);`
เปลี่ยนชื่อใหม่ให้กับ Object
- **Parameter**
  - *std::string* ชื่อที่ต้องการเปลี่ยน

#### `std::string Score::getName();`
ดึงชื่อจาก Object

#### `void setScore(int);`
เปลี่ยนคะแนนใหม่ให้กับ Object
- **Parameter**
  - *int* คะแนนที่ต้องการเปลี่ยน

#### `int getScore();`
ดึงคะแนนจาก Object

### `ScoreList(std::string)`
- **Parameter**
  - *std::string* ชื่อไฟล์ที่ต้องการบันทึก / โหลด

#### `bool loadFile()`
สำหรับโหลดข้อมูลจากไฟล์เก็บไว้ในรายการ
- **Return** 
  - *bool* สำเร็จหรือไม่

#### `void saveFile()`
สำหรับบันทึกข้อมูลจากรายการลงในไฟล์

#### `bool addEntry(Score player)` <br> `bool addEntry(std::string, int)`
สำหรับเพิ่มข้อมูลคะแนนลงในรายการ โดยเรียงจากมากไปน้อย
- **Parameter**
  - *Score* Object คะแนน
- **Parameter**
  - *std::string* ชื่อ
  - *int* คะแนน 
- **Return** 
  - *bool* สำเร็จหรือไม่

#### `void printEntry(int)`
พิมพ์ข้อมูลในรายการออกมาเป็นตาราง
- **Parameter**
  - *int* จำนวนข้อมูลที่ต้องการพิมพ์ (default : 0 พิมพ์ทั้งหมด)

#### `std::vector <Score> ScoreList::get();`
สำหรับดึงค่าข้อมูลรายการ
- **Return**
  - *std::vector \<Score\>*

#### `void set(std::vector <Score>);`
สำหรับเซ็ตค่ารายการ
- **Parameter**
  - *std::vector \<Score\>*

#### `int clear();`
ล้างข้อมูลในรายการทั้งหมด
- **Return**
  - *int* จำนวนรายการที่ลบ

#### `void removeEntry(int)`
ลบข้อมูลที่ตำแหน่งหนึ่งของรายการ
- **Parameter**
  - *int* ลำดับข้อมูลที่ต้องการลบ

#### `Score getEntry(int)`
ดึงข้อมูลจากในรายการที่ต้องการโดยใส่ลำดับที่ต้องการ
- **Parameter**
  - *int* ลำดับข้อมูลที่ต้องการ
- **Return**
  - *Score*