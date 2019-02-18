H=1

S=46
E=52

T=62
F=69
DONE=false
until $DONE ;do
  read || DONE=true
  echo $REPLY
  sed -n "$((H)),$((H))p;$((H+1))q" output.dat >> filtered.dat
  sed -n "$((S)),$((E))p;$((E+1))q" output.dat >> filtered.dat
  sed -n "$((T)),$((F))p;$((F+1))q" output.dat >> filtered.dat
done < output.dat
