cur="$(pwd)"

cd "$2/cases"
zip "../../$1/$2.zip" *
#echo "$1/$2.zip" "$2/cases/*"

cd $cur

mkdir tmp 2>/dev/null
echo "-p $3 -t 4 -m 262144" > config # 256mb
echo >> config
for i in {1..5}; do
    echo "test $i.in $i.out" >> config
done

zip "$1/$2.zip" config

