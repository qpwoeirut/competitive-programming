for p in */; do for f in $(ls $p/cases/*.in); do sed --in-place 's/[[:space:]]\+$//' $f; sed --in-place '/^$/N;/^\n$/D' $f; done done
