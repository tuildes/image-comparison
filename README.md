<p align="center">
  <h1 align="center">Image Comparison</h1>
</p>

<p align="center">
  <i>A fast, C-based CLI tool for generating and comparing PGM images using Local Binary Patterns (LBP) and histogram caching.</i>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Platform-Linux%20%7C%20macOS-blue" alt="Platform">
  <img src="https://img.shields.io/badge/Language-C-orange" alt="C Language">
  <img src="https://img.shields.io/badge/License-MIT-green" alt="License">
</p>

## About

LBP Image Comparison is a lightweight software written in C designed to compare a base PGM image (P2 or P5) against a local database of images. It calculates similarities using Local Binary Patterns (LBP) and histograms. To optimize performance on repeated searches, the tool automatically caches the analyzed images. 

## Features

* **Pattern Recognition:** Extracts and processes features using the LBP algorithm.
* **Image Comparison:** Finds the most similar image in a local database by comparing Euclidean distances of LBP histograms.
* **Performance Caching:** Automatically saves histogram data to speed up future comparisons.
* **LBP Image Generation:** Converts standard PGM images into their LBP visual representations.

## Installation

To compile the project, ensure you have a C compiler (like `gcc`) and `make` installed.

```bash
make
```

# Usage
The executable ./LBP provides two main operating modes:

## Mode 1: LBP Image Creation
Generates a new PGM file by applying the LBP algorithm to the original image.

```bash
./LBP -i original.pgm -o output.pgm
```

## Mode 2: Image Comparison
Compares an input image against all PGM files inside a specified directory and returns the most similar one.

```
Bash
./LBP -i original.pgm -d images/
```
