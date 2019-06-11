# AssociativeArraysCPP

A program to test associative arrays. Used `std::map` and `std::set`.

## Usage
This program reads `text.txt` file and works with it. Filters out 
URLs, prints them. Also searches for repeating words and fills a 
cross-reference table. Everything is printed out to `result.txt` file.

## Versions

### v1.1
* Added sorting by word count;
* Instead of one column in output now there are two.

### v1.0
* Initial release

## Example 

#### text.txt
`A computer is a machine that can be instructed to carry out sequences https://en.wikipedia.org/wiki/Sequence of
 arithmetic or logical operations automatically via computer programming. Modern computers have the ability to follow
 generalized sets of operations, called programs. These programs enable computers to perform an extremely wide range of
 tasks. A "complete" computer including the hardware, the operating system (main software)
 en.wikipedia.org/wiki/Software , and peripheral equipment required and used for "full" operation can be referred to
 as a computer system. This term may as well be used for a group of computers that are connected and work together,
 in particular a computer network or computer cluster.`
 
#### result.txt
![result.txt](https://puu.sh/DEvNK/af3cfdb710.png)