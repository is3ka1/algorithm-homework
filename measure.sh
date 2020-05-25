algorithms=([1]="exchange_sort" [2]="merge_sort" [3]="quick_sort" [4]="counting_sort" [5]="heap_sort")

[ ! -f ./main ] && gcc main.c -DDEBUG=0 -o main
if [ $# == 0 ];then
    NUMS=$(seq 100 100 1000)
else
    NUMS=$*
fi

for algo in {1..5}
do
    echo ${algorithms[$[algo]]}...
    for n in $NUMS
    do
        echo n: ${n}
        ./main ${n} -1000 1000 ${algo} >>${algorithms[$[algo]]}.csv
    done
done