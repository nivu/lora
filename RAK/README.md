# Chirpstack installation WSL2 Windows

[Original Doc](https://www.chirpstack.io/project/guides/debian-ubuntu/)

```shell
sudo service postgresql start

mosquitto

redis-server

chirpstack-gateway-bridge

sudo nano /etc/chirpstack-network-server/chirpstack-network-server.toml

sudo chirpstack-network-server -c /etc/chirpstack-network-server/chirpstack-network-server.toml

sudo nano /etc/chirpstack-application-server/chirpstack-application-server.toml

sudo chirpstack-application-server -c /etc/chirpstack-application-server/chirpstack-application-server.toml
```

## RAK Raspberry Pi Config

```shell
sudo raspi-config

sudo gateway-config 
```

## RAK811 LPWAN Breakout Module AT Commands

[Buy | Documentation](https://store.rakwireless.com/products/rak811-lpwan-breakout-module)

[Connect to TTN](https://www.thethingsnetwork.org/docs/devices/rak811-wisnode-lora-module/connecting-to-ttn/)

### Device Details
```
at+version

at+get_config=device:status
```

### LoRa Details
```
at+get_config=lora:status
```

### OTAA
```
at+set_config=lora:join_mode:0

at+set_config=lora:app_key:7e168bedd4a616c8e43d3ee667afbfc1
```
### ABP

```
at+set_config=lora:join_mode:1

at+set_config=lora:dev_addr:009fead0

at+set_config=lora:nwks_key:91e16093cd784c0c272696061415a741

at+set_config=lora:apps_key:2f4cc548fc5d84978bac519507006537
```

### SEND
```
at+join

at+send=lora:2:1234
```