# `mm`

lazy based, convenient webhook consumer that trigger command through tcp thing

> [!NOTE]
> **Just in case you want to scale it to the moon, or internal only use with stack that will help you to find a job, use [kcat](https://github.com/edenhill/kcat) with Apache Kafka**

## Requirements

- `ncat`
- A server with at least 1 exposed tcp port, and a http port (proxyable)

## How to (install)

- `git clone` this repo
- `./make.sh` to make `mm.c`

## How to use

- Server

By default, it use `8727` as TCP port and `6727` as HTTP port.

You can change it with *enviroment variables*: `IPORT` (for HTTP port) and `OPORT` (for TCP PORT)

If you know what does this mean

```sh
rm lo.sock && killall ncat && ./run.sh
```
Then go ahead

- Client

To run client trigger, simply:
```
SYNC="example.com 8727" ./trig.sh
```

If you want to customize the trigger, edit `CMD` *enviroment variable*

## 

And have a nice day. If this really solve your ploblem without a single PHP file and not fck your docker stack up, give a star!
