for d in build-*;
do 
  echo "******* Starting on $d";
  pushd $d;
  # make clean;
  make -j;
  ctest | ctest --output-on-failure --rerun-failed;
  make handopt.s long_mult_3.s only_construct.s right_fold_mult_3.s use_mult_3.s;
  make benchmark_mult_3.s benchmark_only_construct.s
  echo "******* Done with $d";
  popd;
done
