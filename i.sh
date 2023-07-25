#!/bin/sh

PORT=${INPORT:-6727}

echo "START WHttpIN $PORT"

ncat -tklnp $PORT -c "echo \"\$(date)\" | ncat -U lo.sock && printf \"HTTP/1.0 200 Ok\n\nHello World!\""
