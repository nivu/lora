sudo kill $(sudo lsof -t -i:8080)
sudo systemctl restart mosquitto
sudo systemctl start loraserver
journalctl -u loraserver
sudo systemctl start lora-app-server
journalctl -u lora-app-server

mosquitto_pub -u loraroot -P root -t "my" -m '{"applicationName": "ktlora","deviceName": "kt_lora_4","data": "MQ"}'
