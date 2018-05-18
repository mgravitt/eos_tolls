#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include <string>

using namespace eosio;
using std::string;

class tolls: public contract {
public:
  tolls(account_name self) : contract (self) {}

  // @abi action
  void create ( const account_name    account,
                const string&         gatename,
                uint32_t              latitude,
                uint32_t              longitude,
                const string&         highway_name,
                uint32_t              highway_number,
                const string&         direction);

  // @abi action
  void breachtoll (  const uint32_t       tollId,
                     const account_name   tollgate,
                     const account_name   vehicle);

private:

    // @abi table tollgates i64
    struct tollgate {
      account_name    account;
      string          gatename;
      uint32_t        latitude;
      uint32_t        longitude;
      string          highway_name;
      uint32_t        highway_number;
      string          direction;

      account_name primary_key() const { return account; }

      EOSLIB_SERIALIZE(tollgate, (account)(gatename)(latitude)(longitude)(highway_name)(highway_number)(direction))
    };

    typedef eosio::multi_index<N(tollgates), tollgate> tollgate_table;

    // @abi table tollbreaches1 i64
    struct tollbreach {
      uint32_t        tollId;
      account_name    tollgate;
      account_name    vehicle;
      uint32_t        timestamp;

      uint32_t primary_key() const { return  tollId; }
      EOSLIB_SERIALIZE(tollbreach, (tollgate)(vehicle)(timestamp));
    };

    typedef eosio::multi_index<N(tollbreaches), tollbreach> tollbreach_table;

};

EOSIO_ABI(tolls, (create)(breachtoll))
