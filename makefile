# *****************************************************

CC = arduino-cli
NAME = air_sensor_mkr_zero
BOARD = arduino:samd:mkrzero
PORT = /dev/ttyACM0
#PORT = /dev/ttyUSB0 or sth similar

#arduino-cli compile --fqbn arduino:samd:mkrzero
#arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:samd:mkrzero

# ****************************************************

$(NAME): 
	$(CC) compile --fqbn $(BOARD)

upload: $(NAME)
	$(CC) upload -p $(PORT) --fqbn $(BOARD)
