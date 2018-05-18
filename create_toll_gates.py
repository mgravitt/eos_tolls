import random, hashlib, datetime, time
from subprocess import call
start_time = time.time()

# create random sequence of letters for tollgate ID
direction = ["N","S","W","E"];
road_words = ["Interstate", "Parkway", "Highway", "State Road", "Boulevard", "Turnpike"]
road_names = ["Sunset", "California", "Norway", "Water", "Court", "Samson",
                "Johnson", "Zebra", "Thomas", "Jets", "Falcons", "Peters", "Zinkey",
                "Roosevelt", "Bush", "Eisenhower", "Jerry", "Jenkins", "Bussie", "Moore"]

chars = ["1", "2", "3","4","5","a","b",
            "c","d","e","f","g","h","i","j","k","l",
            "m","n","o","p","q","r","s","t","u","v","x","y","z"]

num_gates = 100
toll_gates = []

for i in range (0, num_gates):
    #tollgate = {};
    id = chars[random.randint(0, len(chars)-1)] + chars[random.randint(0, len(chars)-1)] + chars[random.randint(0, len(chars)-1)] + chars[random.randint(0, len(chars)-1)] + chars[random.randint(0, len(chars)-1)]
    highway_name = road_names[random.randint(0, len(road_names)-1)] + " " + road_words[random.randint(0, len(road_words)-1)]
    gatename = highway_name + " Exit " + str(random.randint(12, 99))
    latitude =  random.randint(300, 800) / 100
    longitude = random.randint(300, 800) / 100
    highway_number = random.randint(12,643)
    direction = direction[random.randint(0, len(direction)-1)]
    toll_gates.append(id)

    # create the account
    command = "cleos create account eosio " + id + " EOS5H53JTqPpKcUw5KYg81top3Viit4HqUvqjkVifXiFqteixvT7G EOS5H53JTqPpKcUw5KYg81top3Viit4HqUvqjkVifXiFqteixvT7G"
    call(command, shell=True)

    # create the toll gate
    command = "cleos push action tolls create \'[\"" + id + "\",\"" + gatename + "\"," + str(latitude) + "," + str(longitude) + ",\"" + highway_name + "\"," + str(highway_number) + ",\"" + direction + "\"]\' -p " + id ;
    call (command, shell=True)


num_vehicles = 100
vehicles = []

for i in range(0, num_vehicles):

    vid = chars[random.randint(0, len(chars)-1)] + chars[random.randint(0, len(chars)-1)] + chars[random.randint(0, len(chars)-1)] + chars[random.randint(0, len(chars)-1)] + chars[random.randint(0, len(chars)-1)]
    vehicles.append(vid);

    # create the account
    command = "cleos create account eosio " + vid + " EOS5H53JTqPpKcUw5KYg81top3Viit4HqUvqjkVifXiFqteixvT7G EOS5H53JTqPpKcUw5KYg81top3Viit4HqUvqjkVifXiFqteixvT7G"
    call(command, shell=True)


num_breaches = 1000

for i in range (0, num_breaches):

    gate = toll_gates[random.randint(0, len(toll_gates)-1)]
    vehicle = vehicles[random.randint(0, len(vehicles)-1)]
    breach_id = int(hashlib.sha256(gate + vehicle + str(datetime.datetime.now())).hexdigest(), 16) % 1000000

    command = "cleos push action tolls breachtoll \'[" + str(breach_id) + ",\"" + gate + "\",\"" + vehicle + "\"]\' -p " + gate + " -p " + vehicle
    #print (command)
    call (command, shell=True)

elapsed_time = time.time() - start_time
print (time.strftime("%H:%M:%S", time.gmtime(elapsed_time)))
