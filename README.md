# autonomous-watering-system
Project for autonomous plant watering with ESP8266 and Pi B+
----

Pi Setup:
===========
1. package signing key
```
wget http://repo.mosquitto.org/debian/mosquitto-repo.gpg.key
sudo apt-key add mosquitto-repo.gpg.key
```

2. add rep to apt
```
cd /etc/apt/sources.list.d/
sudo wget http://repo.mosquitto.org/debian/mosquitto-buster.list
```

4. apt Installation Broker + Client
```
apt-get update
apt-get upgrade -y
apt-get install mosquitto mosquitto-clients -y
```

5. Einstellungen zB. WebPort hinzufügen
    sudo nano /etc/mosquitto/mosquitto.conf


---


## Check Status / Ports
```
service mosquitto status
lsof -i:1883
lsof -i:9001
```

## Daten empfangen/Threads abonieren
    mosquitto_sub -h 192.168.178.190 -t "#" -v
(-d für Debugnachrichten)

## Nachricht versenden
    mosquitto_pub -d -t /Plant1/hum -m 26

