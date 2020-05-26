# Five Sorting Algorithms With Roughly Measurement Of The Time Spent

## Compile With `DEBUG` Macro
### with sorting steps being output

    gcc main.c -DDEBUG=1 -o main

or

    gcc main.c -o main

### the silence one

    gcc main.c -DDEBUG=0 -o main

## Run

### with `stdin` input
    ./main

### with command line argument

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

## Measure with measure.sh script
    bash ./measure.sh
   
specify with custome range:

    bash ./measure.sh $(seq low step high)

## Plot using plot_graphs.py script

    pipenv run python plot_graphs.py

