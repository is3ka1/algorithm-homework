# Five Sorting Algorithm with Roughly cost time measurement

## Compile with `DEBUG` macro
### With sorting steps being output

    gcc main.c -DDEBUG=1 -o main

or

    gcc main.c -o main

### The silence one

    gcc main.c -DDEBUG=0 -o main

## Run

### With `stdin` input
    ./main

### With Command Line argument

    ./main seq_size min max algo

#### seq_size
 sequence_size

#### min
smallest available value in sequence

#### max
biggest available value in sequence

#### algo
Sorting Algorithm Available:

1. exchange_sort
2. merge_sort
3. quick_sort
4. counting_sort
5. heap_sort



