# Digit Rounding
## A HDF5 filter for scientific datasets compression with a fixed number of significant digits preserved


# Goals

Digit Rounding is a data reduction method applies to floating point
datasets.  It allows preserving a fixed number of significant digits
*nsd* in the decimal representation of the sample values and introduces
a variable number of bits 0 in the binary representation of the floating
point sample value to improve the compressibility of the datasets.

The table below provides an example. It presents the value of π in
IEEE-754 single-precision binary representation (first row) and results
preserving 4 significant digits with the Digit Rounding algorithm
(second row). Preserving 4 significant digits allows zeroing 11 bits in
the IEEE-754 single-precision binary representation of π.

| Sign | Exponent | Mantissa                | Decimal    | Note             |
| -----|----------| ------------------------| -----------| -----------------|
| 0    | 10000000 | 10010010000111111011011 | 3.14159265 | Exact value of π |
| 0    | 10000000 | 10010010000100000000000 | 3.14111328 | Result of the Digit Rounding algorithm with *nsd* = 4|

Digit Rounding is implemented as a HDF5 plugin filter (the temporary
**filter ID is 47987**) and is intended to be used within a filtering
pipeline with a lossless compression method (e.g. Deflate or Zstandard)
to achieve high compression ratios. See the [Usage](#usage) section
below for examples.

# Setup

## Requirements

- HDF5 version 1.8.11 or newer.

## Build and install

The environment variable `HDF5_PATH` should be set and point to the
installation path of HDF5. For example:
    
	# Set the HDF5_PATH path environment variable
    export HDF5_PATH=/path/to/hdf5
    
The environment variable `HDF5_PLUGIN_PATH` should be also be set to the
desire install location, for example:

	# Set the HDF5_PLUGIN_PATH path environment variable
	export HDF5_PLUGIN_PATH=/usr/local/hdf5/lib/plugin

To build and install Digit Rounding run: 

	# Go to the source code directory of digit rounding
	cd digiround
	# Build and install
	make
	make install
	# Go back to the previous directory
	cd -

This copies the file `libH5Zdround.so` into the `HDF5_PLUGIN_PATH`
diretory.

# Usage

Usage with h5repack:

	h5repack -i infile.h5 -o outfile.h5 --filter=var:UD=47987,1,1,nsd

- *infile.h5*  
   input HDF5 dataset file
- *outfile.h5*  
   output 'digit rounded' HDF5 dataset file
- *var*  
	variable to process in the HDF5 dataset

UD identifies the HDF5 filter to apply on the *var* dataset. The
temporary ID for the Digit Rounding filter is **47987**. 

Next number 1 provides the number of parameters to configure the Digit
Rounding filter.

The Digit Rounding filter parameters are:

- *nsd*  
	number of significant digit kept (default: 3)

	
## Examples 

The following command lines process the sample dataset file
`data/sample.h5` using the Digit Rounding algorithm and keeping 2
significant digits. The result is then compressed applying *Shuffle* and
*Deflate*. It produces the file `data/sample_c.h5`.

    # Compression
	h5repack -i data/sample.h5 -o data/sample_c.h5 --filter=UD=47987,0,1,2 --filter=SHUF --filter=GZIP=1
    # Inspection
    h5ls -d data/sample.h5
    h5ls -d data/sample_c.h5
    h5ls -v data/sample_c.h5

*Note*: The compression ratios on this sample dataset are very low. They
may be higher on larger datasets.
         
The following command line decompresses the file `data/sample_c.h5` and
produces the file `data/sample_d.h5` in the current directory.

    # Decompression
	h5repack -i data/sample_c.h5 -o data/sample_d.h5 --filter=NONE
    # Inspection
    h5ls -d data/sample_d.h5
    h5ls -v data/sample_d.h5
