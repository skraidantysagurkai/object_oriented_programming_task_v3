# Object-oriented programming project

## User instructions
### Installation of DMG file
If you would like to download only the program with no source code attached to it please download the OP_v3.dmg file from the project repository. \
After downloading the file please double-click on the .dmg file to open it. \
And execute the following commands:
* cd /Volumes/OP_v3
* ./installer.sh
After which the program files will be copied to your system and a shortcut of the executable created in your desktop.
To run the program, please either double-click the shortcut executable (OP_v3) or the executable in the source files (OP)
### When cloning repository
For running from the terminal:
g++ main.cpp FileGenerator.cpp Student.cpp TextReader.cpp UserInterface.cpp -o main \
And:
./main

Afterward you will be promoted to choose a version you want to run, please follow the prompted instructions.

## V.02

### Speed Tests

Testing was done 3 times, best results shown below.

| File Size<br/>  |   1000    |   10000    |   100000    |   1000000    |   10000000    |
|-----------------|:---------:|:----------:|:-----------:|:------------:|:-------------:|
| Read Times      |   4 ms    |   162 ms   |   1511 ms   |   11007 ms   |   152517 ms   |
| Sort Times      |   1 ms    |    7 ms    |    80 ms    |    731 ms    |   12374 ms    |
| Write Times     |   17 ms   |   74 ms    |   599 ms    |   4803 ms    |   85196 ms    |
| **Total Times** | **22 ms** | **243 ms** | **2110 ms** | **16541 ms** | **250087 ms** |

## V.03

### Speed Tests

**Vector speed tests:**

| File Size<br/>  |   1000    |   10000    |   100000    |   1000000    |   10000000    |
|-----------------|:---------:|:----------:|:-----------:|:------------:|:-------------:|
| Read Times      |   4 ms    |   162 ms   |   1511 ms   |   11007 ms   |   152517 ms   |
| Sort Times      |   1 ms    |    7 ms    |    80 ms    |    731 ms    |   12374 ms    |
| Write Times     |   17 ms   |   74 ms    |   599 ms    |   4803 ms    |   85196 ms    |
| **Total Times** | **22 ms** | **243 ms** | **2110 ms** | **16541 ms** | **250087 ms** |

**List speed tests:**

| File Size<br/>  |    1000    |   10000    |   100000    |   1000000    |   10000000    |
|-----------------|:----------:|:----------:|:-----------:|:------------:|:-------------:|
| Read Times      |   19 ms    |   159 ms   |   1477 ms   |   11988 ms   |   153359 ms   |
| Sort Times      |    0 ms    |    6 ms    |   106 ms    |    695 ms    |   13972 ms    |
| Write Times     |   237 ms   |   79 ms    |   800 ms    |   6021 ms    |   58267 ms    |
| **Total Times** | **256 ms** | **244 ms** | **2383 ms** | **18704 ms** | **225598 ms** |

**Notes:**

* Comparing time results with other projects, it is obvious that my Threading system does not add extra performance.
  This could be because:
    * There are 4 Threads used in this experiment for reading and writing, however there may be to much overhead for
      such operations when using Threads, thus making the program slower.
    * There could be a difference of performance just because of hardware differences. Program may even run faster on
      same systems.

## V1.0

### Speed Tests in regard to approaches

**Approach 1:**
In approach 1 we sort our students into two list type objects, either StudentsOver5, or StudentsUnder5

| File Size<br/> | 1000 | 10000 | 100000 | 1000000 | 10000000 |
|----------------|:----:|:-----:|:------:|:-------:|:--------:|
| Vector         | 0 ms | 3 ms  | 35 ms  | 417 ms  | 7814 ms  |
| List           | 0 ms | 4 ms  | 54 ms  | 419 ms  | 8555 ms  |

**Approach 2:**
In approach 2 we sort our students into two list type objects, by finding all students whos average grade is < 5 and
delete them in the previous list type object.

| File Size<br/> | 1000 | 10000 | 100000 | 1000000 | 10000000 |
|----------------|:----:|:-----:|:------:|:-------:|:--------:|
| Vector         | 0 ms | 0 ms  |  5 ms  |  60 ms  | 3160 ms  |
| List           | 0 ms | 0 ms  |  9 ms  |  92 ms  | 4153 ms  |

