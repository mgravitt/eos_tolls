#include <tolls.hpp>

void tolls::createtg (const account_name account,
                      const string&         gatename,
                      uint32_t              latitude,
                      uint32_t              longitude,
                      const string&         highway_name,
                      uint32_t              highway_number,
                      const string&         direction) {

  require_auth (account);

  tg_table tg(_self, _self);

  auto itr = tg.find(account);
  eosio_assert(itr == tg.end(), "Tollgate (tg) already exists");

  tg.emplace(account, [&](auto& t) {
    t.account         = account;
    t.gatename        = gatename;
    t.latitude        = latitude;
    t.longitude       = longitude;
    t.highway_name    = highway_name;
    t.highway_number  = highway_number;
    t.direction       = direction;
  });

  print (name{account}, " Tollgate (tg) created.");
}

void tolls::createtgu(const account_name account) {

  tgu_table tgu(_self, _self);
  auto itr = tgu.find(account);
  eosio_assert(itr == tgu.end(), "Tollgate User (tgu) already exists");

  tgu.emplace (account, [&](auto& t) {
    t.account      = account;
  });

  print (name{account}, " Tollgate User (tgu) created.");
}

void tolls::breachtg( const uint32_t breachId,
                        const account_name tg,
                        const account_name tgu)  {

  require_auth (tg);
  require_auth (tgu);

  // add toll gate breach
  tgb_table tgb(_self, _self);
  tgb.emplace(tgu, [&](auto& t) {
    t.breachId            = breachId;
    t.tg                  = tg;
    t.tgu                 = tgu;
    t.timestamp           = now();
  });

  // increment balance on the toll gate user table
  tgu_table tgu_t (_self, _self);
  auto iterator = tgu_t.find(tgu);
  eosio_assert(iterator != tgu_t.end(), "Tollgate user (tgu) not found.");

  tgu_t.modify(iterator, tgu, [&](auto& t) {
    t.balance++;
  });

  //print (name{tg}, tollId);
  print (name{tg}, " tollgate (tg) breached.");
}
