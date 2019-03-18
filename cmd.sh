cd C:\Users\Nivu\Microchip\LoRaSuite\Applications\LoRaDevUtility

java -jar LoRaDevUtility.jar


cd E:\git\lora\Python

# start app 1 tx packets (kt lora mote)
python decode.py

# start gateway tx packets
python gwdecode.py

# mqtt capture gps packets
python gps_write.py

# capture gw packets
python loc_write.py

# capture app 2 packets (microchip motes)
python mcdecode.py

# contineous gps transmit code
cd LoRaWAN/GPS/TinyGPSUp/TInyGPSUp.ino

# location change dr and transmit 50 packets
cd LoRaWAN/LOC/LOC.ino

# device application mapping

0004a30b0020096f -> GPS -> gps_write.py -> gps_data.csv

0004A30B001FEBCF -> LOC -> loc_write.py -> loc_data.csv

application/1 -> app1 pkts -> decode.py -> app1_data.csv

application/2 -> app2 pkts -> mcdecode.py -> app2_data.csv

gateway/+/rx -> gw rx pkts -> gwdecode.py -> print cmd

change all device duty cycle to 9 -> 10%
backup all data before starting experiment
connect rst to 10th pin
loc program upload on each location