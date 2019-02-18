for size in 10 100 1000 10000 100000 1000000;  do
	./time_test ${size} >> data_unfiltered.out
done
