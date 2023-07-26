#!/bin/sh

PORT=${OPORT:-8727}

echo START TCPEl $PORT

ncat -tklnp $PORT -c "ncat -U lo.sock --recv-only"
