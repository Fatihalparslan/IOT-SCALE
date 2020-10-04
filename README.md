# IOT SCALE
# GENERAL DIAGRAM
![IOT](https://user-images.githubusercontent.com/16806606/95004244-65510d80-05f1-11eb-8162-485b5553cc74.png)
# ARDUINO NODE MCU CONNECTION
![hx711_load_cell_wiring](https://user-images.githubusercontent.com/16806606/95004186-bad8ea80-05f0-11eb-8bb9-f4590c7a2ab5.png)
# COMMAND FOR INSTALL AND SET MQTTT MOSQUITTO ON RASPBERRY PI
Update & Upgrade RPI.
```

sudo apt-get update
sudo apt-get upgrade

```
Install Mosquitto mqtt broker and Subscriber
```
sudo apt-get install mosquitto -y
sudo apt-get install mosquitto-clients -y

```
Open Mosquitto.conf File
```
sudo nano /etc/mosquitto/mosquitto.conf

```
Delete the following line in the  file opened
```
include_dir /etc/mosquitto/conf.d

```
Paste the following lines to replace the deleted line
```
allow_anonymous false
password_file /etc/mosquitto/pwfile
listener 1883

```
save&exit the nano editor 

Now you can add your username with this command. Type in your username in the section called "username".
```
sudo mosquitto_passwd -c /etc/mosquitto/pwfile "username"
```
For example like this.
```
sudo mosquitto_passwd -c /etc/mosquitto/pwfile fatih
```
For more detailed information, see this video : https://youtu.be/_uFVRrQsGKU
