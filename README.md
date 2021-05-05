# FridgeController
Controls the temperature of aa fridge over network


upload: python3 upload.py --chip esp8266 --port COM3 --baud 921600 --before default_reset --after hard_reset write_flash 0x0 temperaturReader.ino.bin 
