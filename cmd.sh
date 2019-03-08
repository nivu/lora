cd C:\Users\Nivu\Microchip\LoRaSuite\Applications\LoRaDevUtility

java -jar LoRaDevUtility.jar


cd E:\git\lora\Python

# start app tx packets
python decode.py

# start gateway tx packets
python gwdecode.py

# mqtt capture all packets


# contineous gps transmit code
cd LoRaWAN/GPS/TinyGPSUp/TInyGPSUp.ino

# location change dr and transmit 50 packets
cd LoRaWAN/LOC/LOC.ino

# device application mapping

0004a30b0020096f -> GPS -> gps_write.py -> gps_data.csv

0004A30B001FEBCF -> LOC -> loc_write.py -> loc_data.csv

application/1 -> app pkts -> decode.py -> lorawan_data.csv

gateway/+/rx -> gw rx pkts -> gedecode.py -> print cmd

confirm duty cycle change
