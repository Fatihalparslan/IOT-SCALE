
import paho.mqtt.client as mqtt 
from xlwt import *
ck=Workbook();
k1=ck.add_sheet('page1')
#k1.write(row,column,variable)
k1.write(0,0,'Grams')

# set your mqtt variable
mqtt_username = "fatih"
mqtt_password = "alparslan"
mqtt_topic = "test"
mqtt_broker_ip = "192.168.1.100" #IP address of Raspberry PI
j=0
client = mqtt.Client()
# Set the username and password for the MQTT client
client.username_pw_set(mqtt_username, mqtt_password)

# These functions handle what happens when the MQTT client connects to the broker
def connect(client, userdata, flags, rc):
    # rc is the error code returned when connecting to the broker
    print ("Connected!", str(rc))
    
    # Once the client has connected to the broker, subscribe to the topic
    client.subscribe(mqtt_topic)
# These functions handle what happens then the topic receives a message
def message(client, userdata, msg):
    # set j variable as a global variable
    global j
    a=float(msg.payload)
    print("Topic: ", msg.topic + "\nMessage: " + str(msg.payload)+"\n")
    # The message itself is stored in the msg variable
    # and details about who sent it are stored in userdata    
    k1.write(j+1,0,a)#write data under grams
    j=j+1#row number
    ck.save('load_cell.xls') #save file 


# Here, we are telling the client which functions are to be run
# on connecting, and on receiving a message

client.on_connect = connect
client.on_message = message
j=0 #declaretion of j variable
# Once everything has been set up, we can (finally) connect to the broker
# 1883 is the listener port that the MQTT broker is using
client.connect(mqtt_broker_ip, 1883)

# Once we have told the client to connect, let the client object run itself
client.loop_forever()
client.disconnect()
