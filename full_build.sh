for d in build-*;
do 
  echo "******* Starting on $d";
  pushd $d;
  make -j;
  ctest | ctest --output-on-failure --rerun-failed;
  # make fake_mult_3.s long_mult_3.s only_construct.s right_fold_mult_3.s use_mult_3.s;
  echo "******* Done with $d";
  popd;
done
