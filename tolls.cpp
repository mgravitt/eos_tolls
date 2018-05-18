#include <tolls.hpp>

void tolls::create(const account_name account,
                  const string&         gatename,
                  uint32_t              latitude,
                  uint32_t              longitude,
                  const string&         highway_name,
                  uint32_t              highway_number,
                  const string&         direction) {

  require_auth (account);

  tollgate_table tollgate(_self, _self);

  auto itr = tollgate.find(account);

  eosio_assert(itr == tollgate.end(), "Tollgate already exists");

  tollgate.emplace(account, [&](auto& t) {
    t.account         = account;
    t.gatename        = gatename;
    t.latitude        = latitude;
    t.longitude       = longitude;
    t.highway_name    = highway_name;
    t.highway_number  = highway_number;
    t.direction       = direction;
  });

  print (name{account}, " tollgate created.");
}


void tolls::breachtoll( const uint32_t tollId,
                        const account_name tollgate,
                        const account_name vehicle)  {

  require_auth (tollgate);
  require_auth (vehicle);

  tollbreach_table tollbreach(_self, _self);

  tollbreach.emplace(tollgate, [&](auto& t) {
    t.tollId           = tollId;
    t.tollgate         = tollgate;
    t.vehicle          = vehicle;
    t.timestamp        = now();
  });

  //print (name{tollgate}, tollId);
  print (name{tollgate}, " tollgate breached.");
}
