for i in `seq 1 10000`; do
    echo $i 

    ./input_gen $i 4 5 > input.txt
    ./code < input.txt > output.txt
    ./naive < input.txt > answer.txt

    diff output.txt answer.txt || break
done
