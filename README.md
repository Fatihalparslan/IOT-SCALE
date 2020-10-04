# IOT SCALE
# GENERAL DIAGRAM
![IOT](https://user-images.githubusercontent.com/16806606/95004244-65510d80-05f1-11eb-8162-485b5553cc74.png)
# ARDUINO NODE MCU CONNECTION
![hx711_load_cell_wiring](https://user-images.githubusercontent.com/16806606/95004186-bad8ea80-05f0-11eb-8bb9-f4590c7a2ab5.png)
# CODE FOR INSTALL AND SET MQTTT MOSQUITO ON RASPBERRY PI
```

sudo apt-get update
sudo apt-get upgrade

```
```
sudo apt-get install mosquitto -y
sudo apt-get install mosquitto-clients -y

```

```
sudo nano /etc/mosquitto/mosquitto.conf

```

```
include_dir /etc/mosquitto/conf.d

```
```
allow_anonymous false
password_file /etc/mosquitto/pwfile
listener 1883

```
```
sudo mosquitto_passwd -c /etc/mosquitto/pwfile username
```
```
sudo mosquitto_passwd -c /etc/mosquitto/pwfile fatih
```
