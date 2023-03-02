for i in $(seq 1 10);
do 
  for d in build-*;
  do
    echo $d >> timing.txt
    ./$d/benchmark_mult_3 >> timing.txt
  done
done
