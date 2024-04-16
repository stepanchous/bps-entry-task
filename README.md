# acct2sql

This is a command line tool for converting account data in TLV format into SQL insert statement 

## Design
The tool consists of three main components.  
### Model
Small layer due to narrow scope of the program. Consists only from `struct Account` and dynamic array of this structure type.  
### Deserialization
#### General
During development I assumed that some sort of protocol based on TLV format exists. This assumption is a ground for decision of writing generic code for reading any TLV message.
#### Account
Type specific deserialization for `Account`. Functions that deserialize `Account` include validations for input values. Validation is needed because tool is supposed to complement database management meaning that it needs to be resistent to malicious input.
### Insert statement formatter
This layer takes model entity as input and prints SQL insert statement to stream.
## Build
The tool is developed for Linux/x86 platform.  
```
git clone https://github.com/stepanchous/bps-entry-task.git
cd bps-entry-task
make acct2sql
```
Supported targets:
- `debug` (Debug build for acct2sql)
- `test` (Builds unit-tests, requires `check` library)
- `coverage` (Make `gcov` report, __note that this target runs executable__)
- `clean` (Remove build directory)