### Results:

* It is evident that he second approach is more efficient, from which vector type lists have shown the best results. I
  have no idea how to further optimise approach 2, so approach 3 will be an optimised approach 1.
* Results consist of averaged times over 5 different runs.

**Approach 3:**
In approach 3 we create two list type object, inserting students into subsequent list if there average is over 5 or
under 5. To do this I've used optimised list type object methods.

| File Size<br/> | 1000 | 10000 | 100000 | 1000000 | 10000000 |
|----------------|:----:|:-----:|:------:|:-------:|:--------:|
| Vector         | 0 ms | 0 ms  |  4 ms  |  69 ms  | 2282 ms  |
| List           | 0 ms | 1 ms  | 12 ms  | 189 ms  | 3596 ms  |

### Results:

* An optimised approach 1 showed better results than approach 2

## V1.1

In this part I will be changing the datatype of the Student structure to a class.

### Sorting Speed Tests

We are using the best performing sort from v1.0, using vectors as the list-type object to hold grades.

| File Size<br/> | 1000 | 10000 | 100000 | 1000000 | 10000000 |
|----------------|:----:|:-----:|:------:|:-------:|:--------:|
| Vector         | 0 ms | 1 ms  | 18 ms  | 147 ms  | 4308 ms  |

### Results

* We can see that having Students as a class inevitably creates more overhead thus making our sorting algorithm slower.

### Flags test

**As Class:**

| Flag<br/> | Size   | 1000 | 10000 | 100000 | 1000000 | 10000000 |
|:---------:|--------|:----:|:-----:|:------:|:-------:|:--------:|
|    -01    | 123 kB | 0 ms | 3 ms  | 37 ms  | 575 ms  | 5260 ms  |
|    -02    | 159 kB | 0 ms | 0 ms  | 12 ms  | 136 ms  | 3164 ms  |
|    -03    | 159 kB | 0 ms | 1 ms  | 14 ms  | 147 ms  | 3998 ms  |

**As Struct:**

| Flag<br/> | Size   | 1000 | 10000 | 100000 | 1000000 | 10000000 |
|:---------:|--------|:----:|:-----:|:------:|:-------:|:--------:|
|    -01    | 285 kB | 0 ms | 3 ms  | 30 ms  | 326 ms  | 4770 ms  |
|    -02    | 156 kB | 0 ms | 0 ms  |  5 ms  |  59 ms  | 3168 ms  |
|    -03    | 157 kB | 0 ms | 0 ms  |  4 ms  |  46 ms  | 2355 ms  |

## V1.2

The implementation of the rule of three: \
<img width="801" alt="Screenshot 2023-12-31 at 17 43 49" src="https://github.com/skraidantysagurkai/object_oriented_programming_task_v2/assets/31926359/317bd580-2795-4a79-8fce-4ebf8ec9bea7">
\
\
Example of usage: \
<img width="655" alt="Screenshot 2023-12-31 at 17 46 09" src="https://github.com/skraidantysagurkai/object_oriented_programming_task_v2/assets/31926359/5b957d85-a6e7-4974-94d2-f8a6705d9832">

## V1.5

Person abstract Class implementation: \
<img width="568" alt="Screenshot 2024-01-02 at 17 12 39" src="https://github.com/skraidantysagurkai/object_oriented_programming_task_v2/assets/31926359/804ddea0-eeb2-4ebb-80aa-996cce1c4325">

\
\
Example of Person object construction and failed build messages: \
<img width="769" alt="Screenshot 2024-01-02 at 17 11 58" src="https://github.com/skraidantysagurkai/object_oriented_programming_task_v2/assets/31926359/3983e82e-5b93-432b-b1e0-d691b6572946">
<img width="998" alt="Screenshot 2024-01-02 at 17 11 46" src="https://github.com/skraidantysagurkai/object_oriented_programming_task_v2/assets/31926359/48dd0257-eea7-4ed8-9e5b-1ea25c2d2678">

# System parameters:

* Processor: 2.3GHz Dual-core Intel Core i5
* Memory: 8 GB 2133 MHz LPDDR3
* Storage: APPLE SSD AP0128J 121 GB
