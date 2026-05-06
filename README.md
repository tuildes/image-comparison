<!-- HEADER -->
<p align="center">
<h3 align="center">LBP Image Comparison</h3>

<p align="center">Image generation and PGM comparison algorithm using LBP</p>
</p>
<!-- HEADER -->

## About

The **LBP IMAGE COMPARISON** project is a software written in the `C` language, designed for comparisons between a PGM database (P2 or P5) and another PGM image. It also allows for the creation of an LBP image using LBP (Local Binary Pattern) processing.

## Functionalities

### Mode 01 (LBP image creation)

* Based on an original PGM image, the algorithm creates a second PGM file by processing the original file using LBP
* **Input**: base image.pgm
* **Output (STDIN)**: none
* **Output**: creation of an output.pgm file with the specified name

```bash
./LBP -i original.pgm -o output.pgm

```

### Mode 02 (image comparison)

* Compares an input image with all PGM images within and returns the most similar one
* **Input**: image.pgm and directory/
* **Output (STDIN)**: imgNear.pgm 134.670000

```bash
./LBP -i original.pgm -d images/
```

## Compilation and execution
```bash
# In the root (compile)
makefile

# Run software
./LBP
```

## 🚀 Files

```
  src/             // Project SOURCE folder and code
  ├── auxiliary.c  // Auxiliary project functions
  ├── auxiliary.h  // Signatures of auxiliary functions
  ├── lbp.c        // PGM and LBP manipulation functions
  ├── lbp.h        // Signatures of PGM and LBP functions
  └── main.c       // Software body + main()
  
  makefile         // MAKEFILE file that generates the executable
  README.md        // This README contains the project description.
```

**NOTE**: More documentation and usage in the function signatures.

### src/ folder (detailed)

Folder with all source files: C and H

### src/auxiliar.c & src/auxiliar.h

Auxiliary functions for the project with more generic functions:

* Euclidean distance calculation: euclidian_distance
* Show options manual: options_manual
* Destroy a matrix: destroy_matrix
* Prepare location (concatenate dir + file): prepare_location_image

### src/lbp.c & src/lbp.h

Functions for manipulating PGM images and LBP files:
* Create matrix based on a PGM image: pgm_image_to_matrix
* Create LBP matrix based on a matrix: create_lbp_matrix
* Create PGM file using LBP matrix: create_pgm_image
* Create LBP histogram file: create_histogram_archive
* Verify histogram existence: verify_histogram_archive
* Transform histogram into a vector: histogram_file_to_vector
* Concatenate string + .lbp: concat_pgm

### src/main.c

Software that handles errors and chooses two processing modes described above. In addition to calling several of the functions described above and handling directories.

### Makefile

Base file to facilitate compilation and standardization
