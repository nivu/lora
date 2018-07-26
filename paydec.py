from lora.crypto import loramac_decrypt
payload = '8001170126000100169867466B65E7ED634C818059'
sequence_counter = 1
key = '30F7B300CA6F509998ECB25E933CCA93'
dev_addr = '26011701'
print(loramac_decrypt(payload, sequence_counter, key, dev_addr))