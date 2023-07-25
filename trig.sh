ncat $SYNC |sh -c "while read; do ${CMD:-"git pull"};done < /dev/stdin;end"
