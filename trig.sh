ncat $CONN |sh -c "while read; do git pull;done < /dev/stdin;end"
