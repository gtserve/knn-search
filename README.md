# k23a-project
Project for *'[K23A] Ανάπτυξη Λογισμικού για Πληροφοριακά Συστήματα'*

## Team

| Name               |     Α.Μ.      | Email                |
|:-------------------|:-------------:|:---------------------|
| Γεώργιος Τσερβένης | 1115201500164 | sdi1500164@di.uoa.gr |
| Νικόλαος Τσόλκας   | 1115201600184 | sdi1600184@di.uoa.gr |

## Table of Contents

- [1st Part](#1st-part)
  - [Download Datasets](#download-test-datasets)
  - [Build](#build)
  - [Run Main](#run-main)
  - [Run Tests](#run-tests)

- [2nd Part](#2nd-part)

- [3rd Part](#3rd-part)

# 1st Part

## Download Test Datasets
To run the `main` function of this part of the project you'll need to download the **siftsmall** dataset from http://corpus-texmex.irisa.fr/

- You can do so by running the following:
    ```bash
    $ curl -O ftp://ftp.irisa.fr/local/texmex/corpus/siftsmall.tar.gz
    ```
  
- And extract the archived file:
    ```bash
    $ tar -xzvf siftsmall.tar.gz
    ```

## Build

- After cloning the repo `cd` into its directory.

- Create a `build` directory:
    ```bash
    $ mkdir build
    $ cd build
    ```
- Generate project build system:

  ```bash
  $ cmake ..
  ```

- Build project:
   ```bash
    $ cmake --build . 
   ``` 

Alternatively you can build a specific target / executable such as `main` like so:

  ```bash
  $ cmake --build . --target main
  ```

## Run Main
The `main` function of this part of the project has to be run with the following flags/arguments:

- `-f`: `<path_to_dataset_directory>`
  - type: String 
  - example: `/home/user/.../data/siftsmall`


- `-a`: `<vamana_parameter_a`
    - type: Float
    - default: `2.0`


- `-k`:
    - type: Integer
    - default: `10`


- `-L`:
    - type: Integer
    - default: `10`


- `-R`:
    - type: Integer
    - default: `10`

An example of a run `main` is:
```bash
./main -f "./blah/blah/.../data/siftsmall" -a 1.1 -k 100 -L 100 -R 15
```

The output of the above was:
```bash
Read vectors! [Time: 14ms]
Run Vamana! [Time: 1033s]
Run Greedy! [Time: 76ms]
k-nearest neighbours [100]: 97 106 107 121 124 146 149 190 224 287 292 348 370 420 492 598 641 696 816 882 924 942 1038 1045 1064 1156 1254 1272 1292 1295 1317 1370 1625 1682 1689 1710 1756 1884 1895 1916 1995 2005 2154 2176 2436 2456 2648 2763 2774 2776 2837 2852 2890 3013 3043 3066 3138 3210 3237 3449 3515 3530 3543 3553 3615 3625 3687 3752 3814 4009 4050 4058 4064 4094 4096 4125 4263 4293 4320 4321 4527 4938 5231 5307 5375 6139 6630 6837 7245 8731 8887 9211 9541 9576 9701 9734 9758 9806 9814 9825
Recall: 0.96
[Total Time: 17min]
```
*(Here the calculation of the medoid was ignored, which have added ~6min to total runtime)*


## Run Tests

After you have built the whole project, you can run all tests by running in the `build` directory:
```bash
  $ ctest
```
The output of the above will be something like this:

```bash
  Test project /home/gtserve/Code/k23a-project/build
      Start 1: TestInput
  1/5 Test #1: TestInput ........................   Passed    0.00 sec
      Start 2: TestDataVector
  2/5 Test #2: TestDataVector ...................   Passed    0.00 sec
      Start 3: TestUtil
  3/5 Test #3: TestUtil .........................   Passed    0.00 sec
      Start 4: TestGraph
  4/5 Test #4: TestGraph ........................   Passed    0.00 sec
      Start 5: TestVamana
  5/5 Test #5: TestVamana .......................   Passed    0.00 sec
```

If you want a more analytical output you can run:
```bash
  $ ctest --verbose
```

If you want to run a specific test:
```bash
  $ ctest -R <TestName>
```

# 2nd Part


# 3rd Part


