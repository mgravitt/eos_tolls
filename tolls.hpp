#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include <string>

using namespace eosio;
using std::string;

class tolls: public contract {
public:
  tolls(account_name self) : contract (self) {}

  // @abi action
  void createtg (  const account_name    account,
                   const string&         gatename,
                   uint32_t              latitude,
                   uint32_t              longitude,
                   const string&         highway_name,
                   uint32_t              highway_number,
                   const string&         direction);

  // @abi action
  void createtgu ( const account_name   account);

  // @abi action
  void breachtg (  const uint32_t       breachId,
                   const account_name   tg,
                   const account_name   tgu);

  // @abi action
  void cleartgbs (const account_name);

  // @abi action
  void cleartgus (const account_name);

  // @abi action
  void cleartgs (const account_name);

  // @abi action
  void clearall (const account_name);


private:

    // @abi table tgs i64
    struct tg {
      account_name    account;
      string          gatename;
      uint32_t        latitude;
      uint32_t        longitude;
      string          highway_name;
      uint32_t        highway_number;
      string          direction;

      account_name primary_key() const { return account; }

      EOSLIB_SERIALIZE(tg, (account)(gatename)(latitude)(longitude)(highway_name)(highway_number)(direction))
    };

    typedef eosio::multi_index<N(tgs), tg> tg_table;

    // @abi table tgbs i64
    struct tgb {
      // experimenting with Dapp-generated primary key
      // and blockchain generated primary key
      uint32_t        pkey;     // b-chain generated
      uint32_t        breachId; // dapp generated
      account_name    tg;
      account_name    tgu; //vehicle
      uint32_t        timestamp;

      uint32_t primary_key() const { return  breachId; }
      EOSLIB_SERIALIZE(tgb, (pkey)(breachId)(tg)(tgu)(timestamp));
    };

    typedef eosio::multi_index<N(tgbs), tgb> tgb_table;

    // @abi table tgus i64
    struct tgu {
      account_name    account;
      uint32_t        balance;
    //  float           balance;

      account_name primary_key() const {return account; }
      EOSLIB_SERIALIZE(tgu, (account)(balance));
    };

    typedef eosio::multi_index<N(tgus), tgu> tgu_table;
};

EOSIO_ABI(tolls, (createtg)(createtgu)(breachtg)(cleartgbs)(cleartgs)(cleartgus)(clearall))
