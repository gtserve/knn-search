# k23a-project
Project για το μάθημα [K23A] Ανάπτυξη Λογισμικού για Πληροφοριακά Συστήματα.

## Ομάδα

| Όνομα              |     Α.Μ.      | Email                |
|:-------------------|:-------------:|:---------------------|
| Γεώργιος Τσερβένης | 1115201500164 | sdi1500164@di.uoa.gr |
| Νικόλαος Τσόλκας   | 1115201600184 | sdi1600184@di.uoa.gr |

## Πίνακας Περιεχομένων
- [Installation](#installation)
- [Usage](#usage)

# 1ο Παραδοτέο

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
  
- Build project with `cmake`:
    ```bash
    $ cmake ..
    $ cmake --build . --target main
    ```

## Run
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

An example of `main` run could be:
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