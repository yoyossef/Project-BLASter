# Project BLASter

Project BLASter is a source-to-source compiler that replaces specified linear algebra calculations in a program by a call to optimized functions from a BLAS library.

## How to use
### Build
`make`
### Run
`blaster [-v, --version] [-t, --tos] [-a, --ast] [-o, --output dest_file] source_file spec_file`

- `source_file`: the file of the program to optimize
- `spec_file`: the file describing the functions to recognize
- `-o dest_file`: to specify the output file (default file is `output.c`)

## Contributors
Team Buffalo (M1 SIL 2019-2020, Université de Strasbourg):
- ROSTAQI Yossef
- BEFOLE Benjamin
- ELHADDAD Hamza
- CHERGUI MALIH Ilyes 