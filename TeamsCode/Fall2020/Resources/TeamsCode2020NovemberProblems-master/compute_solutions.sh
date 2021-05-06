for f in $(ls cases/*.in); do echo computing $f; ./a.out < $f > $(echo $f | sed 's/in$/out/'); done

