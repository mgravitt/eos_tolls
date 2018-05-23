# EOS Toll Gate Simulator

## Dependencies

EOS

python

## Setup

Clone repo and cd to "tolls" dir

Start nodeos

--data_dir and --config-dir create new default chain in current directory

```
nodeos -e -p eosio --plugin eosio::wallet_api_plugin --plugin eosio::chain_api_plugin --plugin eosio::account_history_api_plugin --data-dir data --config-dir config
```

Setup wallet and keys

```
cleos wallet create > wallet
cleos create key > keys
cleos create key >> keys
cleos wallet import {private key #1}
cleos wallet import {private key #2}
```

Create tolls account

```
cleos create account eosio tolls {public key #1} {public key #1}
```

Compile and deploy smart contract.

I use the following shell script with "tolls tolls" as the arguments:

```
#!/bin/bash

if [[ $# -ne 2 ]]; then
    echo "USAGE: comptract.sh <ACCOUNT NAME> <Contract Name> from within the directory"
    exit 1
fi

ACCOUNT=$1
CONTRACT=$2

eosiocpp -o ${CONTRACT}.wast ${CONTRACT}.cpp &&
eosiocpp -g ${CONTRACT}.abi ${CONTRACT}.cpp &&
cleos set contract ${ACCOUNT} ../${CONTRACT}
```

Or can compile and deploy directly with:

```
eosiocpp -o tolls.wast tolls.cpp
eosiocpp -g tolls.abi tolls.cpp
cleos set contract tolls ../tolls
```

## Run the Simulator

### Python Simulator

Run python driver script to create accounts for toll gates, toll gate users, and then breach the tolls. The toll gate users' balances are incremented each time a toll gate is breached.

```
python tolls_simulate.py
```

### C++ Simulator

```
g++ tolls_driver.cpp
./a.out
```

You can modify the "num_gates", "num_tgus", and "num_breaches" to change how many gates, users, and breaches are created / executed.

## View the Results

The C++ driver runs about 130 TPS on my single EOS node running my laptop.

You cam then view the tables to see tollgates, toll gate users, and breaches:

```
$ cleos get table tolls tolls tgs
{
  "rows": [{
      "account": "44h4k",
      "gatename": "Zinkey State Road Exit 44",
      "latitude": 5,
      "longitude": 5,
      "highway_name": "Zinkey State Road",
      "highway_number": 507,
      "direction": "W"
    },{
      "account": "rf4ff",
      "gatename": "Roosevelt Turnpike Exit 61",
      "latitude": 7,
      "longitude": 6,
      "highway_name": "Roosevelt Turnpike",
      "highway_number": 300,
      "direction": "W"
    } }
  ],
  "more": false
}


$ cleos get table tolls tolls tgus
{
  "rows": [{
      "account": "afmru",
      "balance": 1
    },{
      "account": "bt4bm",
      "balance": 2
    },{
      "account": "elrn5",
      "balance": 4
    }],
  "more": false
}


$ cleos get table tolls tolls tgbs
{
  "rows": [{
      "breachId": 123951,
      "tg": "ouema",
      "tgu": "bt4bm",
      "timestamp": 1526914049
    },{
      "breachId": 222617,
      "tg": "ouema",
      "tgu": "elrn5",
      "timestamp": 1526914049
    },{
      "breachId": 228466,
      "tg": "ouema",
      "tgu": "elrn5",
      "timestamp": 1526914049
    },{
      "breachId": 314925,
      "tg": "rf4ff",
      "tgu": "afmru",
      "timestamp": 1526913980
    }],
  "more": false
}
```
